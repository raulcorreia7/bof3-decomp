#include "area040_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3400(s32 x, s32 y) {
    s32 cell_x;
    s32 cell_y;
    s32 i;
    s32 j;

    if (g_GameCellType != 6) {
        return 0;
    }
    if (LOBU(g_Game.current->unk_2B) != 0) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x27) != 0) {
        return 0;
    }
    if (g_SceneEventState.mode != 0x10) {
        return 0;
    }
    func_801F369C();
    FAKE_BARRIER(); /* FAKE: the retail bytes keep the cell shifts below this call. */
    cell_x = x >> 16;
    cell_y = y >> 16;
    if ((u32)(cell_x - 0x94) < 4U && (u32)(cell_y - 0x20) < 4U) {
        if ((func_801F30B8(cell_x, cell_y) & BYTE_MASK) == 0) {
            Area_SetCellPalette(cell_x, cell_y);
        } else {
            Area_ClearCellPalette(cell_x, cell_y);
        }
        func_801F372C(x, y);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 5));
        return 0;
    }
    if ((func_801F3570() & BYTE_MASK) != 0) {
        return 0;
    }
    for (i = 0; (i & BYTE_MASK) < 4U; i++) {
        for (j = 0; (j & BYTE_MASK) < 4U; j++) {
            Area_ClearCellPalette((s16)((i & BYTE_MASK) + 0x94), (j & BYTE_MASK) + 0x20);
        }
    }
    return 0;
}
#else
INCLUDE_ASM(func_801F3400);
#endif
