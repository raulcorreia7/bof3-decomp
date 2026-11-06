#include "battle_15.h"

/* func_800B20D4 */
MATCH void Menu_DrawPanelCursor(void) {
    Menu_DrawCursorSprite(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, 0);
}
