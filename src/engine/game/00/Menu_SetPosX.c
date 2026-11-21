#include "game_00.h"

/* Menu step that sets the cursor x position. */
/* func_8019982C */
MATCH void Menu_SetPosX(void) {
    MENU_ADVANCE_PANEL(pos.x, MENU_PANEL_STEP_X, 17);
}
