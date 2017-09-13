# file      rules.mk
# brief     Makefile compilation rules for application artifacts

# by default CROSS_COMPILE is empty
CC	:=$(CROSS_COMPILE)gcc
C++	:=$(CROSS_COMPILE)g++
CPP	:=$(CROSS_COMPILE)cpp
AR	:=$(CROSS_COMPILE)ar
LD	:=$(CROSS_COMPILE)ld
AS	:=$(CROSS_COMPILE)as

RM	:=rm -rf
MKDIR_P := mkdir -p
