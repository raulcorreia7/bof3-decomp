#include "area174_13.h"

MATCH void func_801F3CE4(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        GFX_FreePaletteSlotOwner((s32)g_Task);
    } else {
        FIELD(u16, (void*)(u32)g_ScriptState, 0xAu) = (u16)(FIELD(u16, (void*)(u32)g_ScriptState, 0xAu) - 2u);
    }
}
