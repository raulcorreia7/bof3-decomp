#include "engine/game/00/game_00.h"

/* func_80199978 */
/* Moves the task panel down by 16 pixels to y 16, then returns it to state 0. */
MATCH void UI_PanelSlideInTaskTop(void) {
    MENU_ADVANCE_PANEL(pos.y, MENU_PANEL_STEP_Y, 16);
}
