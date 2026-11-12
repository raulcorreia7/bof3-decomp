#include "start_08.h"

/* func_801E9350 */
MATCH void Menu_DrawCampIcons(void) {
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
            func_801644D8(s_CampMenuPanelIds[(u8)i], (g_MenuCurrentPanel->pos.x + (u8)i * 16) & HALF_MASK, g_MenuCurrentPanel->pos.y, 16, 0x10,
                          ((u8)i == 6 && g_MenuCurrentPanel->unk_0C) ? 0x40 : 0x80);
        }
    }
    cur  = g_MenuCurrentPanel->unk_0A;
    grow = g_MenuCurrentPanel->u.icons.grow;
    func_801644D8(s_CampMenuPanelIds[(u8)cur], (g_MenuCurrentPanel->pos.x + cur * 0x10 - grow) & HALF_MASK, (g_MenuCurrentPanel->pos.y - grow) & HALF_MASK, (grow * 2 + 0x10) & BYTE_MASK,
                  (grow * 2 + 0x10) & BYTE_MASK, (g_MenuCurrentPanel->unk_0A == 6 && g_MenuCurrentPanel->unk_0C) ? 0x40 : 0x80);
    g_MenuCurrentPanel->unk_0B = g_MenuCurrentPanel->unk_0A;
}
