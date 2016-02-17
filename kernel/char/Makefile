obj-m :=char.o

KDIR := /home/linjc/raspberrypi/linux-rpi

all:
	make -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers  modul*
