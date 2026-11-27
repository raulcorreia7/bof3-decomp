#include "area085_13.h"

MATCH void func_801F35A0(void) {
    PartyMember* battler;
    PartyMember* battler2;

    if (SELF(Actor)->timer != 0) {
        battler = &D_801469B8;
        if (SELF(Actor)->param.unk_0B != 0) {
            battler = g_Game.members;
        }
        battler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
        SELF(Actor)->timer -= 1;
        return;
    }
    battler2 = &D_801469B8;
    if (SELF(Actor)->param.unk_0B != 0) {
        battler2 = g_Game.members;
    }
    battler2->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
    g_Actors[SELF(Actor)->unk_03].header.flags = 0;
    g_Actors[SELF(Actor)->unk_04].header.flags = 0;
    SELF(Actor)->header.mode                   = 2;
}
