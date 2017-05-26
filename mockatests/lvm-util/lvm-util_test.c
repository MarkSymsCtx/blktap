#include <stdio.h>
#include <string.h>
#include <lvm-util.h>
#include "lvm-util_test.h"

#include "test-suites.h"

FILE *
__wrap_popen(void)
{
	return (FILE*) mock();
}

void
__wrap_pclose(FILE *stream)
{
	check_expected_ptr(stream);
	fclose(stream);
}

char *
get_vgs_out(void)
{
    char *vgs_out;

    asprintf(
        &vgs_out,
        "  %s   %"PRIu64"   %d   %d   %s %"PRIu64"\n",
        VG_NAME, VG_EXTENT_SIZE, LV_COUNT, PV_COUNT, PV_NAME, PE_START
    );

    return vgs_out;
}

char *
get_lvs_out(void)
{
    char *lvs_out;

    asprintf(
        &lvs_out,
        "  %s   %"PRIu64"  %s  %"PRIu32"  %llu   %"PRIu64"  %s(%"PRIu64")\n"
        "  %s   %"PRIu64"  %s  %"PRIu32"  %llu   %"PRIu64"  %s(%"PRIu64")\n"
        "  %s   %"PRIu64"  %s  %"PRIu32"  %llu   %"PRIu64"  %s(%"PRIu64")\n"
        "  %s   %"PRIu64"  %s  %"PRIu32"  %llu   %"PRIu64"  %s(%"PRIu64")\n"
        "  %s   %"PRIu64"  %s  %"PRIu32"  %llu   %"PRIu64"  %s(%"PRIu64")\n"
        "  %s   %"PRIu64"  %s  %"PRIu32"  %llu   %"PRIu64"  %s(%"PRIu64")\n"
        "  %s   %"PRIu64"  %s  %"PRIu32"  %llu   %"PRIu64"  %s(%"PRIu64")\n"
        "  %s   %"PRIu64"  %s  %"PRIu32"  %llu   %"PRIu64"  %s(%"PRIu64")\n"
        "  %s   %"PRIu64"  %s  %"PRIu32"  %llu   %"PRIu64"  %s(%"PRIu64")\n",
        LV_NAME[0], LV_SIZE[0], SEGTYPE[0], SEG_COUNT[0], SEG_START[0], SEG_SIZE[0], DEVICES_NAME[0], DEVICES_START[0],
        LV_NAME[1], LV_SIZE[1], SEGTYPE[1], SEG_COUNT[1], SEG_START[1], SEG_SIZE[1], DEVICES_NAME[1], DEVICES_START[1],
        LV_NAME[2], LV_SIZE[2], SEGTYPE[2], SEG_COUNT[2], SEG_START[2], SEG_SIZE[2], DEVICES_NAME[2], DEVICES_START[2],
        LV_NAME[3], LV_SIZE[3], SEGTYPE[3], SEG_COUNT[3], SEG_START[3], SEG_SIZE[3], DEVICES_NAME[3], DEVICES_START[3],
        LV_NAME[4], LV_SIZE[4], SEGTYPE[4], SEG_COUNT[4], SEG_START[4], SEG_SIZE[4], DEVICES_NAME[4], DEVICES_START[4],
        LV_NAME[5], LV_SIZE[5], SEGTYPE[5], SEG_COUNT[5], SEG_START[5], SEG_SIZE[5], DEVICES_NAME[5], DEVICES_START[5],
        LV_NAME[6], LV_SIZE[6], SEGTYPE[6], SEG_COUNT[6], SEG_START[6], SEG_SIZE[6], DEVICES_NAME[6], DEVICES_START[6],
        LV_NAME[7], LV_SIZE[7], SEGTYPE[7], SEG_COUNT[7], SEG_START[7], SEG_SIZE[7], DEVICES_NAME[7], DEVICES_START[7],
        LV_NAME[8], LV_SIZE[8], SEGTYPE[8], SEG_COUNT[8], SEG_START[8], SEG_SIZE[8], DEVICES_NAME[8], DEVICES_START[8]
    );

    return lvs_out;
}

void
dummy_vg_init(struct vg *vg, bool init_lvs)
{
	strcpy(vg->name, VG_NAME);
	vg->extent_size = VG_EXTENT_SIZE;

	vg->pv_cnt = PV_COUNT;
	vg->lv_cnt = LV_COUNT;

	vg->pvs = calloc(PV_COUNT, sizeof(struct pv));
	vg->lvs = calloc(LV_COUNT, sizeof(struct lv));

	strcpy(vg->pvs[0].name, PV_NAME);
	vg->pvs[0].start = PE_START;

    if (!init_lvs) {
        return;
    }

    /*
    for (int i = 0; i < LV_COUNT; ++i) {
        strcpy(vg->lvs[i].name, LV_NAME[i]);
        vg->lvs[i].size = LV_SIZE[i];
        vg->lvs[i].segments = SEG_COUNT[i];
        vg->lvs[i].first_segment.type = !strcmp(SEGTYPE[i], "linear")
            ? LVM_SEG_TYPE_LINEAR
            : LVM_SEG_TYPE_UNKNOWN;
        strcpy(vg->lvs[i].first_segment.device, DEVICES_NAME[i]);

        vg->lvs[i].first_segment.pe_start = (DEVICES_START[i] * VG_EXTENT_SIZE) + PE_START;
        vg->lvs[i].first_segment.pe_size = SEG_SIZE[i];
    }
    */
}


int main(void)
{
	return
		cmocka_run_group_tests(get_lvm_read_line_tests(), NULL, NULL)
		+ cmocka_run_group_tests(get_lvm_open_vg_tests(), NULL, NULL)
		+ cmocka_run_group_tests(get_lvm_scan_lvs_tests(), NULL, NULL)
	;
}
