#include "start_08.h"

MATCH void Menu_DrawPanelCursor(void) {
    Menu_DrawCursorSprite(g_MenuCurrentPanel->x, g_MenuCurrentPanel->y, 0);
}
