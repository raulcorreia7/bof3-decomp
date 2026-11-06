#include "start_08.h"

MATCH void Menu_DrawPanelCursor(void) {
    Menu_DrawCursorSprite(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, 0);
}
