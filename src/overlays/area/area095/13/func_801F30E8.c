#include "area095_13.h"

MATCH void func_801F30E8(void) {
    u8 i;

    for (i = 0; i < ACTOR_SLOT_COUNT; i++) {
        if ((g_SpawnedActors[i].header.flags & ACTOR_FLAG_IN_USE) && g_SpawnedActors[i].pos.x.part.integer == 0x41 && g_SpawnedActors[i].pos.y.part.integer == 0x3A) {
            break;
        }
    }
    if (i != ACTOR_SLOT_COUNT) {
        g_ScriptState->cursor -= 2;
    } else if (g_Game.members[0].u.field.mode_12B.u8_value != 0) {
        g_ScriptState->cursor -= 2;
        Game_SetScriptActive();
    } else {
        func_801BE1B0(0);
    }
}
