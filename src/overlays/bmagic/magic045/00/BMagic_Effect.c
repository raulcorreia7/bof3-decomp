#include "magic045_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EEE58);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEEA4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEE8(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8DC + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EEF80);

INCLUDE_ASM(func_801EF118);

MATCH void func_801EF2B0(void) {
    s32          angle;
    s32          dz;
    u8           count;
    PartyMember* task;

    if (g_FrameCount & 0x1) {
        Actor_StepAnimLoop();
    }
    g_Task->unk_5D -= 6;
    g_Task->unk_5E -= 6;
    g_Task->unk_5F -= 6;
    g_Task->pos.x.fixed += (rsin(g_Task->unk_0C) << 13) >> 12;
    angle = (rcos(g_Task->unk_0C) << 13) >> 12;
    task  = g_Task;
    task->pos.y.fixed += angle;
    count        = task->unk_09 - 1;
    task->unk_09 = count;
    dz           = task->unk_14 + task->unk_20;
    task->unk_14 = dz;
    task->pos.z.part.integer += dz;
    if (count == 0) {
        g_Task->header.step++;
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF40C(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8EC + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF4A4(void) {
    s8 c                       = -0x40;
    g_Task->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.part.integer = g_BattleEffectBattler->pos.z.part.integer;
    g_Task->unk_25             = 0x1D;
    g_Task->unk_26             = 0;
    g_Task->scale.x            = 0x10000;
    g_Task->scale.y            = 0x10000;
    g_Task->unk_48             = 1;
    g_Task->unk_27             = 0xA0;
    g_Task->unk_28             = 0;
    g_Task->unk_24             = 4;
    g_Task->header.flags |= 0x20;
    g_Task->unk_5C      = 2;
    g_Task->unk_5D      = c;
    g_Task->unk_5E      = c;
    g_Task->unk_5F      = c;
    g_Task->unk_2A      = 0;
    g_Task->unk_29      = 4;
    g_Task->unk_2C.half = 0;
    g_Task->unk_2B      = 0;
    Actor_SelectScript(0U);
    g_Task->unk_09 = 0;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801EF608);

MATCH void func_801EF724(void) {
    PartyMember* work;

    if (g_FrameCount & 1) {
        Actor_StepAnimLoop();
    }
    g_Task->unk_5D -= 3;
    g_Task->unk_5E -= 3;
    g_Task->unk_5F -= 3;
    work                     = g_Task;
    work->pos.x.fixed        = FIELD(s32, D_801EC364, work->param.unk_0B * BATTLE_EFFECT_STRIDE);
    work->pos.y.fixed        = FIELD(s32, D_801EC368, work->param.unk_0B * BATTLE_EFFECT_STRIDE);
    COORD_INT(g_Task->pos.z) = Area_SampleHeight(work->pos.x.fixed, work->pos.y.fixed);
    if (FIELD(s16, D_801EC36E, g_Task->param.unk_0B * BATTLE_EFFECT_STRIDE) < COORD_INT(g_Task->pos.z)) {
        g_Task->pos.z.fixed = FIELD(s32, D_801EC36C, g_Task->param.unk_0B * BATTLE_EFFECT_STRIDE);
    }
    if (FIELD(u8, D_801EC332, g_Task->param.unk_0B * BATTLE_EFFECT_STRIDE) == 3) {
        g_Task->header.step += 1;
    }
}

MATCH void Effect_TickDownAndClear3(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}
