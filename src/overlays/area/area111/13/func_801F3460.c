#include "area111_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3460(void) {
    s16 x;
    s16 y;
    s8  offset;
    s32 facing;
    u8  value;

    x = (TASK(Actor)->pos.x.part.integer - 11) >> 1;
    y = (TASK(Actor)->pos.y.part.integer - 177) >> 1;
    func_801F4604(x, y, 0x10);
    facing = TASK(Actor)->direction & 7;
    offset = 0;
    for (;;) {
        x += D_80181B00[facing * 2];
        if ((u16)x >= 7) {
            break;
        }
        y += D_80181B01[facing * 2];
        if ((u16)y >= 7) {
            break;
        }
        if (x & 1) {
            value = D_801F5C18[y][x / 2] & 0xF;
        } else {
            value = D_801F5C18[y][x / 2] >> 4;
        }
        if (value != 0) {
            break;
        }
        offset += 4;
    }
    if (offset != 0) {
        g_ScriptState->steps = offset + 1;
    }
    TASK(Actor)->vz = 0;
    func_801F4604(x, y, 0);
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
}
#else
INCLUDE_ASM(func_801F3460);
#endif
