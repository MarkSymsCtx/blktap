
AM_CFLAGS  = -Wall
AM_CFLAGS += -Werror

sbin_PROGRAMS = lvm-util

lvm_util_SOURCES = main.c

noinst_LTLIBRARIES = liblvmutil.la

liblvmutil_la_SOURCES  = lvm-util.c
liblvmutil_la_SOURCES += lvm-util.h
liblvmutil_la_CPPFLAGS = -D_GNU_SOURCE

lvm_util_CPPFLAGS  = -D_GNU_SOURCE
lvm_util_CPPFLAGS += -DLVM_UTIL

lvm_util_LDADD = liblvmutil.la
