#include "lvm-util_test.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int
lvm_open_vg(const char *vgname, struct vg *vg);

void
test_lvm_open_vg_correct(void **state)
{
	char *vgs_out = get_vgs_out();
	struct vg vg;

	FILE *test_scan = fmemopen(vgs_out, strlen(vgs_out), "r");
	int   rc;

	will_return(__wrap_popen, test_scan);
	expect_value(__wrap_pclose, stream, test_scan);

	rc = lvm_open_vg(VG_NAME, &vg);

	assert_return_code(rc, 0); 
	assert_string_equal(vg.name, VG_NAME);
	assert_int_equal(vg.extent_size, VG_EXTENT_SIZE);
	assert_int_equal(vg.lv_cnt, LV_COUNT);
	assert_int_equal(vg.pv_cnt, PV_COUNT);
	assert_string_equal(vg.pvs[0].name, PV_NAME);
	assert_int_equal(vg.pvs[0].start, PE_START);
	assert_non_null(vg.pvs);
	assert_non_null(vg.lvs);

    free(vgs_out);
	free(vg.pvs);
	free(vg.lvs);
}

void
test_lvm_open_vg_vg_not_found(void **state)
{
	char vgs_out[] = "\n";
	struct vg vg;
	void     *zeroed_mem = calloc(1, sizeof(vg));

	FILE *test_scan = fmemopen(vgs_out, strlen(vgs_out), "r");
	int   rc;

	will_return(__wrap_popen, test_scan);
	expect_value(__wrap_pclose, stream, test_scan);

	rc = lvm_open_vg(VG_NAME, &vg);

	/*
	 * lvm-util.c:156
	 * XXX: Should probably be one of:
	 *     ENOENT
	 *     ENXIO
	 *     ENODEV
	 */
	assert_int_equal(rc, -EINVAL);
	assert_memory_equal(&vg, zeroed_mem, sizeof(vg));

	free(zeroed_mem);
}

void
test_lvm_open_vg_bad_vgs_output(void **state)
{

}


const struct CMUnitTest lvm_open_vg_tests[] = {
	cmocka_unit_test(test_lvm_open_vg_correct),
	cmocka_unit_test(test_lvm_open_vg_vg_not_found),
	cmocka_unit_test(test_lvm_open_vg_bad_vgs_output),
};

const struct CMUnitTest *get_lvm_open_vg_tests()
{
	return lvm_open_vg_tests;
}
