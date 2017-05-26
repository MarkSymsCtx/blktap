
#ifndef _LVM_UTIL_TEST_H_
#define _LVM_UTIL_TEST_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <lvm-util.h>

/*
 * The values of the 'options' of the 'vgs' and 'lvs'
 * commands are defined here as 'const's
 */

/* 'vgs' options */
const char     VG_NAME[]      = "VG_XenStorage-UNIT-TEST";
const uint64_t VG_EXTENT_SIZE = 4000000;
const int      LV_COUNT       = 6;
const int      PV_COUNT       = 1;
const char     PV_NAME[]      = "/dev/sdx9";
const uint64_t PE_START       = 10000000;

/* 'lvs' options */
const char * const LV_NAME[] = {
    "MGT",
    "VHD-TEST-LV-0",
    "VHD-TEST-LV-1",
    "VHD-TEST-LV-2",
    "VHD-TEST-LV-2",
    "VHD-TEST-LV-2",
    "VHD-TEST-LV-2",
    "VHD-TEST-LV-3",
    "VHD-TEST-LV-4",
};

const uint64_t LV_SIZE[] = {
    1000000,
    1100000,
    1200000,
    1300000,
    1300000,
    1300000,
    1300000,
    1400000,
    1500000,
};

const char * const SEGTYPE[] = {
    "linear",
    "linear",
    "linear",
    "linear",
    "linear",
    "linear",
    "linear",
    "linear",
    "linear",
};

const uint32_t SEG_COUNT[] = { 1, 1, 1, 4, 4, 4, 4, 1, 1, };
const unsigned long long SEG_START[] = { 0, 0, 0, 0, 2310, 2410, 2510, 0, 0, };
const uint64_t SEG_SIZE[] = { 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, };

/* Option 'devices' split into 2 (NAME, START), for easier manipulation.
 * In 'lvs's output it looks like this:
 *     DEVICES_NAME[i](DEVICES_START[i])
 *     /dev/sdx9(20)     */

const char * const DEVICES_NAME[] = {
    "/dev/sdx9",
    "/dev/sdx9",
    "/dev/sdx9",
    "/dev/sdx9",
    "/dev/sdx9",
    "/dev/sdx9",
    "/dev/sdx9",
    "/dev/sdx9",
    "/dev/sdx9",
};

const uint64_t DEVICES_START[] = { 0, 10, 20, 30, 40, 50, 60, 70, 80 };


FILE *__wrap_popen(void);
void  __wrap_pclose(FILE *stream);

/*
 * These functions return a dummy output string
 * using 'vgs' and 'lvs' options' values.
 * XXX: pointer MUST be freed by the caller.
 */
char *get_vgs_out(void);
char *get_lvs_out(void);

void dummy_vg_init(struct vg *dummy_vg, bool init_lvs);

#endif /* _LVM_UTIL_TEST_H_ */
