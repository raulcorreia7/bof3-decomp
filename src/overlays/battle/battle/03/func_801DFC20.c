#include "battle_03.h"

MATCH void func_801DFC20(void) {
    volatile PartyMember* work;
    PartyMember*          scratch_work;

    g_Game.current->u.turn.unk_0B  = SELF(PartyMember)->unk_4B;
    scratch_work                   = SELF(PartyMember);
    work                           = g_Game.current;
    work->unk_134                  = scratch_work->unk_58;
    scratch_work->unk_04           = 0;
    SELF(PartyMember)->header.step = 1;
}
