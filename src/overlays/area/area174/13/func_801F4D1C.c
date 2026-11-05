#include "area174_13.h"

MATCH void func_801F4D1C(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        GFX_FreePaletteSlotOwner((s32)g_Task);
    }
}
