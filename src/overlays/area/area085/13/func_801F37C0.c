#include "area085_13.h"

MATCH void func_801F37C0(void) {
    Actor* work;
    u8     i;

    if (SCENARIO_PROGRESS == 0xC06) {
        SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        Party_MemberLoadSprite(CHAR_ID_GARR, 2);
        Script_Select(1);
        return;
    }
    for (i = 0; i < g_PartySize; i++) {
        if (g_Game.members[i].chr.character_id == CHAR_ID_GARR) {
            work              = SELF(Actor);
            work->pos.x.fixed = g_Game.members[i].pos.x.fixed;
            work->pos.y.fixed = g_Game.members[i].pos.y.fixed;
            work->pos.z.fixed = g_Game.members[i].pos.z.fixed;
        }
    }
    g_ScriptState->cursor -= 2;
}
