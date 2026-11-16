#include "area111_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3460(void) {
    s16 x;
    s16 y;
    s8  step;
    u8  facing;
    u8  value;

    x = (g_Task->pos.x.part.integer - 11) >> 1;
    y = (g_Task->pos.y.part.integer - 177) >> 1;
    func_801F4604(x, y, 0x10);
    facing = g_Task->direction_08 & 7;
    step   = 0;
    for (;;) {
        x += (s8)D_80181B00[facing * 2];
        if ((u16)x >= 7) {
            goto done;
        }
        y += (s8)D_80181B01[facing * 2];
        if ((u16)y >= 7) {
            goto done;
        }
        if (x & 1) {
            value = D_801F5C18[y * 4 + x / 2] & 0xF;
        } else {
            value = D_801F5C18[y * 4 + x / 2] >> 4;
        }
        if (value != 0) {
            break;
        }
        step += 4;
    }
done:
    if (step != 0) {
        g_ScriptState->unk_07 = step + 1;
    }
    g_Task->vz = 0;
    func_801F4604(x, y, 0);
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
}
#else
INCLUDE_ASM(func_801F3460);
#endif
