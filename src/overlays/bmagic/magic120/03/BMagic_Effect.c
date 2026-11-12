#include "magic120_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

MATCH void func_801EEEC8(void) {
    u32          slot;
    PartyMember* task;
    PartyMember* task2;

    if (g_Task->param.unk_0B == 1) {
        slot                               = Battle_AllocEffect(1, 15) & BYTE_MASK;
        task                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = 2;
        g_BattleEffects[slot].target.party = task;
        slot                               = Battle_AllocEffect(1, 15) & BYTE_MASK;
        task2                              = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = 3;
        g_BattleEffects[slot].target.party = task2;
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

/* func_801EF010 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

/* func_801EF054 */
MATCH void BMagic_UpdateWhelpBreath(void) {
    SYS_DISPATCH_BYTE(D_801F0CB0, g_Task->header.step);
    if (g_BattleEffectBattler->param.unk_0B != 0xFF) {
        if (g_Task->header.step != 0) {
            BMagic_DrawWhelpBreath();
        }
    }
}

INCLUDE_ASM(func_801EF0D8);

MATCH void func_801EF270(void) {
    u8 counter;
    g_Task->timer += 3;
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 8) {
        g_BattleEffectBattler->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpTimerCallSelector.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt120.h"

#include "overlays/bmagic/Effect_CountUpAndFinishAt136.h"

INCLUDE_ASM(BMagic_DrawWhelpBreath);

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EFDD4);

MATCH void func_801F0008(void) {
    func_8014D290();
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        func_801E5988();
    }
}

MATCH void func_801F0044(void) {
    u8 count;

    Actor_StepAnimLoop();
    func_8014D290();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        func_801E5988();
    }
}

MATCH void func_801F009C(void) {
    u8 timer;

    func_801F0274();
    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 96) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F0104(void) {
    u8 count;

    func_801F0274();
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x70) {
        func_801E5988();
    }
}

MATCH void func_801F0158(void) {
    u8 timer;

    func_801F08AC();
    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 16) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F01C0(void) {
    u8 count;

    func_801F08AC();
    count         = g_Task->timer - 1;
    g_Task->timer = count;
    if (count == 0) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F0224(void) {
    u8 count;

    func_801F08AC();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0274);

INCLUDE_ASM(func_801F04B0);

MATCH void func_801F078C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    switch (g_Task->facing) {
        case 0:
            rot.vy = 3072;
            break;
        case 1:
            rot.vx = 1024;
            break;
        case 2:
            rot.vy = 1024;
            break;
        case 3:
            rot.vx = 3072;
            break;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

MATCH void func_801F08AC(void) {
    PartyMember* work;
    u32          i;

    for (i = 0; i < 8; i++) {
        if (Battle_SlotIsBlocked((i + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK) != 0) {
            continue;
        }
        work                     = g_Task;
        work->facing             = g_BattleEnemyBattlers[i].unk_08;
        g_Task->pos.x.fixed      = g_BattleEnemyBattlers[i].pos.x.fixed;
        g_Task->pos.y.fixed      = g_BattleEnemyBattlers[i].pos.y.fixed;
        COORD_INT(g_Task->pos.z) = FIELD(u16, D_801EB66E, i * BATTLE_ENEMY_STRIDE);
        Effect_SetActorMatrix();
        func_801F0974();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F0974);

#include "overlays/bmagic/Effect_SetActorMatrix.h"
