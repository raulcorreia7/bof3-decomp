#include "area148_13.h"

MATCH void func_801F4544(void) {
    s32 y;

    ((Actor*)g_SpadWork)->unk_18 =
        ((Actor*)g_SpadWork)->x.fixed + (g_FacingSteps[((Actor*)g_SpadWork)->direction_08].x * 5);
    y = ((Actor*)g_SpadWork)->y.fixed + (D_80181B98[((Actor*)g_SpadWork)->direction_08 * 2] * 5);
    ((Actor*)g_SpadWork)->unk_1C  = y;
    ((Actor*)g_SpadWork)->gravity = Area_SampleHeight(((Actor*)g_SpadWork)->unk_18, y) << 0x10;
}
