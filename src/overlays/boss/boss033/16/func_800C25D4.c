#include "boss033_16.h"

MATCH void func_800C25D4(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_Task;
    work->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    work         = (PartyBattler*)g_Task;
    work->unk_5C = 3u;
    work         = (PartyBattler*)g_Task;
    work->unk_5D = -(work->unk_0B * 16);
    work         = (PartyBattler*)g_Task;
    work->unk_5F = -(work->unk_0B * 16);
    work         = (PartyBattler*)g_Task;
    work->unk_5E = -(work->unk_0B * 16);
    work         = (PartyBattler*)g_Task;
    work->unk_09 = 8u;
    work         = (PartyBattler*)g_Task;
    work->header.step++;
    func_8014DAEC();
}
