#include "area145_14.h"

MATCH void func_801F3E10(void) {
    TASK(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    COORD_INT(TASK(Actor)->pos.z) = Area_HeightRead(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) + 2000;
    TASK(Actor)->gravity          = -8;
    setVector(TASK(Actor), 0, 0, 0);
    TASK(Actor)->unk_04 = 1;
    Script_Select(0x3B);
    g_ScriptState->flags |= 0x40;
    g_ScriptState->unk_01 = (D_80146250 - g_Game.members) * 20;
    g_ScriptState->cursor -= 2;
}
