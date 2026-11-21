#include "start_08.h"

/* Menu step that sets the cursor y position. */
/* func_801EA158 */
MATCH void Menu_SetPosY(void) {
    MENU_ADVANCE_PANEL(pos.y, MENU_PANEL_STEP_Y, 38);
}
