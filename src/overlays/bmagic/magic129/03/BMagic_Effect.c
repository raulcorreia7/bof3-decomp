#include "magic129_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC10(void) {
    Magic129Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F05D8[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F05D8[i];
            g_BattleEffectBattler = D_801F05D8[i].target.party;
            func_801EFF40();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

MATCH void func_801EED18(void) {
    u16          i;
    u8           slot;
    u32          member;
    PartyMember* work;

    BMAGIC_CLEAR_EFFECTS(i);
    Battle_CenterCamera();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 56;
    g_Task->header.mode += 1;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        g_Task->header.mode = 2;
        return;
    }
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        member = i;
        if (g_Game.members[member].header.flags & PARTY_MEMBER_FLAG_OCCUPIED) {
            slot                               = Battle_AllocEffect(1, 106);
            work                               = g_Task;
            g_BattleEffects[slot].unk_0B       = member << 4;
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_04       = i;
            g_BattleEffects[slot].arg.unk_09   = 60;
            g_BattleEffects[slot].target.party = work;
            g_Task->param.unk_0B += 1;
        }
    }
}
