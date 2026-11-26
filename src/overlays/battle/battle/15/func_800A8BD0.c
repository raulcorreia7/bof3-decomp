#include "battle_15.h"

MATCH void func_800A8BD0(void) {
    u8*   work;
    void* saved;

    BATTLE_ACTIVE_PARTY.header.flags &= ~ACTOR_FLAG_HIDDEN;
    work  = (u8*)g_BattleEffectBattler;
    saved = SELF(void);
    SELF_SET(work);
    Script_Select((((PartyMember*)work)->facing + 4) & BYTE_MASK);
    SELF_SET(saved);
    Effect_Reset();
}
