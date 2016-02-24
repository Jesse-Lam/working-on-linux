# ubuntu15.04 on firefly-rk3288
该教程是在官方已有的ubuntu系统的基础上做的，主要参考了[firefly的维基文档](http://wiki.t-firefly.com/index.php/Firefly-RK3288/Build_Ubuntu_rfs)
##准备工作
官方ubuntu固件  
官方linux-boot-miniroot.img  
firefly-rk3288开发板  
串口转usb小板  
显示器  
##步骤
1.在板子烧写官方的ubuntu系统  
2.Boot分区烧写linux-boot-miniroot.img  
3.开机进入miniroot  
4.格式化原来的ubuntu文件系统：  
`mkfs.ext4 -E nodiscard /dev/mmcblk0p5`  
5.挂载文件系统：  
`mount /dev/mmcblk0p5 /mnt`  
6.下载ubuntu-core (这里可以在板子上下载，也可以在电脑下载然后拷贝进去)  
A.电脑上下载：  
`http://cdimage.ubuntu.com/ubuntu-core/releases/15.04/release/ubuntu-core-15.04-core-armhf.tar.gz`  
B.在板子上下载：  
`Wget -P /mnt http://cdimage.ubuntu.com/ubuntu-core/releases/15.04/release/ubuntu-core-15.04-core-armhf.tar.gz`  
7.解压：  
`mkdir /mnt/ubuntu  
tar -xpzf /mnt/ubuntu-core-15.04-core-armhf.tar.gz -C /mnt/ubuntu`  
8.设置主机名称：
`echo firefly > /mnt/ubuntu/etc/hostname  
sed -e ‘s/miniroot/firefly/’ < /etc/hosts > /mnt/ubuntu/etc/hosts`  
9.新增用户帐户：  
`chroot /mnt/ubuntu useradd -G sudo -m -s /bin/bash ubuntu  
echo ubuntu:ubuntu | chroot /mnt/ubuntu chpasswd`  
10.由于miniroot使用的是xinit,ubuntu15.04使用的是systemd,所以把ubuntu的systemd拷贝到miniroot执行库中：  
`mkdir /lib/systemd  
cp /mnt/ubuntu/lib/systemd/systemd /lib/systemd/`  
11.设置串口控制台：  
`cp /mnt/ubuntu/lib/systemd/system/serial-getty@.service /mnt/ubuntu/lib/systemd/system/serial-getty@ttyS2.service  
ln -s /mnt/ubuntu/lib/systemd/system/serial-getty@ttyS2.service /mnt/ubuntu/etc/systemd/system/getty.target.wants/`  
12.修改/mnt/ubuntu/lib/systemd/system/serial-getty@ttyS2.service把里面的“%i.device”改为“%i”  
13.启动ubuntu:  
`boot /mnt:/ubuntu lib/systemd/systemd`  
14.开机自动登陆:  
`vi /usr/share/lightdm/lightdm.conf.d/20-lubuntu.conf  
autologin-user=username`  
15.串口自动登陆:  
`vi /lib/systemd/system/serial-getty@ttyS2.service  
ExecStart=-/sbin/agetty -a root --keep-baud 115200,38400,9600 %I $TERM`  
16.

