#include "magic060_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC34(void) {
    Magic060Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

INCLUDE_ASM(func_801EECA4);

MATCH void func_801EED68(void) {
    u32          slot;
    PartyMember* work;

    if (g_Task->param.unk_0B == 2) {
        slot                               = Battle_AllocEffect(1, 0x12) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 2;
        g_BattleEffects[slot].target.party = work;
        g_Task->unk_09                     = 0x10;
        g_Task->header.mode                = g_Task->header.mode + 1;
    }
}

MATCH void func_801EEE00(void) {
    u8 timer;

    if (g_Battle.target_selector < 3U) {
        func_801EF174();
    } else {
        func_801EF2DC();
    }
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEE84(void) {
    if (g_Battle.target_selector < 3) {
        func_801EF174();
    } else {
        func_801EF2DC();
    }
    if (g_InputPressed != 0) {
        g_Task->param.unk_0B = 0x83;
        g_Task->header.mode++;
    }
}

MATCH void func_801EEF04(void) {
    u16* flags;

    if (g_Task->param.unk_0B == 0x80) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EEF50);

/* Sets the bit of the targeted enemy's id in g_IdentifiedEnemies. */
MATCH void Effect_MarkTargetIdentified(void) {
    u8 id;

    id = ENEMY_COMBATANT(g_Battle.target_selector).enemy_id.byte.kind;
    BIT_ARRAY_SET(g_IdentifiedEnemies, id);
}

/* Whether the bit of the targeted enemy's id is set in g_IdentifiedEnemies. */
MATCH bool Effect_TargetIsIdentified(void) {
    u8 id;

    id = ENEMY_COMBATANT(g_Battle.target_selector).enemy_id.byte.kind;
    return BIT_ARRAY_TEST(g_IdentifiedEnemies, id) != 0;
}

INCLUDE_ASM(func_801EF174);

INCLUDE_ASM(func_801EF2DC);

INCLUDE_ASM(func_801EF470);

INCLUDE_ASM(func_801EF590);

INCLUDE_ASM(func_801EF76C);

INCLUDE_ASM(func_801EF924);

INCLUDE_ASM(func_801EFB00);
