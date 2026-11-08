#include "area198_13.h"

/* func_801F35A4 */
MATCH void Area_FreePaletteOnChange(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        GFX_FreePaletteSlotOwner(g_Task);
    } else {
        g_ScriptState->cursor = (g_ScriptState->cursor - 2u);
    }
}
