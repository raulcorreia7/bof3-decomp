#include "start_08.h"

MATCH void func_801E9350(void) {
    s32 i;
    u16 grow;
    u16 cur;

    if (g_MenuPanelTaskCurrent->unk_0B != g_MenuPanelTaskCurrent->unk_0A) {
        g_MenuPanelTaskCurrent->unk_10 = 0;
    }
    if ((s16)g_MenuPanelTaskCurrent->unk_10 < 3) {
        g_MenuPanelTaskCurrent->unk_10++;
    }
    for (i = 0; (u8)i < 7; i++) {
        if ((u8)i != g_MenuPanelTaskCurrent->unk_0A) {
            func_801644D8(s_CampMenuPanelIds[(u8)i], (g_MenuPanelTaskCurrent->x + (u8)i * 0x10) & HALF_MASK,
                          g_MenuPanelTaskCurrent->y, 0x10, 0x10,
                          ((u8)i == 6 && g_MenuPanelTaskCurrent->unk_0C) ? 0x40 : 0x80);
        }
    }
    cur  = g_MenuPanelTaskCurrent->unk_0A;
    grow = g_MenuPanelTaskCurrent->unk_10;
    func_801644D8(s_CampMenuPanelIds[(u8)cur], (g_MenuPanelTaskCurrent->x + cur * 0x10 - grow) & HALF_MASK,
                  (g_MenuPanelTaskCurrent->y - grow) & HALF_MASK, (grow * 2 + 0x10) & BYTE_MASK,
                  (grow * 2 + 0x10) & BYTE_MASK,
                  (g_MenuPanelTaskCurrent->unk_0A == 6 && g_MenuPanelTaskCurrent->unk_0C) ? 0x40 : 0x80);
    g_MenuPanelTaskCurrent->unk_0B = g_MenuPanelTaskCurrent->unk_0A;
}
