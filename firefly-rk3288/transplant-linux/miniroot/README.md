miniroot is a tiny shell environment, used to create and load root file system, such as Ubuntu, Gentoo and Arch Linux, etc. These systems can be reside in root or sub directories on any supported storage device. This means that we can install multiple OS in eMMC Flash, TF card or USB disk, and boot from one of them. Very handy to switch OS, no need to modify and flash parameter file (parameter file is used to specify the important partition info of flash storage).
### how to build the miniroot ###
1. get the miniroot
2. get the initrd
3. package initrd-miniroot: initrd-miniroot=initrd+miniroot
4. package the image file: linux-boot-miniroot.img=zImage+inird-miniroot

#### get the miniroot ####
1.1 download the linux-boot-miniroot.img form [firefly web](http://www.t-firefly.com/download/fireprime/firmware/linux-boot-miniroot.img)  
1.2 split the linux-boot-miniroot.img  
    ./split_boot.pl linux-boot-miniroot.img  
1.3 you can get the files like this  
* linux-boot-miniroot.img-kernel //the kernel
* linux-boot-miniroot.img-ramdisk.gz //the miniroot fs
1.4 if you want to get the source file
    gunzip linux-boot-miniroot.img-ramdisk.gz  
    cpio -i < linux-boot-miniroot.img-ramdisk  
#### get the initrd ####
    find . ! -path "./.git*" \
        ! -path "./README.md" \
        ! -path "./Makefile" \
        | cpio -H newc  -ov | gzip > ../initrd.img

#### package inird-miniroot ####
#### package linux-boot-miniroot ####
        mkbootimg --kernel $ZIMAGE --ramdisk $INITRD_MINIROOT -o $LINUX_BOOT_IMG_MINIROOT  
