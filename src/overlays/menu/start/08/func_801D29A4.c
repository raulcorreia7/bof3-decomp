#include "start_08.h"

MATCH void func_801D29A4(void) {
    s32  i;
    u32  j;
    u8   count;
    u32  idx;
    u8*  panel;
    u16* entry;

    i = 0;
    for (;;) {
        count = Party_CountOrder(0);
        idx   = i & BYTE_MASK;
        if (idx >= (u32)count) {
            break;
        }
        panel            = &D_801484E0 + idx * 0x24;
        panel[1]         = 6;
        panel[2]         = 5;
        panel[3]         = 2;
        panel[0]         = 1;
        ((u16*)panel)[2] = 320;
        j                = idx + 4;
        entry            = (u16*)((u8*)&D_80148336 + j * 0x24);
        ((u16*)panel)[3] = *entry;
        panel[0xA]       = i;
        i += 1;
    }
    panel      = &D_801484BC;
    D_801484BD = 6;
    D_801484BE = 9;
    D_801484BF = 2;
    *panel     = 1;
    D_801484C0 = 0x14;
    D_801484C2 = -0x14;
    D_801484CC = 0;
    D_801485DD = 6;
    D_801485DE = 0xA;
    panel += 0x120;
    *panel     = 0;
    D_801485E6 = 0;
    D_801485E7 = 1;
}
