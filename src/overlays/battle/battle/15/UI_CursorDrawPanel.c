#include "battle_15.h"

/* func_800B20D4 */
MATCH void UI_CursorDrawPanel(void) {
    UI_CursorDraw(g_UiPanelCurrent->pos.x, g_UiPanelCurrent->pos.y, 0);
}
