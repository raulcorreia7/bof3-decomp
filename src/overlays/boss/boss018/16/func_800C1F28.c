#include "boss018_16.h"

MATCH void func_800C1F28(void) {
    Script_Select(4);
    Battle_DefeatEnemy();
    if (SELF(PartyMember)->slot == 4) {
        func_800C29AC(1, 2);
    } else {
        func_800C29AC(0, 2);
    }
    D_801EB66E                           = Area_HeightSample(D_801EB664, D_801EB668);
    g_Game.members[0].pos.z.part.integer = Area_HeightSample(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed);
    SELF(PartyMember)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_MODE(3);
    SELF(PartyMember)->header.step = 0;
    SELF(PartyMember)->unk_03      = 0;
}
