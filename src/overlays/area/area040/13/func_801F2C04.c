#include "area040_13.h"

MATCH s32 func_801F2C04(void) {
    s16 slot;

    slot = SP_REF(s16, 0x0u) = Actor_FindFree();
    if (slot != GAME_NONE) {
        func_801A4D54(D_801F4970);
    } else {
        g_ScriptState->cursor -= 2;
    }
}
