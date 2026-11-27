#include "boss050_16.h"

MATCH void func_800C1A08(void) {
    PartyMember* saved;

    saved               = (SELF(PartyMember));
    (SELF(PartyMember)) = D_801EC2E0->target.party;
    Battle_PlayEnemySE((*g_BattleCurrentEnemy->unk_E8 + 4) & HALF_MASK);
    Script_Select(2U);
    (SELF(PartyMember)) = saved;
    saved->header.mode += 1;
}
