#include "start_08.h"

void func_801DAC1C(void);

#ifdef NON_MATCHING
NON_MATCHING void func_801DAA68(void) {
    u8*            record;
    MenuPanelTask* rows;
    u8*            panel;
    u8             i;
    u32            index;
    u8             count;

    record = &D_801484BC;
    rows   = (MenuPanelTask*)(record + 0x120);
    i      = 0;
    record++;
    record--;
    g_MenuPanelTasks[11].handler = 6;
    g_MenuPanelTasks[11].mode    = 9;
    g_MenuPanelTasks[11].state   = 2;
    record[0]                    = 1;
    g_MenuPanelTasks[11].pos.x   = 0x14;
    g_MenuPanelTasks[11].pos.y   = 0x10;
    g_MenuPanelTasks[11].unk_10  = 0;
    for (i = 0; i < 2; i++) {
        rows[i].handler = 6;
        rows[i].mode    = 0xA;
        rows[i].active  = 0;
        rows[i].unk_0A  = 0;
    }

    i = 0;
    for (;;) {
        count = Party_CountOrder(PARTY_ORDER_FIELD);
        index = i & BYTE_MASK;
        if ((s32)index >= (u32)count) {
            break;
        }
        panel      = &D_801483C0 + (index * 0x24);
        panel[0xA] = i;
        i += 1;
        panel[0x1]       = 6;
        panel[0x2]       = 0;
        panel[0x3]       = 0;
        panel[0x0]       = 1;
        ((u16*)panel)[2] = 0x11;
        ((u16*)panel)[3] = (index * 0x36) + 0x3E;
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
/* blocker: row address formed before i++; first diff: 0x801DAAE0. */
INCLUDE_ASM(func_801DAA68);
#endif
