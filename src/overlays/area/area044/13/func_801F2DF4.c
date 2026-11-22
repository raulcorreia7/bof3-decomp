#include "area044_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2DF4(void) {
    u8  state;
    u8  variant;
    u8  i;
    s32 x;
    s32 column;

    state   = g_ScriptVars[3];
    variant = (state & 0x30) >> 4;
    if ((state & 3) == 0) {
        i = 0;
        do {
            x      = i;
            column = x + 0x3C;
            Area_CellSetCode(column, 0xA, 0);
            Area_CellSetCode(column, 0xB, 0);
            x += 0x40;
            Area_CellSetCode(x, 0xA, 0x10);
            Area_CellSetCode(x, 0xB, 0x10);
            Area_CellSetCode(column, 0xE, 0x10);
            Area_CellSetCode(column, 0xF, 0x10);
            i++;
        } while (i < 2);
    } else if ((state & 3) == 1) {
        i = 0;
        do {
            x      = i;
            column = x + 0x40;
            Area_CellSetCode(column, 0xA, 0);
            Area_CellSetCode(column, 0xB, 0);
            x += 0x3C;
            Area_CellSetCode(x, 0xA, 0x10);
            Area_CellSetCode(x, 0xB, 0x10);
            Area_CellSetCode(x, 0xE, 0x10);
            Area_CellSetCode(x, 0xF, 0x10);
            i++;
        } while (i < 2);
    } else {
        i = 0;
        do {
            x      = i;
            column = x + 0x3C;
            Area_CellSetCode(column, 0xE, 0);
            Area_CellSetCode(column, 0xF, 0);
            x += 0x40;
            Area_CellSetCode(x, 0xA, 0x10);
            Area_CellSetCode(x, 0xB, 0x10);
            Area_CellSetCode(column, 0xA, 0x10);
            Area_CellSetCode(column, 0xB, 0x10);
            i++;
        } while (i < 2);
    }
    if (variant == 0) {
        i = 0;
        do {
            x      = i;
            column = x + 0x3E;
            Area_CellSetCode(column, 0xC, 0);
            Area_CellSetCode(column, 0xD, 0);
            Area_CellSetCode(column, 0x8, 0x10);
            Area_CellSetCode(column, 0x9, 0x10);
            x += 0x3A;
            Area_CellSetCode(x, 0xC, 0x10);
            Area_CellSetCode(x, 0xD, 0x10);
            i++;
        } while (i < 2);
    } else if (variant == 1) {
        i = 0;
        do {
            x      = i;
            column = x + 0x3E;
            Area_CellSetCode(column, 0x8, 0);
            Area_CellSetCode(column, 0x9, 0);
            Area_CellSetCode(column, 0xC, 0x10);
            Area_CellSetCode(column, 0xD, 0x10);
            x += 0x3A;
            Area_CellSetCode(x, 0xC, 0x10);
            Area_CellSetCode(x, 0xD, 0x10);
            i++;
        } while (i < 2);
    } else {
        i = 0;
        do {
            x      = i;
            column = x + 0x3A;
            Area_CellSetCode(column, 0xC, 0);
            Area_CellSetCode(column, 0xD, 0);
            x += 0x3E;
            Area_CellSetCode(x, 0xC, 0x10);
            Area_CellSetCode(x, 0xD, 0x10);
            Area_CellSetCode(x, 0x8, 0x10);
            Area_CellSetCode(x, 0x9, 0x10);
            i++;
        } while (i < 2);
    }
}
#else
INCLUDE_ASM(func_801F2DF4);
#endif
