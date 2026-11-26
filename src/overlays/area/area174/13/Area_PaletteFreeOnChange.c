#include "area174_13.h"

/* Frees the area palette when the area changes. */
/* func_801F3CE4 */
MATCH void Area_PaletteFreeOnChange(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        GFX_PaletteFreeSlotOwner(g_Self);
    } else {
        FIELD(u16, (void*)(u32)g_ScriptState, 0xAu) = (FIELD(u16, (void*)(u32)g_ScriptState, 0xAu) - 2u);
    }
}
