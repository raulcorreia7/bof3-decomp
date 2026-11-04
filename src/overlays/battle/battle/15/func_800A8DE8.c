#include "battle_15.h"

MATCH void func_800A8DE8(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_SpadWork;
    work->flags_00 |= ACTOR_FLAG_SEMI_TRANSPARENT;
    work                      = (PartyBattler*)g_SpadWork;
    work->unk_5C              = 3u;
    work                      = (PartyBattler*)g_SpadWork;
    work->unk_5D              = -(work->word_08.byte.unk_0B * 16);
    work                      = (PartyBattler*)g_SpadWork;
    work->unk_5F              = -(work->word_08.byte.unk_0B * 16);
    work                      = (PartyBattler*)g_SpadWork;
    work->unk_5E              = -(work->word_08.byte.unk_0B * 16);
    work                      = (PartyBattler*)g_SpadWork;
    work->word_08.byte.unk_09 = 8u;
    work                      = (PartyBattler*)g_SpadWork;
    work->step_01++;
    func_8014DAEC();
}
