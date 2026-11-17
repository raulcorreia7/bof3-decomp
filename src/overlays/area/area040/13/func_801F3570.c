#include "area040_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3570(void) {
    s32 x;
    s32 y;
    s32 column;
    s32 row;

    row = 0;
    do {
        y      = row + 0x20;
        column = 0;
        do {
            x = column + 0x94;
            if ((func_801F30B8(x, y) & BYTE_MASK) != D_801F4960[row][column]) {
                return 0;
            }
            column += 1;
        } while (column < 4);
        row += 1;
    } while (row < 4);

    SYS_SetFlag(g_SceneEventFlags, 0x27);
    func_801A4BC0(0x92, 0x1C, 0xA1);
    func_801A4BC0(0x93, 0x1C, 0xA1);
    func_801A4BC0(0x92, 0x1D, 0xC0);
    func_801A4BC0(0x93, 0x1D, 0xC0);
    g_SceneEventState.step = 0xA;
    Area_SetCellPalette(0x92, 0x1D);
    SND_PlaySE(EMI_CUE_ID(SND_BANK_AREA, 3));
    return 1;
}
#else
INCLUDE_ASM(func_801F3570);
#endif
