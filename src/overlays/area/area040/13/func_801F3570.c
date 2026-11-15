#include "area040_13.h"

extern u8 D_801F4960;
s32       func_801F30B8(s32 x, s32 y);

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3570(void) {
    u8* palette;
    s32 x;
    s32 y;
    s32 column;
    s32 row;

    row = 0;
    do {
        y       = (s16)((row & BYTE_MASK) + 0x20);
        palette = (u8*)&D_801F4960 + ((row & BYTE_MASK) << 2);
        column  = 0;
        do {
            x = (column & BYTE_MASK) + 0x94;
            if ((func_801F30B8(x, y) & BYTE_MASK) != palette[column & BYTE_MASK]) {
                return 0;
            }
            column += 1;
        } while ((column & BYTE_MASK) < 4U);
        row += 1;
    } while ((row & BYTE_MASK) < 4U);

    SYS_SetFlag(g_SceneEventFlags, 0x27);
    func_801A4BC0(0x92, 0x1C, 0xA1);
    func_801A4BC0(0x93, 0x1C, 0xA1);
    func_801A4BC0(0x92, 0x1D, 0xC0);
    func_801A4BC0(0x93, 0x1D, 0xC0);
    g_SceneEventStep = 0xA;
    Area_SetCellPalette(0x92, 0x1D);
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
    return 1;
}
#else
INCLUDE_ASM(func_801F3570);
#endif
