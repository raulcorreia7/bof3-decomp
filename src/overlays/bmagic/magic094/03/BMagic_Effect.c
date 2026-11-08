#include "magic094_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EED60};

    table[TASK_BYTES[1]]();
}

INCLUDE_ASM(func_801EEC5C);

/* Copies the selected actor's unk_2E and unk_30 - 0x10; at unk_0B 0xFF releases the target and plays. */
MATCH void func_801EED60(void) {
    u32           slot;
    u8*           selector;
    PartyBattler* battler;

    g_Task->unk_2E.half = g_BattleSelectedActor->unk_2E.half;
    g_Task->unk_30.half = g_BattleSelectedActor->unk_30.half - 0x10;
    if (g_Task->param.unk_0B == 0xFF) {
        BMAGIC_RELEASE_TARGET_AND_PLAY();
    }
}

MATCH void func_801EEE4C(void) {
    SYS_DISPATCH_BYTE(D_801EF988, g_Task->header.mode);
    if (g_BattleEffectBattler->param.unk_0B != 0xFF) {
        func_801EF654();
        func_801EF14C();
        func_801EF710();
        PopMatrix();
    }
    GFX_AddDitheredDrawMode(3, getTPage(0, 0, 320, 256));
}

MATCH void func_801EEF1C(void) {
    func_800A9610(g_BattleTargetSelector, 32);
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;
    g_Task->header.mode++;
}

MATCH void func_801EEF7C(void) {
    u32           slot;
    u8            step;
    PartyBattler* battler;

    g_Task->timer++;
    step           = g_Task->unk_09 + 1;
    g_Task->unk_09 = step;
    if (step == 0x10) {
        slot = LOBU(g_BattleTargetSelector);
        if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
            battler = &g_BattlePartyBattlers[slot];
        } else {
            battler = (PartyBattler*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
        }
        func_80196718(battler);
        func_8019651C(battler, 6, 4, 8, 0);
        g_Task->unk_09 = 0;
        g_Task->header.mode++;
    }
}

MATCH void func_801EF078(void) {
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = g_Task->timer;
    if (temp_v1 < 0x10U) {
        g_Task->timer = temp_v1 + 1;
    }
    temp_v1_2      = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v1_2;
    if ((temp_v1_2 & 0xFF) == 0x10) {
        g_Task->unk_09 = 0;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF0FC(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x20) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF14C);

MATCH void func_801EF654(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = g_Task->timer << 4;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF710);
