#include "area174_13.h"

/* func_801F4D1C */
MATCH void Area_PaletteFreeOnAreaChange(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        GFX_PaletteFreeSlotOwner(g_Self);
    }
}
