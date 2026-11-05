#include "start_08.h"

void func_801DAC1C(void);

#ifdef NON_MATCHING
NON_MATCHING void func_801DAA68(void) {
    u8*            record;
    MenuPanelTask* rows;
    u8*            panel;
    u8             i;
    u32            idx;
    u8             count;

    record = &D_801484BC;
    rows   = (MenuPanelTask*)(record + 0x120);
    i      = 0;
    record++;
    record--;
    D_801484BD = 6;
    D_801484BE = 9;
    D_801484BF = 2;
    record[0]  = 1;
    D_801484C0 = 0x14;
    D_801484C2 = 0x10;
    D_801484CC = 0;
    for (i = 0; i < 2; i++) {
        rows[i].unk_00[1] = 6;
        rows[i].unk_00[2] = 0xA;
        rows[i].unk_00[0] = 0;
        rows[i].unk_0A    = 0;
    }

    i = 0;
    for (;;) {
        count = Party_CountOrder(0);
        idx   = i & BYTE_MASK;
        if ((s32)idx >= (u32)count) {
            break;
        }
        panel      = &D_801483C0 + (idx * 0x24);
        panel[0xA] = i;
        i += 1;
        panel[0x1]       = 6;
        panel[0x2]       = 0;
        panel[0x3]       = 0;
        panel[0x0]       = 1;
        ((u16*)panel)[2] = 0x11;
        ((u16*)panel)[3] = (idx * 0x36) + 0x3E;
        panel[0xB]       = 1;
        panel[0xC]       = 0;
    }

    Menu_DrawClutStrip(D_80144953);
    func_801DAC1C();
    D_80148651 = 2;
    D_80148652 = 0;
    D_80148654 = 5;
}
#else
/* Best draft 6 instructions off. First diff 0x801DAAE0: retail forms the row address before
 * i++, the draft increments first. while, do-while and a row pointer keep the draft order;
 * the panel base register also swaps (v0/v1). */
INCLUDE_ASM(func_801DAA68);
#endif
