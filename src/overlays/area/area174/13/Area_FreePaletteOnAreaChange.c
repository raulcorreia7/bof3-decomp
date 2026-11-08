#include "area174_13.h"

/* func_801F4D1C */
MATCH void Area_FreePaletteOnAreaChange(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        GFX_FreePaletteSlotOwner(g_Task);
    }
}
