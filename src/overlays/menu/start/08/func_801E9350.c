#include "start_08.h"

MATCH void func_801E9350(void) {
    s32 i;
    u16 grow;
    u16 cur;

    if (((u8*)g_MenuCurrentPanel)[0xB] != ((u8*)g_MenuCurrentPanel)[0xA]) {
        ((s16*)g_MenuCurrentPanel)[8] = 0;
    }
    if (((s16*)g_MenuCurrentPanel)[8] < 3) {
        ((s16*)g_MenuCurrentPanel)[8]++;
    }
    for (i = 0; (u8)i < 7; i++) {
        if ((u8)i != ((u8*)g_MenuCurrentPanel)[0xA]) {
            func_801644D8(s_CampMenuPanelIds[(u8)i], (g_MenuCurrentPanel->x + (u8)i * 0x10) & HALF_MASK,
                          g_MenuCurrentPanel->y, 0x10, 0x10,
                          ((u8)i == 6 && ((u8*)g_MenuCurrentPanel)[0xC]) ? 0x40 : 0x80);
        }
    }
    cur  = ((u8*)g_MenuCurrentPanel)[0xA];
    grow = ((u16*)g_MenuCurrentPanel)[8];
    func_801644D8(s_CampMenuPanelIds[(u8)cur], (g_MenuCurrentPanel->x + cur * 0x10 - grow) & HALF_MASK,
                  (g_MenuCurrentPanel->y - grow) & HALF_MASK, (grow * 2 + 0x10) & BYTE_MASK,
                  (grow * 2 + 0x10) & BYTE_MASK,
                  (((u8*)g_MenuCurrentPanel)[0xA] == 6 && ((u8*)g_MenuCurrentPanel)[0xC]) ? 0x40 : 0x80);
    ((u8*)g_MenuCurrentPanel)[0xB] = ((u8*)g_MenuCurrentPanel)[0xA];
}
