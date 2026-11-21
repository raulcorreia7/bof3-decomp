#include "engine/game/00/game_00.h"

MATCH void UI_CursorDrawPanel(void) {
    UI_CursorDraw(g_UiPanelCurrent->pos.x, g_UiPanelCurrent->pos.y, 0);
}
