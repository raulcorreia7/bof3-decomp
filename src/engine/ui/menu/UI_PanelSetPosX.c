#include "engine/game/00/game_00.h"

/* Menu step that sets the cursor x position. */
/* func_8019982C */
MATCH void UI_PanelSetPosX(void) {
    MENU_ADVANCE_PANEL(pos.vx, MENU_PANEL_STEP_X, 17);
}
