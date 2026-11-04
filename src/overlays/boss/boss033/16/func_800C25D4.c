#include "boss033_16.h"

MATCH void func_800C25D4(void) {
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
    work->unk_02++;
    func_8014DAEC();
}
