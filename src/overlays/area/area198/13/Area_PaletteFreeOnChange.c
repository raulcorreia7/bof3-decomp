#include "area198_13.h"

/* func_801F35A4 */
MATCH void Area_PaletteFreeOnChange(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        GFX_PaletteFreeSlotOwner(g_Self);
    } else {
        g_ScriptState->cursor = (g_ScriptState->cursor - 2u);
    }
}
