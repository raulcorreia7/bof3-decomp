#include "boss050_16.h"

MATCH void func_800C1A08(void) {
    PartyMember* saved;

    saved                  = ((PartyMember*)g_Task);
    ((PartyMember*)g_Task) = D_801EC2E0->target.party;
    func_801E52F0((*g_BattleCurrentEnemy->unk_E8 + 4) & HALF_MASK);
    Actor_SelectScript(2U);
    ((PartyMember*)g_Task) = saved;
    saved->header.mode += 1;
}
