#include "start_08.h"

/* func_801E9350 */
MATCH void Menu_DrawCampIcons(void) {
    s32 i;
    u16 grow;
    u16 cur;

    if (g_UIPanelCurrent->unk_0B != g_UIPanelCurrent->unk_0A) {
        ((s16*)g_UIPanelCurrent)[8] = 0;
    }
    if (((s16*)g_UIPanelCurrent)[8] < 3) {
        ((s16*)g_UIPanelCurrent)[8]++;
    }
    for (i = 0; (u8)i < 7; i++) {
        if ((u8)i != g_UIPanelCurrent->unk_0A) {
            UI_IconDrawCell(s_CampMenuPanelIds[(u8)i], ((u16)g_UIPanelCurrent->pos.vx + (u8)i * 16) & HALF_MASK, (u16)g_UIPanelCurrent->pos.vy, UI_ICON_CELL_SIZE, UI_ICON_CELL_SIZE,
                            ((u8)i == 6 && g_UIPanelCurrent->unk_0C) ? 0x40 : 0x80);
        }
    }
    cur  = g_UIPanelCurrent->unk_0A;
    grow = g_UIPanelCurrent->u.icons.grow;
    UI_IconDrawCell(s_CampMenuPanelIds[(u8)cur], ((u16)g_UIPanelCurrent->pos.vx + cur * 0x10 - grow) & HALF_MASK, ((u16)g_UIPanelCurrent->pos.vy - grow) & HALF_MASK, (grow * 2 + 0x10) & BYTE_MASK,
                    (grow * 2 + 0x10) & BYTE_MASK, (g_UIPanelCurrent->unk_0A == 6 && g_UIPanelCurrent->unk_0C) ? 0x40 : 0x80);
    g_UIPanelCurrent->unk_0B = g_UIPanelCurrent->unk_0A;
}
