#include "start_08.h"

/* Menu step that advances the panel y position toward its step. */
/* func_801EA158 */
MATCH void Menu_AdvancePanelY(void) {
    MENU_ADVANCE_PANEL(pos.vy, MENU_PANEL_STEP_Y, 38);
}
