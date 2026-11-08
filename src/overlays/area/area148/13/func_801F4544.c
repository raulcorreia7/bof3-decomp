#include "area148_13.h"

MATCH void func_801F4544(void) {
    s32 y;

    (g_Task)->unk_18  = (g_Task)->pos.x.fixed + (g_FacingSteps[(g_Task)->direction_08].x * 5);
    y                 = (g_Task)->pos.y.fixed + (g_FacingStepY[(g_Task)->direction_08 * 2] * 5);
    (g_Task)->unk_1C  = y;
    (g_Task)->gravity = Area_SampleHeight((g_Task)->unk_18, y) << 0x10;
}
