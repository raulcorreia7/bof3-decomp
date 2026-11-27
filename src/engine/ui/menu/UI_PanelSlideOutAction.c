#include "engine/game/00/game_00.h"

/* func_801997EC */
/* Moves the action panel left by 32 pixels to x -170, then returns it to state 0. */
MATCH void UI_PanelSlideOutAction(void) {
    MENU_RETREAT_PANEL(pos.vx, MENU_PANEL_STEP_X, MENU_PANEL_FLOOR_X);
}
