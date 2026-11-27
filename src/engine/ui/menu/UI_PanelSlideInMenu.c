#include "engine/game/00/game_00.h"

/* func_80199638 */
/* Moves the menu panel right by 32 pixels to x 80, then returns it to state 0. */
MATCH void UI_PanelSlideInMenu(void) {
    MENU_ADVANCE_PANEL(pos.vx, MENU_PANEL_STEP_X, 80);
}
