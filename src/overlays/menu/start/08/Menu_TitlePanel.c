#include "start_08.h"

/* Menu_TitlePanel */
MATCH void Menu_TitlePanel(void) {
    u8* resource;
    s32 panel_x;
    u32 label_dx;

    g_MenuStartTitleSteps[g_UIPanelCurrent->state]();
    Menu_DrawHeaderBar((u16)g_UIPanelCurrent->pos.vx, (u16)g_UIPanelCurrent->pos.vy, MENU_HEADER_SHORT_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    resource = UI_MessageGetText(g_UIPanelCurrent->u.message.id);
    label_dx = (Game_ReadCommand(resource) & BYTE_MASK) * 4 - 0x25;
    panel_x  = (s16)(g_UIPanelCurrent->pos.vx - label_dx);
    UI_TextDraw(panel_x, g_UIPanelCurrent->pos.vy + 3, 0, Game_ReadCommand(resource) & BYTE_MASK, resource);
}
