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
BIN_NAME=testservice
LIB_NAME=lib$(MOD_NAME).so

PRJ_OBJS_CPP=\

PRJ_OBJS_C=\
service_interfaces.o

PRJ_LDFLAGS=-rdynamic -L$(PREFIX)/lib $(LDFLAGS)
PRJ_CFLAGS=-I. -fPIC -DPIC $(DBGFLAGS) $(LCOVFLAGS) $(CFLAGS) -I$(PREFIX)/../include -I/usr/include

service_interfaces.o: service_interfaces.c
	mkdir -p ../bin
	$(CC) $(PRJ_CFLAGS) ../libs/$(LIB_NAME) -o $(BIN_NAME) service_interfaces.c
	mv $(BIN_NAME) ../bin
	

$(LIB_NAME): $(PRJ_OBJS_CPP) $(PRJ_OBJS_C) 
	$(CC)  -o $@ $(PRJ_OBJS_CPP) $(PRJ_OBJS_C)  $(PRJ_LDFLAGS)  $(LCOVFLAGS) -shared

$(BIN_NAME): $(LIB_NAME) service_manager.o
	$(CC)  -o $@ service_interfaces.o $(PRJ_LDFLAGS) $(LCOVFLAGS)

clean:
	rm -rf *.o *.so ../bin/$(BIN_NAME)


