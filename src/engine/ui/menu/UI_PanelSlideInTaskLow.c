#include "engine/game/00/game_00.h"

/* func_801999B8 */
/* Moves the task panel down by 16 pixels to y 40, then returns it to state 0. */
MATCH void UI_PanelSlideInTaskLow(void) {
    MENU_ADVANCE_PANEL(pos.vy, MENU_PANEL_STEP_Y, 40);
}
