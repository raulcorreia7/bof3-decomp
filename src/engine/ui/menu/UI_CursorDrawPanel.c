#include "engine/game/00/game_00.h"

MATCH void UI_CursorDrawPanel(void) {
    UI_CursorDraw(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, 0);
}
