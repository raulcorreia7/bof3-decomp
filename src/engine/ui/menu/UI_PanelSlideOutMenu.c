#include "engine/game/00/game_00.h"

/* func_801995F8 */
/* Moves the menu panel left by 32 pixels to x -170, then returns it to state 0. */
MATCH void UI_PanelSlideOutMenu(void) {
    MENU_RETREAT_PANEL(pos.vx, MENU_PANEL_STEP_X, MENU_PANEL_FLOOR_X);
}
