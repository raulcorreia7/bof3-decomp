#include "battle_15.h"

/* Menu step that sets the cursor x position. */
/* func_800B23F8 */
MATCH void Menu_SetPosX_800B23F8(void) {
    MENU_ADVANCE_PANEL(pos.vx, MENU_PANEL_STEP_X, 17);
}
