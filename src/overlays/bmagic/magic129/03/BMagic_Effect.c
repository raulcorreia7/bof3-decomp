#include "magic129_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC10(void) {
    MagicModuleSteps handlers = D_801EEC04;
    PartyMember*     saved_task;
    PartyMember*     saved_battler;
    u8               i;

    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.mode);

    BMAGIC_RUN_EFFECT_SLOTS(D_801F05D8, func_801EFF40);
}

MATCH void func_801EED18(void) {
    u16          i;
    u8           slot;
    u32          member;
    PartyMember* work;

    BMAGIC_CLEAR_EFFECTS(i);
    Battle_CenterCamera();
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 56;
    SELF(PartyMember)->header.mode += 1;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        SELF(PartyMember)->header.mode = 2;
        return;
    }
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        member = i;
        if (g_Game.members[member].header.flags & PARTY_MEMBER_FLAG_OCCUPIED) {
            slot                               = Battle_AllocEffect(1, 106);
            work                               = SELF(PartyMember);
            g_BattleEffects[slot].unk_0B       = member << 4;
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_04       = i;
            g_BattleEffects[slot].arg.unk_09   = 60;
            g_BattleEffects[slot].target.party = work;
            SELF(PartyMember)->param.unk_0B += 1;
        }
    }
}
