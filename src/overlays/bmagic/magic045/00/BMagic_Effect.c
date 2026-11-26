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
        SELF(PartyMember)->facing                       = g_BattleEffectBattler->facing;
        SELF(PartyMember)->pos.x                        = g_BattleEffectBattler->pos.x;
        SELF(PartyMember)->pos.y                        = g_BattleEffectBattler->pos.y;
        SELF(PartyMember)->pos.z                        = g_BattleEffectBattler->pos.z;
        first                                           = Battle_AllocEffect(1, 49);
        g_BattleEffects[first & BYTE_MASK].target.party = SELF(PartyMember);
        g_BattleEffects[first & BYTE_MASK].header.mode  = 0;
        slot                                            = Battle_AllocEffect(1, 49) & BYTE_MASK;
        g_BattleEffects[slot].target.party              = SELF(PartyMember);
        g_BattleEffects[slot].unk_0B                    = first;
        g_BattleEffects[slot].header.mode               = 1;
        g_GfxPalettePending                             = 1;
        BMAGIC_POINT_AT_PALETTE_ROW(dst, src, first);
        do {
            dst[first] = src[first] | PSX_COLOR_STP_BIT;
            first++;
        } while (first < 16);
        g_AreaPaletteCopy->rows[26].colors[0] = g_AreaPaletteArena->rows[26].colors[0];
        SELF(PartyMember)->param.unk_0B       = 2;
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EEEA4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEE8(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8DC + 1, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EEF80(void) {
    PartyMember* work;
    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    SELF(PartyMember)->unk_0C = 0x10000;
    SELF(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Self);
    SELF(PartyMember)->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed + SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed + SELF(PartyMember)->unk_10;
    COORD_INT(SELF(PartyMember)->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 0x100;
    SELF(PartyMember)->unk_25           = 0x1D;
    SELF(PartyMember)->unk_26           = 0;
    work                                = SELF(PartyMember);
    work->unk_48                        = 1;
    work->scale.x                       = 0x10000;
    work->scale.y                       = 0x10000;
    SELF(PartyMember)->unk_27           = 0xA0;
    SELF(PartyMember)->unk_28           = 0;
    SELF(PartyMember)->unk_24           = 4;
    SELF(PartyMember)->unk_5D           = 0;
    SELF(PartyMember)->unk_5E           = 0;
    SELF(PartyMember)->unk_5F           = 0;
    SELF(PartyMember)->unk_5C           = 0;
    SELF(PartyMember)->unk_2A           = 0;
    SELF(PartyMember)->unk_29           = 4;
    SELF(PartyMember)->unk_2C.value     = 0;
    SELF(PartyMember)->unk_2B           = 1;
    Script_Select(0);
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->header.step += 1;
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
        SELF(PartyMember)->header.flags |= 0x20;
        SELF(PartyMember)->unk_5C = 1;
        SELF(PartyMember)->unk_5D = 0;
        SELF(PartyMember)->unk_5E = 0;
        SELF(PartyMember)->unk_5F = 0;
        SELF(PartyMember)->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - SELF(PartyMember)->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - SELF(PartyMember)->pos.y.fixed);
        work                      = SELF(PartyMember);
        work->unk_14              = 0x40;
        work->unk_09              = 16;
        work->unk_20              = -8;
        SELF(PartyMember)->header.step += 1;
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
    SELF(PartyMember)->unk_5D -= 6;
    SELF(PartyMember)->unk_5E -= 6;
    SELF(PartyMember)->unk_5F -= 6;
    SELF(PartyMember)->pos.x.fixed += (rsin(SELF(PartyMember)->unk_0C) << 13) >> 12;
    angle = (rcos(SELF(PartyMember)->unk_0C) << 13) >> 12;
    task  = SELF(PartyMember);
    task->pos.y.fixed += angle;
    count        = task->unk_09 - 1;
    task->unk_09 = count;
    dz           = task->unk_14 + task->unk_20;
    task->unk_14 = dz;
    task->pos.z.part.integer += dz;
    if (count == 0) {
        SELF(PartyMember)->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"

MATCH void func_801EF40C(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8EC + 1, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF4A4(void) {
    s8 c                                  = -0x40;
    SELF(PartyMember)->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->pos.z.part.integer = g_BattleEffectBattler->pos.z.part.integer;
    SELF(PartyMember)->unk_25             = 0x1D;
    SELF(PartyMember)->unk_26             = 0;
    SELF(PartyMember)->scale.x            = 0x10000;
    SELF(PartyMember)->scale.y            = 0x10000;
    SELF(PartyMember)->unk_48             = 1;
    SELF(PartyMember)->unk_27             = 0xA0;
    SELF(PartyMember)->unk_28             = 0;
    SELF(PartyMember)->unk_24             = 4;
    SELF(PartyMember)->header.flags |= 0x20;
    SELF(PartyMember)->unk_5C       = 2;
    SELF(PartyMember)->unk_5D       = c;
    SELF(PartyMember)->unk_5E       = c;
    SELF(PartyMember)->unk_5F       = c;
    SELF(PartyMember)->unk_2A       = 0;
    SELF(PartyMember)->unk_29       = 4;
    SELF(PartyMember)->unk_2C.value = 0;
    SELF(PartyMember)->unk_2B       = 0;
    Script_Select(0U);
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF608(void) {
    s32 y;

    Script_AnimStepLoop();
    SELF(PartyMember)->pos.x.fixed        = g_BattleEffects[SELF(PartyMember)->param.unk_0B].pos.x.fixed;
    y                                     = g_BattleEffects[SELF(PartyMember)->param.unk_0B].pos.y.fixed;
    SELF(PartyMember)->pos.y.fixed        = y;
    SELF(PartyMember)->pos.z.part.integer = Area_HeightSample(SELF(PartyMember)->pos.x.fixed, y);
    if (g_BattleEffects[SELF(PartyMember)->param.unk_0B].pos.z.part.integer < SELF(PartyMember)->pos.z.part.integer) {
        SELF(PartyMember)->pos.z.fixed = g_BattleEffects[SELF(PartyMember)->param.unk_0B].pos.z.fixed;
    }
    if (g_BattleEffects[SELF(PartyMember)->param.unk_0B].header.step == 2) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF724(void) {
    PartyMember* work;

    if (g_FrameCount & 1) {
        Script_AnimStepLoop();
    }
    SELF(PartyMember)->unk_5D -= 3;
    SELF(PartyMember)->unk_5E -= 3;
    SELF(PartyMember)->unk_5F -= 3;
    work                                = SELF(PartyMember);
    work->pos.x.fixed                   = g_BattleEffects[work->param.unk_0B].pos.x.fixed;
    work->pos.y.fixed                   = g_BattleEffects[work->param.unk_0B].pos.y.fixed;
    COORD_INT(SELF(PartyMember)->pos.z) = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);
    if (g_BattleEffects[SELF(PartyMember)->param.unk_0B].pos.z.part.integer < COORD_INT(SELF(PartyMember)->pos.z)) {
        SELF(PartyMember)->pos.z.fixed = g_BattleEffects[SELF(PartyMember)->param.unk_0B].pos.z.fixed;
    }
    if (g_BattleEffects[SELF(PartyMember)->param.unk_0B].header.step == 3) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void Effect_TickDownAndClear3(void) {
    EFFECT_TICK_DOWN_AND_CLEAR();
}
