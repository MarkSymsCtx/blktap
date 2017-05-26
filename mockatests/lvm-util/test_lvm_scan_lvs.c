#include "lvm-util_test.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int
lvm_scan_lvs(struct vg *vg);

void
test_lvm_scan_lvs_correct(void **state)
{
	char *lvs_out = get_lvs_out();

	FILE *test_scan = fmemopen(lvs_out, strlen(lvs_out), "r");
	struct vg dummy_vg;
	int   rc, i;

	dummy_vg_init(&dummy_vg, false);

	will_return(__wrap_popen, test_scan);
	expect_value(__wrap_pclose, stream, test_scan);

	rc = lvm_scan_lvs(&dummy_vg);
	assert_return_code(rc, 0); 

	for (i = 0; i < LV_COUNT; ++i) {
		assert_string_equal(dummy_vg.lvs[i].name, LV_NAME[i]);
		assert_int_equal(dummy_vg.lvs[i].segments, SEG_COUNT[i]);
		assert_int_equal(dummy_vg.lvs[i].size, LV_SIZE[i]);
		assert_string_equal(dummy_vg.lvs[i].first_segment.device, DEVICES_NAME[i]);
		assert_int_equal(dummy_vg.lvs[i].first_segment.pe_size, SEG_SIZE[i]);

		assert_int_equal(
			dummy_vg.lvs[i].first_segment.pe_start,
			(DEVICES_START[i] * VG_EXTENT_SIZE) + PE_START
			);
		assert_int_equal(
			dummy_vg.lvs[i].first_segment.type,
			LVM_SEG_TYPE_LINEAR
			);

		/*
		 * LVs with more than 1 segment, get printed in multiple lines
		 * (1 for each segment). 'lvm-util' prints 1 line per LV. If
		 * such an lv is found, we assume that its 1st line represents
		 * its 1st segment, and can jump the other lines.
		 */
		if (SEG_COUNT[i] > 1) {
			i += (SEG_COUNT[i] - 1);
		}
	}

	free(lvs_out);
	free(dummy_vg.pvs);
	free(dummy_vg.lvs);
}


const struct CMUnitTest lvm_scan_lvs_tests[] = {
	cmocka_unit_test(test_lvm_scan_lvs_correct),
};

const struct CMUnitTest *get_lvm_scan_lvs_tests()
{
	return lvm_scan_lvs_tests;
}
