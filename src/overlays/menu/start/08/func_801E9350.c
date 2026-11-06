#include "start_08.h"

MATCH void func_801E9350(void) {
    s32 i;
    u16 grow;
    u16 cur;

    if (g_MenuCurrentPanel->unk_0B != g_MenuCurrentPanel->unk_0A) {
        ((s16*)g_MenuCurrentPanel)[8] = 0;
    }
    if (((s16*)g_MenuCurrentPanel)[8] < 3) {
        ((s16*)g_MenuCurrentPanel)[8]++;
    }
    for (i = 0; (u8)i < 7; i++) {
        if ((u8)i != g_MenuCurrentPanel->unk_0A) {
            func_801644D8(s_CampMenuPanelIds[(u8)i], (g_MenuCurrentPanel->x + (u8)i * 0x10) & 0xFFFF,
                          g_MenuCurrentPanel->y, 0x10, 0x10, ((u8)i == 6 && g_MenuCurrentPanel->unk_0C) ? 0x40 : 0x80);
        }
    }
    cur  = g_MenuCurrentPanel->unk_0A;
    grow = g_MenuCurrentPanel->unk_10;
    func_801644D8(s_CampMenuPanelIds[(u8)cur], (g_MenuCurrentPanel->x + cur * 0x10 - grow) & 0xFFFF,
                  (g_MenuCurrentPanel->y - grow) & 0xFFFF, (grow * 2 + 0x10) & 0xFF, (grow * 2 + 0x10) & 0xFF,
                  (g_MenuCurrentPanel->unk_0A == 6 && g_MenuCurrentPanel->unk_0C) ? 0x40 : 0x80);
    g_MenuCurrentPanel->unk_0B = g_MenuCurrentPanel->unk_0A;
}
