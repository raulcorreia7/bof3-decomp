#include "magic045_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EEE58);
}

MATCH void func_801EEC5C(void) {
    u8   first;
    u16* dst;
    u16* src;
    u32  slot;

    if ((g_Battle.target_selector < BATTLE_PARTY_CHARACTERS_COUNT && g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) ||
        (g_Battle.target_selector >= BATTLE_PARTY_CHARACTERS_COUNT && g_Battle.active_battler >= BATTLE_PARTY_CHARACTERS_COUNT)) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    } else {
        BMAGIC_WORK->facing                             = g_BattleEffectBattler->facing;
        BMAGIC_WORK->pos.x                              = g_BattleEffectBattler->pos.x;
        BMAGIC_WORK->pos.y                              = g_BattleEffectBattler->pos.y;
        BMAGIC_WORK->pos.z                              = g_BattleEffectBattler->pos.z;
        first                                           = Battle_AllocEffect(1, 0x31);
        g_BattleEffects[first & BYTE_MASK].target.party = g_Task;
        g_BattleEffects[first & BYTE_MASK].header.mode  = 0;
        slot                                            = Battle_AllocEffect(1, 0x31) & BYTE_MASK;
        g_BattleEffects[slot].target.party              = g_Task;
        g_BattleEffects[slot].unk_0B                    = first;
        g_BattleEffects[slot].header.mode               = 1;
        g_GfxPalettePending                             = 1;
        BMAGIC_POINT_AT_PALETTE_ROW(dst, src, first);
        do {
            dst[first] = src[first] | PSX_COLOR_STP_BIT;
            first++;
        } while (first < 16);
        g_AreaPaletteCopy->rows[26].colors[0] = g_AreaPaletteArena->rows[26].colors[0];
        BMAGIC_WORK->param.unk_0B             = 2;
        BMAGIC_WORK->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EEEA4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEE8(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8DC + 1, BMAGIC_WORK->header.step);
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EEF80(void) {
    PartyMember* work;
    BMAGIC_WORK->facing = g_BattleEffectBattler->facing;
    BMAGIC_WORK->unk_0C = 0x10000;
    BMAGIC_WORK->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    BMAGIC_WORK->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed + BMAGIC_WORK->unk_0C;
    BMAGIC_WORK->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed + BMAGIC_WORK->unk_10;
    COORD_INT(BMAGIC_WORK->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 0x100;
    BMAGIC_WORK->unk_25           = 0x1D;
    BMAGIC_WORK->unk_26           = 0;
    work                          = g_Task;
    work->unk_48                  = 1;
    work->scale.x                 = 0x10000;
    work->scale.y                 = 0x10000;
    BMAGIC_WORK->unk_27           = 0xA0;
    BMAGIC_WORK->unk_28           = 0;
    BMAGIC_WORK->unk_24           = 4;
    BMAGIC_WORK->unk_5D           = 0;
    BMAGIC_WORK->unk_5E           = 0;
    BMAGIC_WORK->unk_5F           = 0;
    BMAGIC_WORK->unk_5C           = 0;
    BMAGIC_WORK->unk_2A           = 0;
    BMAGIC_WORK->unk_29           = 4;
    BMAGIC_WORK->unk_2C.value     = 0;
    BMAGIC_WORK->unk_2B           = 1;
    Script_Select(0);
    BMAGIC_WORK->unk_09 = 0;
    BMAGIC_WORK->header.step += 1;
}

MATCH void func_801EF118(void) {
    PartyMember** selected;
    PartyMember*  work;
    VECTOR        pos;
    u16*          flags;

    Script_AnimStepLoop();
    selected = &g_Battle.selected_actor;
    setVector(&pos, ((*selected)->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, ((*selected)->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, (COORD_INT((*selected)->pos.z) + 0xC0) >> 1);
    Battle_StepRangeToward(pos, 0x30);
    if (func_800AF66C(*selected, 0x8000)) {
        BATTLE_RAISE_STATE(BATTLE_STATE_DAMAGE_APPLIED);
        Battle_MarkDamaged(g_Battle.target_selector);
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_AREA, 0x03));
        BMAGIC_WORK->header.flags |= 0x20;
        BMAGIC_WORK->unk_5C = 1;
        BMAGIC_WORK->unk_5D = 0;
        BMAGIC_WORK->unk_5E = 0;
        BMAGIC_WORK->unk_5F = 0;
        BMAGIC_WORK->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - BMAGIC_WORK->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - BMAGIC_WORK->pos.y.fixed);
        work                = g_Task;
        work->unk_14        = 0x40;
        work->unk_09        = 16;
        work->unk_20        = -8;
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void func_801EF2B0(void) {
    s32          angle;
    s32          dz;
    u8           count;
    PartyMember* task;

    if (g_FrameCount & 0x1) {
        Script_AnimStepLoop();
    }
    BMAGIC_WORK->unk_5D -= 6;
    BMAGIC_WORK->unk_5E -= 6;
    BMAGIC_WORK->unk_5F -= 6;
    BMAGIC_WORK->pos.x.fixed += (rsin(BMAGIC_WORK->unk_0C) << 13) >> 12;
    angle = (rcos(BMAGIC_WORK->unk_0C) << 13) >> 12;
    task  = g_Task;
    task->pos.y.fixed += angle;
    count        = task->unk_09 - 1;
    task->unk_09 = count;
    dz           = task->unk_14 + task->unk_20;
    task->unk_14 = dz;
    task->pos.z.part.integer += dz;
    if (count == 0) {
        BMAGIC_WORK->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"

MATCH void func_801EF40C(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8EC + 1, BMAGIC_WORK->header.step);
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF4A4(void) {
    s8 c                            = -0x40;
    BMAGIC_WORK->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed;
    BMAGIC_WORK->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed;
    BMAGIC_WORK->pos.z.part.integer = g_BattleEffectBattler->pos.z.part.integer;
    BMAGIC_WORK->unk_25             = 0x1D;
    BMAGIC_WORK->unk_26             = 0;
    BMAGIC_WORK->scale.x            = 0x10000;
    BMAGIC_WORK->scale.y            = 0x10000;
    BMAGIC_WORK->unk_48             = 1;
    BMAGIC_WORK->unk_27             = 0xA0;
    BMAGIC_WORK->unk_28             = 0;
    BMAGIC_WORK->unk_24             = 4;
    BMAGIC_WORK->header.flags |= 0x20;
    BMAGIC_WORK->unk_5C       = 2;
    BMAGIC_WORK->unk_5D       = c;
    BMAGIC_WORK->unk_5E       = c;
    BMAGIC_WORK->unk_5F       = c;
    BMAGIC_WORK->unk_2A       = 0;
    BMAGIC_WORK->unk_29       = 4;
    BMAGIC_WORK->unk_2C.value = 0;
    BMAGIC_WORK->unk_2B       = 0;
    Script_Select(0U);
    BMAGIC_WORK->unk_09 = 0;
    BMAGIC_WORK->header.step += 1;
}

MATCH void func_801EF608(void) {
    s32 y;

    Script_AnimStepLoop();
    BMAGIC_WORK->pos.x.fixed        = g_BattleEffects[BMAGIC_WORK->param.unk_0B].pos.x.fixed;
    y                               = g_BattleEffects[BMAGIC_WORK->param.unk_0B].pos.y.fixed;
    BMAGIC_WORK->pos.y.fixed        = y;
    BMAGIC_WORK->pos.z.part.integer = Area_HeightSample(BMAGIC_WORK->pos.x.fixed, y);
    if (g_BattleEffects[BMAGIC_WORK->param.unk_0B].pos.z.part.integer < BMAGIC_WORK->pos.z.part.integer) {
        BMAGIC_WORK->pos.z.fixed = g_BattleEffects[BMAGIC_WORK->param.unk_0B].pos.z.fixed;
    }
    if (g_BattleEffects[BMAGIC_WORK->param.unk_0B].header.step == 2) {
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void func_801EF724(void) {
    PartyMember* work;

    if (g_FrameCount & 1) {
        Script_AnimStepLoop();
    }
    BMAGIC_WORK->unk_5D -= 3;
    BMAGIC_WORK->unk_5E -= 3;
    BMAGIC_WORK->unk_5F -= 3;
    work                          = g_Task;
    work->pos.x.fixed             = g_BattleEffects[work->param.unk_0B].pos.x.fixed;
    work->pos.y.fixed             = g_BattleEffects[work->param.unk_0B].pos.y.fixed;
    COORD_INT(BMAGIC_WORK->pos.z) = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);
    if (g_BattleEffects[BMAGIC_WORK->param.unk_0B].pos.z.part.integer < COORD_INT(BMAGIC_WORK->pos.z)) {
        BMAGIC_WORK->pos.z.fixed = g_BattleEffects[BMAGIC_WORK->param.unk_0B].pos.z.fixed;
    }
    if (g_BattleEffects[BMAGIC_WORK->param.unk_0B].header.step == 3) {
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void Effect_TickDownAndClear3(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}
