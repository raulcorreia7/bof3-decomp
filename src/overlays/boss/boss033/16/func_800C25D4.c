#include "boss033_16.h"

MATCH void func_800C25D4(void) {
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
    work->header.step++;
    func_8014DAEC();
}
