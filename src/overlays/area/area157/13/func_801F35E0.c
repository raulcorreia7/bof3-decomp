#include "area157_13.h"

MATCH void func_801F35E0(void) {
    if (g_Task->direction_08 != 0) {
        if (abs(D_80145EC8 - ((((s32)g_Task->y.part.integer - 2) << 16) | 0x8000)) <= 0x8000) {
            if (abs(D_80145EC4 - ((s32)g_Task->x.part.integer << 16)) <= 0x10000 ||
                abs(D_80145EC4 - (((s32)g_Task->x.part.integer + 1) << 16)) <= 0x10000) {
                if (D_80143BB0 == 0) {
                    SND_PlayCue(EMI_CUE_ID(2, 0));
                }
                g_Task->step++;
            }
        }
    } else {
        if (abs(D_80145EC4 - ((((s32)g_Task->x.part.integer - 2) << 16) | 0x8000)) <= 0x8000) {
            if (abs(D_80145EC8 - ((s32)g_Task->y.part.integer << 16)) <= 0x10000 ||
                abs(D_80145EC8 - (((s32)g_Task->y.part.integer + 1) << 16)) <= 0x10000) {
                if (D_80143BB0 == 0) {
                    SND_PlayCue(EMI_CUE_ID(2, 0));
                }
                g_Task->step++;
            }
        }
    }
}
