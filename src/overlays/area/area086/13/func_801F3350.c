#include "area086_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3350(s32 cell_x, s32 cell_y) {
    s32 x;
    s32 y;
    s32 index;
    s32 offset;

    offset = 0;
    for (index = 0; index < 3; index++, offset += 4) {
        if (D_801F3CEC[offset] == (u8)cell_x && D_801F3CED[offset] == (u8)cell_y && D_801F3CEE[offset] == g_Game.members[0].facing) {
            break;
        }
    }
    if (index == 3) {
        return 0;
    }
    offset = index * 4;
    for (x = D_801F3CF8[offset]; x < D_801F3CFA[offset]; x++) {
        for (y = D_801F3CF9[offset]; y < D_801F3CFB[offset]; y++) {
            if ((s8)func_801F34F8(x, y) < 0) {
                return 0;
            }
        }
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x1C) != 0) {
        return 0;
    }
    SYS_ToggleFlag(g_SceneEventFlags, D_801F3CEF[index * 4]);
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
    func_8019ABB0(0xF);
    return 1;
}
#else
INCLUDE_ASM(func_801F3350);
#endif
