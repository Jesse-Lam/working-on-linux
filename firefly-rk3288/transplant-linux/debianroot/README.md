### how to build the linuxboot ###
zImage + initrd-debianroot => linux-boot.img
#### get the initrd ####
#### get the debianroot ####
#### package inird-debianroot ####
#### package linux-boot.img ####
    mkbootimg --kernel $ZIMAGE --ramdisk $INITRD -o $LINUX_BOOT_IMG

