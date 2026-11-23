#include "battle_15.h"

MATCH void func_800A8BD0(void) {
    u8*   work;
    void* saved;

    BATTLE_ACTIVE_PARTY.header.flags &= ~ACTOR_FLAG_HIDDEN;
    work  = (u8*)g_BattleEffectBattler;
    saved = TASK(void);
    TASK_SET(work);
    Script_Select((((PartyMember*)work)->facing + 4) & BYTE_MASK);
    TASK_SET(saved);
    Effect_Reset();
}
