#include "start_08.h"

MATCH void UI_CursorDrawPanel(void) {
    UI_CursorDraw(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, 0);
}
