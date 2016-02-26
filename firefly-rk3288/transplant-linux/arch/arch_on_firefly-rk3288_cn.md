1.	把板子烧成firefly-rk3288官方的ubuntu单系统固件；
2.	下载miniroot文件：链接，把linux-boot-miniroot.img烧到boot分区(0xA000)
3.	重启板子，进入miniroot模式
miniroot#
4.	在官方的linux单系统中，/dev/mmcblk0p5分区就是存储linux文件系统的，我们就在此分区创建ext4文件系统，用于存放新的archlinux文件系统，这里把它挂载到/mnt
miniroot# mkfs.ext4 -E nodiscard /dev/mmcblk0p5 
miniroot# mount /dev/mmcblk0p5 /mnt/
5.	接上以太网，打开网络，下载archlinux文件系统（你也可以直接到archlinuxarm.org把文件包下载下来）
miniroot# udhcpc 
miniroot# wget –P /mnt http://archlinuxarm.org/os/ArchLinuxARM-veyron-latest.tar.gz
6.	解压：
miniroot# cd /mnt/
miniroot# tar -xzf ArchLinuxARM-veyron-latest.tar.gz 
7.	切换到archlinu 并新增用户：
miniroot# chroot /mnt/
[root@miniroot /]# useradd -m -s /bin/bash firefly
[root@miniroot /]# passwd firefly
8.	修改hostname:
[root@miniroot /]# vi /etc/hostname
9.	archlinux是用systemd来启动系统服务的，为了启动archlinux时能正常使用串口，这里需要做一点修改：
[root@miniroot /]# cp /lib/systemd/system/serial-getty\@.service /lib/systemd/system/serial-getty@ttyS2.service
[root@miniroot /]vi /lib/systemd/system/serial-getty@ttyS2.service （把里面的“%i.device”改为“%i”）
[root@miniroot /]# systemctl enable serial-getty@ttyS2.service
10.	如果以上步骤都顺利通过，可以在这里先启动archlinux试试了：
[root@miniroot /]# exit
miniroot# boot /mnt: /lib/systemd/systemd
11.	进入系统后可以用刚刚添加的用户名firefly进入了
Arch login: firefly
Password
12.	archlinux默认的root用户默认密码为root
[firefly@Arch ~]$ su
Password: 
[root@Arch firefly]#
13.	开机启动网络服务：
[root@Arch firefly]# systemctl enable dhcpcd.service
[root@Arch firefly]# systemctl start dhcpcd.service
14.	更新系统：
[root@Arch firefly]# pacman –Syu
注意：更新的时候会出现以下提示，要选择n，要不你会前功尽弃：
>>> Updating module dependencies. Please wait ...
A new kernel version needs to be flashed onto /dev/mmcblk0p5.
Do you want to do this now? [y|N]
n
15.	为了操作方便，这里安装sudo
[root@Arch firefly]# pacman -S sudo
编辑sudo，添加用户权限：
[root@Arch firefly]# visudo 
firefly ALL=(ALL) ALL
16.	添加wifi功能
网友Tiago Lobato在添加wifi功能的时候使用了libhybris，这里提供一种更方便的方法
从官方的ubuntu固件中拷贝/system/到arhclinux根文件系统目录：
[root@Arch firefly]# cp -r system/ /
从官方的ubuntu固件中拷贝wifi启动及关闭脚本到archlinux对应目录：
[root@Arch firefly]# cp wifi-on.sh /usr/local/bin/
[root@Arch firefly]# cp wifi-off.sh /usr/local/bin/
编辑systemd的service文件：
[root@Arch firefly]# vi /lib/systemd/system/wifi-on.service
[Unit]
Description=Turn on Wifi
ConditionFileIsExecutable=/usr/local/bin/wifi-on.sh
Before=network.target NetworkManager.service

[Service]
type=forking
ExecStart=/usr/local/bin/wifi-on.sh
TimeoutSec=0
RemainAfterExit=yes

[Install]
WantedBy=multi-user.target
启动wifi服务：
[root@Arch firefly]# systemctl enable wifi-on.service
17.	添加蓝牙功能：
安装bluez
[root@Arch mnt]# pacman -S bluez
[root@Arch mnt]# pacman -S bluez-utils
编辑配置文件
vi /etc/default/bluetooth-brcm
# Customize your own bluetooth mac address here
# MAC_ADDR=43:29:B1:55:01:01

BAUD_RATE=1500000
SERIAL_PORT=/dev/ttyS0
RFKILL_STATE=/sys/class/rfkill/rfkill0/state
# AP6335
HCD_FILE=/system/vendor/firmware/bcm4339a0.hcd
添加蓝牙启动脚本：
[root@Arch mnt]# cp do-brcm-patchram-plus.sh /usr/local/bin/
开机启动蓝牙服务：
[root@Arch firefly]# systemctl enable bluetooth-brcm-firmware.service
[root@Arch firefly]# systemctl enable bluetooth.service

18.	如果你想把你制作的文件系统做成一个完整的固件，有一步是必不可少的，那就是第一次启动系统的时候要resize文件系统对应的分区，这里我们在第一次开机的时候启动一个脚本来实现：
[root@Arch firefly]# touch /firstboot
[root@Arch firefly]# vi /usr/local/bin/first-boot.sh
[root@Arch firefly]# chmod a+x /usr/local/bin/first-boot.sh
[root@Arch firefly]# vi /lib/systemd/system/rc.local.service
#  This file is part of systemd.
#
#  systemd is free software; you can redistribute it and/or modify it
#  under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation; either version 2.1 of the License, or
#  (at your option) any later version.

# This unit gets pulled automatically into multi-user.target by
# systemd-rc-local-generator if /etc/rc.local is executable.
[Unit]
Description=/etc/rc.local Compatibility
ConditionFileIsExecutable=/etc/rc.local
Wants=network.target
Before=network.target

[Service]
Type=forking
ExecStart=/etc/rc.local
TimeoutSec=0
RemainAfterExit=yes

[Install]
WantedBy=multi-user.target

[root@Arch firefly]# vi /etc/rc.local
#
# rc.local
#
# This script is executed at the end of each multiuser runlevel.
# Make sure that the script will "exit 0" on success or any other
# value on error.
#
# In order to enable or disable this script just change the execution
# bits.
#
# By default this script does nothing.

/usr/local/bin/first-boot.sh

exit 0
[root@Arch firefly]# systemctl enable rc.local.service

19.	打包固件之前，为了减小固件的体积，可以把无用的安装包删掉：
[root@Arch firefly]# rm /var/cache/pacman/pkg/*
20.	打包(这里我用u盘存放我的文件系统镜像，即/dev/sda)：
重启板子之后再次进入miniroot:
miniroot# mount /dev/mmcblk0p5 /mnt/
miniroot# mkdir /media
miniroot# mount /dev/sda /media/
miniroot# dd if=/dev/zero of=/media/linuxroot.img bs=1M count=1024
miniroot# mkfs.ext4 -F -L linuxroot /media/linuxroot.img
miniroot# mkdir tmp
miniroot# mount -o loop /media/linuxroot.img /tmp/
miniroot# cp -a /mnt/* /tmp/
miniroot# umount /tmp/
miniroot# umount /media/
miniroot# umount /mnt/
21.	到此基本功能已经可以用了，这里，如果只是想在板子上运行archlinux，可以配置miniroot开机自启动archlinux，修改如下：
miniroot# editenv
root=/dev/mmcblk0p5:
init=/sbin/init
#ethaddr=00:11:22:33:44:55
#fbset_args="-a -nonstd 1 -g 1920 1080 1920 1080 32 -rgba 8/0,8/8,8/16,8/24"
#fbset_args="-a -nonstd 4 -g 1280 720 1280 720 16 -rgba 5/11,6/5,5/0,0/0"
autoboot=1
miniroot# saveenv
miniroot# reboot –f
启动后自动进入archlinux
如果不想自动进入archlinux，开机进入miniroot，可以做以下操作：
[root@Arch firefly]# dd if=/dev/zero of=/dev/block/mtd/by-name/misc

