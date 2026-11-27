#include "battle_15.h"

/* func_800B20D4 */
MATCH void UI_CursorDrawPanel(void) {
    UI_CursorDraw(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, 0);
}
