#include "engine/game/00/game_00.h"

/* func_80199938 */
/* Moves the task panel up by 16 pixels to y -20, then returns it to state 0. */
MATCH void UI_PanelSlideOutTask(void) {
    MENU_RETREAT_PANEL(pos.y, MENU_PANEL_STEP_Y, MENU_PANEL_HIDDEN_Y);
}
