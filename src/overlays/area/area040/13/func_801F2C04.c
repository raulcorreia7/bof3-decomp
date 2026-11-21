#include "area040_13.h"

MATCH s32 func_801F2C04(void) {
    s16 slot;

    slot = SP_REF(s16, 0x0u) = Actor_FindFreeField();
    if (slot != GAME_NONE) {
        Actor_SpawnFromRecord(D_801F4970);
    } else {
        g_ScriptState->cursor -= 2;
    }
}
