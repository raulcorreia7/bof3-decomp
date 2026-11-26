#include "magic173_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* BMagic_IntimidateUpdate */
/* func_801EEC04 */
MATCH void BMagic_IntimidateUpdate(void) {
    Callback handlers[2] = {BMagic_IntimidateInit, Effect_MarkDamagedOnZeroTick};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

/* func_801EEC5C */
MATCH void BMagic_IntimidateInit(void) {
    u32          i;
    u8           slot;
    PartyMember* task;
    PartyMember* work;
    u16*         src;
    u16*         dst;

    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    task                      = TASK(PartyMember);
    WorldPos_Copy(&task->pos, &g_BattleEffectBattler->pos);
    task->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
    for (i = 0; i < 2; i++) {
        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_INTIMIDATE);
        work                               = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].target.party = work;
        TASK(PartyMember)->param.unk_0B += 1;
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < AREA_PALETTE_COLORS; i++) {
        *dst++ = *src++;
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEDF0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EEE34 */
MATCH void BMagic_IntimidateStreakUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicIntimidateStreakSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->unk_04 != 0) {
        if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
            BMagic_IntimidateDrawStreakNarrow();
        }
    } else {
        if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
            BMagic_IntimidateDrawStreakWide();
        }
    }
}

/* func_801EEEEC */
MATCH void BMagic_IntimidateStreakPlace(void) {
    PartyMember* target;
    u8           battler;
    u8           type;
    PartyMember* work;

    target                    = g_Battle.selected_actor;
    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    battler                   = g_Battle.active_battler;
    if (battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        TASK(PartyMember)->unk_0C = 0x4000;
        TASK(PartyMember)->unk_10 = 0;
        TASK(PartyMember)->unk_14 = 0xC00000;
    } else {
        type = g_BattleEnemyBattlers[battler - BATTLE_PARTY_CHARACTERS_COUNT].enemy_id.byte.type;
        switch (type) {
            case 0x61:
                TASK(PartyMember)->unk_0C = 0x38000;
                TASK(PartyMember)->unk_10 = 0;
                TASK(PartyMember)->unk_14 = 0;
                break;
            case 0x6C:
                work = TASK(PartyMember);
                if (work->facing & 2) {
                    work->unk_0C = 0x20000;
                } else {
                    work->unk_0C = 0x30000;
                }
                work->unk_10 = 0;
                work->unk_14 = 0x800000;
                break;
            default:
                TASK(PartyMember)->unk_0C = 0x10000;
                TASK(PartyMember)->unk_10 = 0;
                TASK(PartyMember)->unk_14 = 0x800000;
                break;
        }
    }
    Effect_RotatePosition(g_Task);
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + TASK(PartyMember)->unk_10;
    TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TASK(PartyMember)->unk_14;
    TASK(PartyMember)->unk_0C      = ratan2(target->pos.x.fixed - TASK(PartyMember)->pos.x.fixed, target->pos.y.fixed - TASK(PartyMember)->pos.y.fixed);
    TASK(PartyMember)->unk_10      = 0;
    Battle_ProjectRange();
    BMagic_Trail[TASK(PartyMember)->unk_04][0].vx = TASK(PartyMember)->screen_x.value;
    BMagic_Trail[TASK(PartyMember)->unk_04][0].vy = TASK(PartyMember)->screen_y.value;
    BMagic_Trail[TASK(PartyMember)->unk_04][1].vx = TASK(PartyMember)->screen_x.value;
    BMagic_Trail[TASK(PartyMember)->unk_04][1].vy = TASK(PartyMember)->screen_y.value;
    TASK(PartyMember)->param.unk_0B               = 0;
    TASK(PartyMember)->unk_09                     = 16;
    TASK(PartyMember)->timer                      = 1;
    TASK(PartyMember)->header.step++;
}

/* func_801EF148 */
MATCH void BMagic_IntimidateStreakFly(void) {
    VECTOR       pos;
    PartyMember* target;
    PartyMember* battler;
    s32          diff;
    u32          slot;
    u8           count;

    count = TASK(PartyMember)->timer;
    if (count < 8) {
        TASK(PartyMember)->timer = count + 1;
    }
    target = g_Battle.selected_actor;
    setVector(&pos, (target->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (target->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, (target->pos.z.fixed + 0x800000) >> 17);
    Battle_StepRangeToward(pos, 0xC0);
    TASK(PartyMember)->unk_10 = TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->unk_0C = ratan2(target->pos.x.fixed - TASK(PartyMember)->pos.x.fixed, target->pos.y.fixed - TASK(PartyMember)->pos.y.fixed);
    if (func_800AF66C((BattleRange*)target, 0x8000) != 0) {
        TASK(PartyMember)->pos.x.fixed = target->pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed = target->pos.y.fixed;
        TASK(PartyMember)->header.step++;
    } else {
        diff                      = (TASK(PartyMember)->unk_10 & ANGLE_MASK) - (TASK(PartyMember)->unk_0C & ANGLE_MASK);
        TASK(PartyMember)->unk_10 = diff;
        if (diff < 0) {
            TASK(PartyMember)->unk_10 = ~diff + 1;
        }
        if ((u32)(TASK(PartyMember)->unk_10 - 0x601) < 0x3FF) {
            TASK(PartyMember)->pos.x.fixed = target->pos.x.fixed;
            TASK(PartyMember)->pos.y.fixed = target->pos.y.fixed;
            TASK(PartyMember)->header.step++;
        }
    }
    Battle_ProjectRange();
    Effect_RecordTrail();
    if (TASK(PartyMember)->header.step != 1 && TASK(PartyMember)->unk_04 == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    }
    if (TASK(PartyMember)->header.step == 2) {
        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_INTIMIDATE) & BYTE_MASK;
        battler                            = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = battler;
        g_BattleEffects[slot].pos.x.fixed  = TASK(PartyMember)->pos.x.fixed;
        g_BattleEffects[slot].pos.y.fixed  = TASK(PartyMember)->pos.y.fixed;
        g_BattleEffects[slot].pos.z.fixed  = TASK(PartyMember)->pos.z.fixed;
        g_BattleEffectBattler->param.unk_0B++;
    }
}

/* func_801EF3D8 */
MATCH void BMagic_IntimidateStreakSlide(void) {
    u8 timer;

    if (TASK(PartyMember)->timer < 8U) {
        TASK(PartyMember)->param.unk_0B += 1;
        TASK(PartyMember)->timer += 1;
        Battle_ProjectRange();
        Effect_RecordTrail();
    }
    timer = TASK(PartyMember)->timer;
    if ((timer & BYTE_MASK) == 8) {
        TASK(PartyMember)->unk_09 = timer;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EF484 */
#include "overlays/bmagic/shared/Effect_EndTrail.h"

/* func_801EF4EC */
MATCH void BMagic_IntimidateDrawStreakNarrow(void) {
    POLY_G4* prim;
    s32      tpage;
    s32      i;
    s32      next;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    i = TASK(PartyMember)->param.unk_0B;
    while (BMagic_Trail[TASK(PartyMember)->unk_04][i].vx == -1) {
        i++;
    }
    g_ScratchPad.cells.halves[0] = 2;
    next                         = i + 1;
    g_ScratchPad.cells.halves[6] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vx;
    g_ScratchPad.cells.halves[7] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vy;
    g_ScratchPad.cells.halves[4] = BMagic_Trail[TASK(PartyMember)->unk_04][next].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[TASK(PartyMember)->unk_04][next].vy;
    g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
    g_ScratchPad.cells.halves[4] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vy;
    for (i = next; i < TASK(PartyMember)->timer; i++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[4] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vx;
        g_ScratchPad.cells.halves[5] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vy;
        prim                         = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + 0x400) & ANGLE_MASK;
        setXY0(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
               g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] - 0x400) & ANGLE_MASK;
        prim->x2                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y2                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + 0x400) & ANGLE_MASK;
        prim->x1                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] - 0x400) & ANGLE_MASK;
        prim->x3                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y3                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPad.cells.halves[3] = 0x61 - (i - 1) * 12;
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], 1);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], 1);
        g_ScratchPad.cells.halves[3] = 0x61 - i * 12;
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], 1);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

/* func_801EFA34 */
MATCH void BMagic_IntimidateDrawStreakWide(void) {
    POLY_G4* prim;
    s32      tpage;
    s32      i;
    s32      next;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = 0xC;
    i                            = TASK(PartyMember)->param.unk_0B;
    while (BMagic_Trail[TASK(PartyMember)->unk_04][i].vx == -1) {
        i++;
    }
    next                         = i + 1;
    g_ScratchPad.cells.halves[6] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vx;
    g_ScratchPad.cells.halves[7] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vy;
    g_ScratchPad.cells.halves[4] = BMagic_Trail[TASK(PartyMember)->unk_04][next].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[TASK(PartyMember)->unk_04][next].vy;
    g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
    g_ScratchPad.cells.halves[4] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vy;
    for (i = next; i < TASK(PartyMember)->timer; i++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[4] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vx;
        g_ScratchPad.cells.halves[5] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vy;
        prim                         = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + 0x400) & ANGLE_MASK;
        setXY0(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
               g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        prim->x2                     = g_ScratchPad.cells.halves[6];
        prim->y2                     = g_ScratchPad.cells.halves[7];
        g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + 0x400) & ANGLE_MASK;
        prim->x1                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x3                     = g_ScratchPad.cells.halves[4];
        prim->y3                     = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[3] = 0x61 - (i - 1) * 12;
        setRGB0(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        g_ScratchPad.cells.halves[3] = 0x61 - i * 12;
        setRGB1(prim, 1, 1, 1);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    }
    i = TASK(PartyMember)->param.unk_0B;
    while (BMagic_Trail[TASK(PartyMember)->unk_04][i].vx == -1) {
        i++;
    }
    next                         = i + 1;
    g_ScratchPad.cells.halves[6] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vx;
    g_ScratchPad.cells.halves[7] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vy;
    g_ScratchPad.cells.halves[4] = BMagic_Trail[TASK(PartyMember)->unk_04][next].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[TASK(PartyMember)->unk_04][next].vy;
    g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
    g_ScratchPad.cells.halves[4] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vy;
    for (i = next; i < TASK(PartyMember)->timer; i++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[4] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vx;
        g_ScratchPad.cells.halves[5] = BMagic_Trail[TASK(PartyMember)->unk_04][i].vy;
        prim                         = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] - 0x400) & ANGLE_MASK;
        setXY0(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
               g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        prim->x2                     = g_ScratchPad.cells.halves[6];
        prim->y2                     = g_ScratchPad.cells.halves[7];
        g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] - 0x400) & ANGLE_MASK;
        prim->x1                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x3                     = g_ScratchPad.cells.halves[4];
        prim->y3                     = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[3] = 0x81 - ((i - 1) << 4);
        setRGB0(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        g_ScratchPad.cells.halves[3] = 0x81 - (i << 4);
        setRGB1(prim, 1, 1, 1);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

/* func_801F02B0 */
#include "overlays/bmagic/shared/Effect_RecordTrail.h"

/* func_801F03A0 */
#include "overlays/bmagic/shared/Effect_ClearTrail.h"

/* func_801F0488 */
MATCH void BMagic_IntimidateImpactUpdate(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(g_BMagicIntimidateImpactSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Battle_ProjectRange();
        BMagic_IntimidateDrawImpactBurst();
        if (TASK(PartyMember)->header.step < 3) {
            Area_AddGridActor();
        }
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

/* func_801F0540 */
MATCH void BMagic_IntimidateImpactPlace(void) {
    TASK(PartyMember)->unk_25       = 0x1D;
    TASK(PartyMember)->unk_26       = 0;
    TASK(PartyMember)->unk_27       = 0xA0;
    TASK(PartyMember)->unk_28       = 0;
    TASK(PartyMember)->unk_24       = 4;
    TASK(PartyMember)->unk_5D       = 0;
    TASK(PartyMember)->unk_5E       = 0;
    TASK(PartyMember)->unk_5F       = 0;
    TASK(PartyMember)->unk_5C       = 0;
    TASK(PartyMember)->unk_2A       = 0;
    TASK(PartyMember)->unk_29       = 3;
    TASK(PartyMember)->unk_2C.value = 0;
    TASK(PartyMember)->unk_2B       = 1;
    Script_Select(0U);
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->header.step += 1;
}

/* func_801F0648 */
MATCH void BMagic_IntimidateImpactRise(void) {
    u8 timer;

    Script_AnimStepOnce();
    timer                     = TASK(PartyMember)->unk_09 + 4;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 16) {
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

/* func_801F06B0 */
MATCH void BMagic_IntimidateImpactPlay(void) {
    Script_AnimStepOnce();
    if (Script_AnimStepOnce() != 0u) {
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

/* func_801F075C */
MATCH void BMagic_IntimidateDrawImpactBurst(void) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = (rand() & 3) + 28;
    g_ScratchPad.cells.halves[3] = TASK(PartyMember)->unk_09 * 6;
    for (i = 0; i < 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, TASK(PartyMember)->screen_x.value, TASK(PartyMember)->screen_y.value, TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]),
               TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]),
               TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin((i + 1) << 9), g_ScratchPad.cells.halves[0]),
               TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos((i + 1) << 9), g_ScratchPad.cells.halves[0]));
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));
    }
}
