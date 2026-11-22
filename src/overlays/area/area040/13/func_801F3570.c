#include "area040_13.h"

MATCH s32 func_801F3570(void) {
    u8 row;
    u8 column;

    for (row = 0; row < 4; row++) {
        for (column = 0; column < 4; column++) {
            if ((func_801F30B8((s16)(column + 0x94), (s16)(row + 0x20)) & BYTE_MASK) != D_801F4960[row][column]) {
                return 0;
            }
        }
    }

    SYS_SetFlag(g_SceneEventFlags, 0x27);
    func_801A4BC0(0x92, 0x1C, 0xA1);
    func_801A4BC0(0x93, 0x1C, 0xA1);
    func_801A4BC0(0x92, 0x1D, 0xC0);
    func_801A4BC0(0x93, 0x1D, 0xC0);
    g_SceneEventState.step = 0xA;
    Area_CellSetPalette(0x92, 0x1D);
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
    return 1;
}
