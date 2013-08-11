#**********************************************
# Makefile linux 2.6 Module 
# This makefile is written for Ubuntu 10.10
# It may not perfomance without erros on the
# other version or distributions.
#**********************************************
#    BY: Xu, Marco
#    Mail: marco.xu.f@gmail.com
#    2013/01/23
#**********************************************

TARGET=binder

obj-m := binder.o
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
all:
	make -C $(KERNELDIR) M=$(CURRENT_PATH) modules
clean:
	make -C $(KERNELDIR) M=$(CURRENT_PATH) clean
install:
	insmod binder.ko
unistall:
	rmmod binder 

