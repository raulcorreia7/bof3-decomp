#include "start_08.h"

MATCH void Menu_DrawPanelCursor(void) {
    Menu_DrawCursorSprite(g_MenuPanelTaskCurrent->x, g_MenuPanelTaskCurrent->y, 0);
}
