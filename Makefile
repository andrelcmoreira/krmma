obj-m	+= kmma.o
kmma-objs += kmma_main.o kmma_sysfs.o

modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
