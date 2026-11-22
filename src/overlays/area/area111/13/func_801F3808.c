#include "area111_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3808(void) {
    s16 x;
    s16 y;
    s32 index;
    u8  row;
    u8  col;

    index = (g_CurrentActor - g_PartyActors) + 1;
    x     = (g_Task->pos.x.part.integer - 11) / 2;
    y     = (g_Task->pos.y.part.integer - 177) / 2;
    func_801F4604(x, y, 0);
    for (row = 0; row < 7; row++) {
        for (col = 0; col < 7; col++) {
            if ((D_801F5C18[row][col / 2] & 0xF) == (u8)index) {
                D_801F5C18[row][col / 2] &= 0xF0;
            } else if ((D_801F5C18[row][col / 2] >> 4) == (u8)index) {
                D_801F5C18[row][col / 2] &= 0xF;
            }
        }
    }
    if (x & 1) {
        D_801F5C18[y][x / 2] |= index;
    } else {
        D_801F5C18[y][x / 2] |= index << 4;
    }
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
}
#else
INCLUDE_ASM(func_801F3808);
#endif
