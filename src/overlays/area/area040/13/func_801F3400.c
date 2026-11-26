#include "area040_13.h"

MATCH s32 func_801F3400(s32 x, s32 y) {
    s32 i;
    s32 j;
    /* FAKE: un-pinned C leaves 6 rows different; keep the x range value in a0. */
    FAKE_REG(s32, test_x, "a0");
    /* FAKE: un-pinned C leaves 6 rows different; keep the y range value in a1. */
    FAKE_REG(s32, test_y, "a1");
    /* FAKE: un-pinned C leaves 6 rows different; preserve the accepted x in s0. */
    FAKE_REG(s32, cell_x, "s0");
    /* FAKE: un-pinned C leaves 6 rows different; preserve the accepted y in s1. */
    FAKE_REG(s32, cell_y, "s1");

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
    test_x = x >> 16;
    test_y = y >> 16;
    if ((u32)(test_x - 0x94) < 4U && (u32)(test_y - 0x20) < 4U) {
        cell_x = test_x;
        cell_y = test_y;
        if ((func_801F30B8(cell_x, cell_y) & BYTE_MASK) == 0) {
            Area_CellSetPalette(cell_x, cell_y);
        } else {
            Area_CellClearPalette(cell_x, cell_y);
        }
        func_801F372C(x, y);
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 5));
        return 0;
    }
    if ((func_801F3570() & BYTE_MASK) != 0) {
        return 0;
    }
    for (i = 0; (i & BYTE_MASK) < 4U; i++) {
        for (j = 0; (j & BYTE_MASK) < 4U; j++) {
            Area_CellClearPalette((s16)((i & BYTE_MASK) + 0x94), (j & BYTE_MASK) + 0x20);
        }
    }
    return 0;
}
