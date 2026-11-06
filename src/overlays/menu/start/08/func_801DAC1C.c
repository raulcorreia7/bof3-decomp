#include "start_08.h"

extern s8 D_801ED66C;

/* Lays out the 3x3 start-menu grid: column 0 marks the rows below the member count, and each other cell arms the
 * next choice panel when its bit is set in D_80144F59 and the panel index is below the count's limit.
 * nonmatching 88.98%: retail keeps &D_801ED680 in t9 across both loops and computes row < count before the row
 * offset; ours rematerializes the address per row. resume: a loop shape that makes the table base invariant. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DAC1C(void) {
    u8* table;
    u8* panel;
    u8  count;
    u8  row;
    u8  col;
    u8  panel_index;
    u32 bit;
    u32 limit;
    u32 group_base;

    count = Party_CountOrder(0);
    switch (count) {
        case 1:
            group_base = 0;
            limit      = 1;
            break;
        case 2:
            group_base = 1;
            limit      = 3;
            break;
        case 3: /* a full party takes the default layout */
        default:
            group_base = 4;
            limit      = 6;
            break;
    }
    bit         = 1;
    panel_index = 0;
    for (row = 0; row < 3; row++) {
        table = &D_801ED680[row * 3];
        for (col = 0; col < 3; col++) {
            if (col == 0 && row < count) {
                table[0] = 1;
            } else {
                table[col] = 0;
            }
            if (col != 0) {
                if ((bit & D_80144F59) != 0 && panel_index < limit) {
                    table[col]       = 1;
                    panel            = &D_801484E0 + panel_index * 0x24;
                    panel[1]         = 6;
                    panel[2]         = 0xB;
                    panel[3]         = 2;
                    ((u16*)panel)[2] = (u16)((col - 1) * 0x4B + 0x140);
                    panel[0xA]       = (u8)(group_base + panel_index);
                    panel[0]         = 1;
                    ((u16*)panel)[3] = (u16)(row * 0x36 + 0x3E);
                    panel[0xB]       = panel_index;
                    panel[0xC]       = 0;
                    ((u16*)panel)[8] = 0xE00;
                } else {
                    table[col] = 0;
                }
                panel_index++;
                bit *= 2;
            }
        }
    }
    D_801ED678 = 0x7F;
    D_801ED67C = 0x7F;
    D_801ED668 = 0;
    D_801ED66C = 0;
    D_801ED670 = (g_SaveData.party_formation & 1) + 1;
    D_801ED674 = (u8)g_SaveData.party_formation >> 1;
}
#else
INCLUDE_ASM(func_801DAC1C);
#endif
