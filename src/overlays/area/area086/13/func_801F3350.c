#include "area086_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3350(s32 x, s32 y) {
    s32 i;
    s32 off;
    s32 row;
    s32 x0;
    s32 y0;
    u8* facing;

    i = 0;
    x &= BYTE_MASK;
    y &= BYTE_MASK;
    facing = &g_Game.members[0].facing;
    off    = 0;
    for (; i < 3; i++, off += 4) {
        if (x == D_801F3CEC[off] && y == D_801F3CED[off] && D_801F3CEE[off] == *facing) {
            break;
        }
    }
    if (i == 3) {
        return 0;
    }
    row = i * 4;
    x0  = D_801F3CF8[row];
    if (x0 < D_801F3CFA[row]) {
        do {
            y0 = D_801F3CF9[row];
            if (y0 < D_801F3CFB[row]) {
                do {
                    if ((s8)Area_FindMemberAt(x0, y0) >= 0) {
                        return 0;
                    }
                    y0++;
                } while (y0 < D_801F3CFB[row]);
            }
            x0++;
        } while (x0 < D_801F3CFA[row]);
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x1C) != 0) {
        return 0;
    }
    SYS_ToggleFlag(g_SceneEventFlags, D_801F3CEF[i * 4]);
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
    func_8019ABB0(0xF);
    return 1;
}
#else
INCLUDE_ASM(func_801F3350);
#endif
