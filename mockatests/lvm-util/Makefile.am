AM_CFLAGS  = -Wall
AM_CFLAGS += -Werror
# Arc coverage and wrap don't seem to be compatible
#AM_CFLAGS += -fprofile-arcs
#AM_CFLAGS += -ftest-coverage

check_PROGRAMS = test-lvm-util
TESTS = test-lvm-util

test_lvm_util_SOURCES = lvm-util_test.c test_lvm_open_vg.c test_lvm_read_line.c test_lvm_scan_lvs.c
test_lvm_util_CPPFLAGS = -D_GNU_SOURCE -I$(top_srcdir)/lvm
test_lvm_util_LDFLAGS = $(top_srcdir)/lvm/liblvmutil.la -lcmocka
test_lvm_util_LDFLAGS += -Wl,--wrap=popen,--wrap=pclose
