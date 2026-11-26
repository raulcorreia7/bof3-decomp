#include "engine/game/00/game_00.h"

MATCH void UI_CursorDrawPanel(void) {
    UI_CursorDraw(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy, 0);
}
