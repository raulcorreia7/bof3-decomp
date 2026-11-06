#include "area148_13.h"

MATCH void func_801F4544(void) {
    s32 y;

    ((Actor*)g_Task)->unk_18  = ((Actor*)g_Task)->pos.x.fixed + (g_FacingSteps[((Actor*)g_Task)->direction_08].x * 5);
    y                         = ((Actor*)g_Task)->pos.y.fixed + (D_80181B98[((Actor*)g_Task)->direction_08 * 2] * 5);
    ((Actor*)g_Task)->unk_1C  = y;
    ((Actor*)g_Task)->gravity = Area_SampleHeight(((Actor*)g_Task)->unk_18, y) << 0x10;
}
