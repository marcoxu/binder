#**********************************************
# Makefile linux 2.6 Module 
# This makefile is written for Ubuntu 10.10
# It may not perfomance without erros on the
# other version or distributions.
#**********************************************
#    BY: Xu, Marco
#    Mail: marco.xu.f@gmail.com
#    2013/08/04
#**********************************************
CC:=gcc
CXX:=g++

PREFIX:=$(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build

ifeq ($(ARCH_PLATFORM),x86)
	ARCH_CFLAGS=
else
	ARCH_CFLAGS=-DCPU_ARMV7L
endif

ifeq ($(OPT_CODE_COVERAGE),yes)
	LCOVFLAGS:=-fprofile-arcs -ftest-coverage
else
	LCOVFLAGS:=
endif

ifeq ($(OPT_DBG),yes)
	DBGFLAGS:=-g
else
	DBGFLAGS:=
endif

MOD_NAME=binder
LIB_NAME=lib$(MOD_NAME).so

PRJ_OBJS_CPP=\

PRJ_OBJS_C=\
binder.o

PRJ_LDFLAGS=-rdynamic -L$(PREFIX)/lib $(LDFLAGS)
PRJ_CFLAGS=-I. -fPIC -DPIC $(DBGFLAGS) $(LCOVFLAGS) $(CFLAGS) -I$(PREFIX)/../include -I/usr/include

binder.o: binder.c
#	$(CC) -c binder.c $(PRJ_CFLAGS)
	mkdir -p ../libs
	$(CC) binder.c -fPIC -shared $(PRJ_CFLAGS) -o $(LIB_NAME)
	mv $(LIB_NAME) ../libs

clean:
	rm -rf *.o *.so ../libs/$(LIB_NAME)


