#include "area145_14.h"

MATCH void func_801F3F18(void) {
    s16 result;

    SELF(Actor)->vz += SELF(Actor)->gravity;
    Actor_MovementUpdate();
    result = Area_HeightRead(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    if (COORD_INT(SELF(Actor)->pos.z) < result) {
        COORD_INT(SELF(Actor)->pos.z) = result;
        SELF(Actor)->vz               = 0;
        SELF(Actor)->gravity          = 0;
        SELF(Actor)->unk_04           = 2;
        Script_Select(0x39U);
        g_ScriptState->unk_01 = 4;
        return;
    }
    g_ScriptState->cursor -= 2;
}
