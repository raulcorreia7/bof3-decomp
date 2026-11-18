#include "magic173_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED90};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EEC5C(void) {
    u32          i;
    u8           slot;
    PartyMember* task;
    PartyMember* work;
    u16*         src;
    u16*         dst;

    g_Task->facing = g_BattleEffectBattler->facing;
    task           = g_Task;
    WorldPos_Copy(&task->pos, &g_BattleEffectBattler->pos);
    task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 2; i++) {
        slot                               = Battle_AllocEffect(1, 24);
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < AREA_PALETTE_COLORS; i++) {
        *dst++ = *src++;
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionSE(EMI_SE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEDF0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE34(void) {
    SYS_DISPATCH_BYTE(D_801F0990, g_Task->header.step);
    if (g_Task->unk_04 != 0) {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EF4EC();
        }
    } else {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EFA34();
        }
    }
}

MATCH void func_801EEEEC(void) {
    PartyMember* target;
    u8           battler;
    u8           kind;
    PartyMember* work;

    target         = g_Battle.selected_actor;
    g_Task->facing = g_BattleEffectBattler->facing;
    battler        = g_Battle.active_battler;
    if (battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        g_Task->unk_0C = 0x4000;
        g_Task->unk_10 = 0;
        g_Task->unk_14 = 0xC00000;
    } else {
        kind = g_BattleEnemyBattlers[battler - BATTLE_PARTY_CHARACTERS_COUNT].enemy_id.byte.type;
        switch (kind) {
            case 0x61:
                g_Task->unk_0C = 0x38000;
                g_Task->unk_10 = 0;
                g_Task->unk_14 = 0;
                break;
            case 0x6C:
                work = g_Task;
                if (work->facing & 2) {
                    work->unk_0C = 0x20000;
                } else {
                    work->unk_0C = 0x30000;
                }
                work->unk_10 = 0;
                work->unk_14 = 0x800000;
                break;
            default:
                g_Task->unk_0C = 0x10000;
                g_Task->unk_10 = 0;
                g_Task->unk_14 = 0x800000;
                break;
        }
    }
    Effect_RotatePosition(g_Task);
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + g_Task->unk_14;
    g_Task->unk_0C      = ratan2(target->pos.x.fixed - g_Task->pos.x.fixed, target->pos.y.fixed - g_Task->pos.y.fixed);
    g_Task->unk_10      = 0;
    Battle_ProjectRange();
    BMagic_Trail[g_Task->unk_04][0].vx = g_Task->unk_2E.value;
    BMagic_Trail[g_Task->unk_04][0].vy = g_Task->unk_30.value;
    BMagic_Trail[g_Task->unk_04][1].vx = g_Task->unk_2E.value;
    BMagic_Trail[g_Task->unk_04][1].vy = g_Task->unk_30.value;
    g_Task->param.unk_0B               = 0;
    g_Task->unk_09                     = 16;
    g_Task->timer                      = 1;
    g_Task->header.step++;
}

MATCH void func_801EF148(void) {
    VECTOR       pos;
    PartyMember* target;
    PartyMember* battler;
    s32          diff;
    u32          slot;
    u8           count;

    count = g_Task->timer;
    if (count < 8) {
        g_Task->timer = count + 1;
    }
    target = g_Battle.selected_actor;
    setVector(&pos, (target->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (target->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, (target->pos.z.fixed + 0x800000) >> 17);
    Battle_StepRangeToward(pos, 0xC0);
    g_Task->unk_10 = g_Task->unk_0C;
    g_Task->unk_0C = ratan2(target->pos.x.fixed - g_Task->pos.x.fixed, target->pos.y.fixed - g_Task->pos.y.fixed);
    if (func_800AF66C((BattleRange*)target, 0x8000) != 0) {
        g_Task->pos.x.fixed = target->pos.x.fixed;
        g_Task->pos.y.fixed = target->pos.y.fixed;
        g_Task->header.step++;
    } else {
        diff           = (g_Task->unk_10 & ANGLE_MASK) - (g_Task->unk_0C & ANGLE_MASK);
        g_Task->unk_10 = diff;
        if (diff < 0) {
            g_Task->unk_10 = ~diff + 1;
        }
        if ((u32)(g_Task->unk_10 - 0x601) < 0x3FF) {
            g_Task->pos.x.fixed = target->pos.x.fixed;
            g_Task->pos.y.fixed = target->pos.y.fixed;
            g_Task->header.step++;
        }
    }
    Battle_ProjectRange();
    Effect_RecordTrail();
    if (g_Task->header.step != 1 && g_Task->unk_04 == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    }
    if (g_Task->header.step == 2) {
        slot                               = Battle_AllocEffect(1, 24) & BYTE_MASK;
        battler                            = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = battler;
        g_BattleEffects[slot].pos.x.fixed  = g_Task->pos.x.fixed;
        g_BattleEffects[slot].pos.y.fixed  = g_Task->pos.y.fixed;
        g_BattleEffects[slot].pos.z.fixed  = g_Task->pos.z.fixed;
        g_BattleEffectBattler->param.unk_0B++;
    }
}

MATCH void func_801EF3D8(void) {
    u8 timer;

    if (g_Task->timer < 8U) {
        g_Task->param.unk_0B += 1;
        g_Task->timer += 1;
        Battle_ProjectRange();
        Effect_RecordTrail();
    }
    timer = g_Task->timer;
    if ((timer & BYTE_MASK) == 8) {
        g_Task->unk_09 = timer;
        g_Task->header.step += 1;
    }
}

/* func_801EF484 */
#include "overlays/bmagic/Effect_EndTrail.h"

/* Draws the trail as a ribbon of POLY_G4 quads two units wide either side of each segment heading, from the first
 * recorded point to the effect timer, the shade falling by 12 per segment. */
MATCH void func_801EF4EC(void) {
    POLY_G4* prim;
    s32      tpage;
    s32      i;
    s32      next;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    i = g_Task->param.unk_0B;
    while (BMagic_Trail[g_Task->unk_04][i].vx == -1) {
        i++;
    }
    g_ScratchPad.cells.halves[0] = 2;
    next                         = i + 1;
    g_ScratchPad.cells.halves[6] = BMagic_Trail[g_Task->unk_04][i].vx;
    g_ScratchPad.cells.halves[7] = BMagic_Trail[g_Task->unk_04][i].vy;
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][next].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][next].vy;
    g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][i].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][i].vy;
    for (i = next; i < g_Task->timer; i++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][i].vx;
        g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][i].vy;
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

/* Draws the trail as a ribbon twelve units wide in two passes, one side of the centreline each: the outer edge near
 * black, the centreline shaded 0x61 falling by 12 per segment on one side and 0x81 falling by 16 on the other. */
MATCH void func_801EFA34(void) {
    POLY_G4* prim;
    s32      tpage;
    s32      i;
    s32      next;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = 0xC;
    i                            = g_Task->param.unk_0B;
    while (BMagic_Trail[g_Task->unk_04][i].vx == -1) {
        i++;
    }
    next                         = i + 1;
    g_ScratchPad.cells.halves[6] = BMagic_Trail[g_Task->unk_04][i].vx;
    g_ScratchPad.cells.halves[7] = BMagic_Trail[g_Task->unk_04][i].vy;
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][next].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][next].vy;
    g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][i].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][i].vy;
    for (i = next; i < g_Task->timer; i++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][i].vx;
        g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][i].vy;
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
    i = g_Task->param.unk_0B;
    while (BMagic_Trail[g_Task->unk_04][i].vx == -1) {
        i++;
    }
    next                         = i + 1;
    g_ScratchPad.cells.halves[6] = BMagic_Trail[g_Task->unk_04][i].vx;
    g_ScratchPad.cells.halves[7] = BMagic_Trail[g_Task->unk_04][i].vy;
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][next].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][next].vy;
    g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][i].vx;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][i].vy;
    for (i = next; i < g_Task->timer; i++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][i].vx;
        g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][i].vy;
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
#include "overlays/bmagic/Effect_RecordTrail.h"

/* func_801F03A0 */
#include "overlays/bmagic/Effect_ClearTrail.h"

MATCH void func_801F0488(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F09A0, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Battle_ProjectRange();
        func_801F075C();
        if (g_Task->header.step < 3) {
            Area_AddGridActor();
        }
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801F0540(void) {
    g_Task->unk_25       = 0x1D;
    g_Task->unk_26       = 0;
    g_Task->unk_27       = 0xA0;
    g_Task->unk_28       = 0;
    g_Task->unk_24       = 4;
    g_Task->unk_5D       = 0;
    g_Task->unk_5E       = 0;
    g_Task->unk_5F       = 0;
    g_Task->unk_5C       = 0;
    g_Task->unk_2A       = 0;
    g_Task->unk_29       = 3;
    g_Task->unk_2C.value = 0;
    g_Task->unk_2B       = 1;
    Actor_SelectScript(0U);
    g_Task->unk_09 = 0;
    g_Task->header.step += 1;
}

MATCH void func_801F0648(void) {
    u8 timer;

    Actor_StepAnimOnce();
    timer          = g_Task->unk_09 + 4;
    g_Task->unk_09 = timer;
    if (timer == 16) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F06B0(void) {
    Actor_StepAnimOnce();
    if (Actor_StepAnimOnce() != 0u) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

MATCH void func_801F075C(void) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = (rand() & 3) + 28;
    g_ScratchPad.cells.halves[3] = g_Task->unk_09 * 6;
    for (i = 0; i < 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, g_Task->unk_2E.value, g_Task->unk_30.value, g_Task->unk_2E.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]),
               g_Task->unk_30.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]), g_Task->unk_2E.value + FIXED_MUL(rsin((i + 1) << 9), g_ScratchPad.cells.halves[0]),
               g_Task->unk_30.value + FIXED_MUL(rcos((i + 1) << 9), g_ScratchPad.cells.halves[0]));
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));
    }
}
