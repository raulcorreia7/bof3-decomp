#include "battle_15.h"

/* func_800B20D4 */
MATCH void UI_CursorDrawPanel(void) {
    UI_CursorDraw(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy, 0);
}
