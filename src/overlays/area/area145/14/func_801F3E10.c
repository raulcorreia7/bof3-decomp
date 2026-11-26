#include "area145_14.h"

MATCH void func_801F3E10(void) {
    SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    COORD_INT(SELF(Actor)->pos.z) = Area_HeightRead(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) + 2000;
    SELF(Actor)->gravity          = -8;
    setVector(SELF(Actor), 0, 0, 0);
    SELF(Actor)->unk_04 = 1;
    Script_Select(0x3B);
    g_ScriptState->flags |= 0x40;
    g_ScriptState->unk_01 = (g_GameState - g_Game.members) * 20;
    g_ScriptState->cursor -= 2;
}
