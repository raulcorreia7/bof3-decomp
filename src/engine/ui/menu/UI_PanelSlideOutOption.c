#include "engine/game/00/game_00.h"

/* func_801996FC */
/* Moves the option panel right by 32 pixels to the screen width, then returns it to state 0. */
MATCH void UI_PanelSlideOutOption(void) {
    MENU_ADVANCE_PANEL(pos.vx, MENU_PANEL_STEP_X, SCREEN_WIDTH);
}
