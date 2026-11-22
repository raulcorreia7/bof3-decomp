#include "area145_14.h"

MATCH void func_801F3F18(void) {
    s16 result;

    TASK(Actor)->vz += TASK(Actor)->gravity;
    Actor_MovementUpdate();
    result = Area_HeightRead(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    if (COORD_INT(TASK(Actor)->pos.z) < result) {
        COORD_INT(TASK(Actor)->pos.z) = result;
        TASK(Actor)->vz               = 0;
        TASK(Actor)->gravity          = 0;
        TASK(Actor)->unk_04           = 2;
        Script_Select(0x39U);
        g_ScriptState->unk_01 = 4;
        return;
    }
    g_ScriptState->cursor -= 2;
}
