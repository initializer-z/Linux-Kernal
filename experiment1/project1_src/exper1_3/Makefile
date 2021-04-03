obj-m:=mod3.o
KERNAL_PATH:=/lib/modules/$(shell uname -r)/build
all:
	make -C $(KERNAL_PATH) M=$(shell pwd) modules
clean:
	make -C $(KERNAL_PATH) M=$(shell pwd) clean	