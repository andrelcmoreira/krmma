obj-m	+= kermma.o
kermma-objs += kermma_main.o kermma_sysfs.o kermma_hooks.o

modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
