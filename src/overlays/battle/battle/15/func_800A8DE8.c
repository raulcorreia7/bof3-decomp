#include "battle_15.h"

MATCH void func_800A8DE8(void) {
    PartyMember* work;

    work = TASK(PartyMember);
    work->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    work         = TASK(PartyMember);
    work->unk_5C = 3u;
    work         = TASK(PartyMember);
    work->unk_5D = -(work->param.unk_0B * 16);
    work         = TASK(PartyMember);
    work->unk_5F = -(work->param.unk_0B * 16);
    work         = TASK(PartyMember);
    work->unk_5E = -(work->param.unk_0B * 16);
    work         = TASK(PartyMember);
    work->unk_09 = 8u;
    work         = TASK(PartyMember);
    work->header.mode++;
    Script_AnimStepOnce();
}
