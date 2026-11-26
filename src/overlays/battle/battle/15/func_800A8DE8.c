#include "battle_15.h"

MATCH void func_800A8DE8(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    work->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    work         = SELF(PartyMember);
    work->unk_5C = 3u;
    work         = SELF(PartyMember);
    work->unk_5D = -(work->param.unk_0B * 16);
    work         = SELF(PartyMember);
    work->unk_5F = -(work->param.unk_0B * 16);
    work         = SELF(PartyMember);
    work->unk_5E = -(work->param.unk_0B * 16);
    work         = SELF(PartyMember);
    work->unk_09 = 8u;
    work         = SELF(PartyMember);
    work->header.mode++;
    Script_AnimStepOnce();
}
