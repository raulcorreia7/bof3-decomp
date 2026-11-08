#include "battle_15.h"

MATCH void func_800A8DE8(void) {
    PartyMember* work;

    work = (PartyMember*)g_Task;
    work->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    work         = (PartyMember*)g_Task;
    work->unk_5C = 3u;
    work         = (PartyMember*)g_Task;
    work->unk_5D = -(work->param.unk_0B * 16);
    work         = (PartyMember*)g_Task;
    work->unk_5F = -(work->param.unk_0B * 16);
    work         = (PartyMember*)g_Task;
    work->unk_5E = -(work->param.unk_0B * 16);
    work         = (PartyMember*)g_Task;
    work->unk_09 = 8u;
    work         = (PartyMember*)g_Task;
    work->header.mode++;
    func_8014DAEC();
}
