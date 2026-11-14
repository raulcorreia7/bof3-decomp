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

MATCH void func_801EF118(void) {
    PartyMember** selected;
    PartyMember*  work;
    VECTOR        pos;
    u16*          flags;

    Actor_StepAnimLoop();
    selected = &g_Battle.selected_actor;
    pos.vx   = ((*selected)->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vy   = ((*selected)->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vz   = (COORD_INT((*selected)->pos.z) + 0xC0) >> 1;
    func_800AF3A0(pos, 0x30);
    if (func_800AF66C(*selected, 0x8000)) {
        BATTLE_RAISE_STATE(BATTLE_STATE_DAMAGE_APPLIED);
        Battle_MarkDamaged(g_Battle.target_selector);
        SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_AREA, 0x03));
        g_Task->header.flags |= 0x20;
        g_Task->unk_5C = 1;
        g_Task->unk_5D = 0;
        g_Task->unk_5E = 0;
        g_Task->unk_5F = 0;
        g_Task->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - g_Task->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - g_Task->pos.y.fixed);
        work           = g_Task;
        work->unk_14   = 0x40;
        work->unk_09   = 16;
        work->unk_20   = -8;
        g_Task->header.step += 1;
    }
}

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

MATCH void func_801EF608(void) {
    s32 y;

    Actor_StepAnimLoop();
    g_Task->pos.x.fixed        = g_BattleEffects[g_Task->param.unk_0B].pos.x.fixed;
    y                          = g_BattleEffects[g_Task->param.unk_0B].pos.y.fixed;
    g_Task->pos.y.fixed        = y;
    g_Task->pos.z.part.integer = Area_SampleHeight(g_Task->pos.x.fixed, y);
    if (g_BattleEffects[g_Task->param.unk_0B].pos.z.part.integer < g_Task->pos.z.part.integer) {
        g_Task->pos.z.fixed = g_BattleEffects[g_Task->param.unk_0B].pos.z.fixed;
    }
    if (g_BattleEffects[g_Task->param.unk_0B].header.step == 2) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF724(void) {
    PartyMember* work;

    if (g_FrameCount & 1) {
        Actor_StepAnimLoop();
    }
    g_Task->unk_5D -= 3;
    g_Task->unk_5E -= 3;
    g_Task->unk_5F -= 3;
    work                     = g_Task;
    work->pos.x.fixed        = g_BattleEffects[work->param.unk_0B].pos.x.fixed;
    work->pos.y.fixed        = g_BattleEffects[work->param.unk_0B].pos.y.fixed;
    COORD_INT(g_Task->pos.z) = Area_SampleHeight(work->pos.x.fixed, work->pos.y.fixed);
    if (g_BattleEffects[g_Task->param.unk_0B].pos.z.part.integer < COORD_INT(g_Task->pos.z)) {
        g_Task->pos.z.fixed = g_BattleEffects[g_Task->param.unk_0B].pos.z.fixed;
    }
    if (g_BattleEffects[g_Task->param.unk_0B].header.step == 3) {
        g_Task->header.step += 1;
    }
}

MATCH void Effect_TickDownAndClear3(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}
