#include "boss034_16.h"

MATCH void func_800C1CBC(void) {
    func_8014D978();
    if (EMI_IsReady() != 0) {
        Battle_DefeatEnemy();
        ((PartyMember*)g_Task)->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        ((PartyMember*)g_Task)->header.mode = 6;
        ((PartyMember*)g_Task)->header.step = 4;
        ((PartyMember*)g_Task)->unk_03      = 6;
    }
}
