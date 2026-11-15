#include "start_08.h"

/* Menu_TitlePanel */
MATCH void Menu_TitlePanel(void) {
    u8* resource;
    s32 panel_x;
    u32 label_dx;

    g_MenuStartTitleStates[g_MenuCurrentPanel->state]();
    Menu_DrawHeaderBar(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, MENU_HEADER_SHORT_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    resource = Message_GetText(g_MenuCurrentPanel->u.message.id);
    label_dx = (Game_ReadCommand(resource) & BYTE_MASK) * 4 - 0x25;
    panel_x  = (s16)(g_MenuCurrentPanel->pos.x - label_dx);
    UI_DrawText(panel_x, g_MenuCurrentPanel->pos.y + 3, 0, Game_ReadCommand(resource) & BYTE_MASK, resource);
}
