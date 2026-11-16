#include "magic044_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEDA0);
}

MATCH void func_801EEC5C(void) {
    PartyMember* task;
    PartyMember* work;
    u16*         src;
    u16*         dst;
    u32          i;
    u8           slot;

    g_Task->facing = g_BattleEffectBattler->facing;
    task           = g_Task;
    WorldPos_Copy(&task->pos, &g_BattleEffectBattler->pos);
    task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 2; i++) {
        slot                               = Battle_AllocEffect(1, 6) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    i   = 1;
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i + AREA_PALETTE_UNIT / sizeof(u16)] = src[i + AREA_PALETTE_UNIT / sizeof(u16)] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW + AREA_PALETTE_UNIT) = 0;

    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEE00 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE44(void) {
    SYS_DISPATCH_BYTE(D_801F0A1C, g_Task->header.step);
    if (g_Task->unk_04 != 0) {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EF4E0();
        }
    } else {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EFA4C();
        }
    }
}

MATCH void func_801EEEFC(void) {
    PartyMember* source;
    PartyMember* record;
    PartyMember* work;
    s32          heading;

    source         = g_BattleSelectedActor;
    g_Task->facing = g_BattleEffectBattler->facing;
    if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        g_Task->unk_0C = 0x4000;
        g_Task->unk_10 = 0;
        g_Task->unk_14 = TO_COORD(0x100);
    } else {
        switch (ENEMY_COMBATANT(g_Battle.active_battler).enemy_id.byte.kind) {
            case 0x99:
            default:
                g_Task->unk_0C = 0x2000;
                g_Task->unk_10 = 0;
                g_Task->unk_14 = TO_COORD(0x1C0);
                break;
            case 0x9A:
                g_Task->unk_0C = 0x10000;
                g_Task->unk_10 = 0;
                g_Task->unk_14 = TO_COORD(0x200);
                break;
            case 0xB5:
                g_Task->unk_0C = -0xE000;
                g_Task->unk_10 = 0;
                g_Task->unk_14 = TO_COORD(0x380);
                break;
        }
    }
    Effect_RotatePosition(g_Task);
    record            = g_BattleEffectBattler;
    work              = g_Task;
    work->pos.x.fixed = record->pos.x.fixed + work->unk_0C;
    work->pos.y.fixed = record->pos.y.fixed + work->unk_10;
    work->pos.z.fixed = record->pos.z.fixed + work->unk_14;
    heading           = ratan2(source->pos.x.fixed - work->pos.x.fixed, source->pos.y.fixed - work->pos.y.fixed);
    g_Task->unk_0C    = heading;
    g_Task->unk_10    = 0;
    Battle_ProjectRange();
    BMagic_Trail[g_Task->unk_04][0].x = g_Task->unk_2E.half;
    BMagic_Trail[g_Task->unk_04][0].y = g_Task->unk_30.half;
    BMagic_Trail[g_Task->unk_04][1].x = g_Task->unk_2E.half;
    BMagic_Trail[g_Task->unk_04][1].y = g_Task->unk_30.half;
    g_Task->param.unk_0B              = 0;
    g_Task->unk_09                    = 0x10;
    g_Task->timer                     = 1;
    g_Task->header.step++;
}

MATCH void func_801EF138(void) {
    VECTOR       pos;
    PartyMember* actor;
    s32          diff;
    u8           count;

    count = g_Task->timer;
    if (count < 16) {
        g_Task->timer = count + 1;
    }
    actor = g_Battle.selected_actor;
    setVector(&pos, (actor->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (actor->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, (actor->pos.z.fixed + 0x800000) >> 17);
    Battle_StepRangeToward(pos, 0xC0);
    g_Task->unk_10 = g_Task->unk_0C;
    g_Task->unk_0C = ratan2(actor->pos.x.fixed - g_Task->pos.x.fixed, actor->pos.y.fixed - g_Task->pos.y.fixed);
    if (func_800AF66C((BattleRange*)actor, 0x8000) != 0) {
        g_Task->pos.x.fixed = actor->pos.x.fixed;
        g_Task->pos.y.fixed = actor->pos.y.fixed;
        g_Task->header.step += 1;
    } else {
        diff           = (g_Task->unk_10 & ANGLE_MASK) - (g_Task->unk_0C & ANGLE_MASK);
        g_Task->unk_10 = diff;
        if (diff < 0) {
            g_Task->unk_10 = ~diff + 1;
        }
        if ((u32)(g_Task->unk_10 - 0x601) < 0x3FF) {
            g_Task->pos.x.fixed = actor->pos.x.fixed;
            g_Task->pos.y.fixed = actor->pos.y.fixed;
            g_Task->header.step += 1;
        }
    }
    Battle_ProjectRange();
    Effect_RecordTrail();
    if (g_Task->header.step != 1 && g_Task->unk_04 == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    }
}

MATCH void func_801EF320(void) {
    PartyMember* work;
    u32          slot;
    u8           count;

    if (g_Task->timer < 0x10) {
        g_Task->param.unk_0B += 1;
        g_Task->timer += 1;
        Battle_ProjectRange();
        Effect_RecordTrail();
    }
    if ((g_FrameCount & 0x3) == 0) {
        slot = Battle_AllocEffect(1, 6) & BYTE_MASK;
        if (slot != GAME_NONE) {
            work                               = g_BattleEffectBattler;
            g_BattleEffects[slot].header.mode  = 1;
            g_BattleEffects[slot].target.party = work;
            g_BattleEffects[slot].pos.x.fixed  = g_Task->pos.x.fixed;
            g_BattleEffects[slot].pos.y.fixed  = g_Task->pos.y.fixed;
            g_BattleEffects[slot].pos.z.fixed  = g_Task->pos.z.fixed;
            g_BattleEffectBattler->param.unk_0B += 1;
        }
    }
    count = g_Task->timer;
    if ((count & BYTE_MASK) == 0x10) {
        g_Task->unk_09 = count;
        g_Task->header.step += 1;
    }
}

/* func_801EF478 */
#include "overlays/bmagic/Effect_FinishTrail.h"

MATCH void func_801EF4E0(void) {
    POLY_G4* prim;
    s32      k;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(3, tpage);
    k = g_Task->param.unk_0B;
    while (BMagic_Trail[g_Task->unk_04][k].x == -1) {
        k++;
    }
    g_ScratchPad.cells.halves[0] = 2;
    g_ScratchPad.cells.halves[6] = BMagic_Trail[g_Task->unk_04][k].x;
    g_ScratchPad.cells.halves[7] = BMagic_Trail[g_Task->unk_04][k].y;
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][k + 1].x;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][k + 1].y;
    g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][k].x;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][k].y;
    for (k = k + 1; k < g_Task->timer; k++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][k].x;
        g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][k].y;
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
        g_ScratchPad.cells.halves[2] = 97 - (k - 1) * 6;
        g_ScratchPad.cells.halves[3] = 193 - (k - 1) * 12;
        setRGB0(prim, 1, 1, g_ScratchPad.cells.halves[3]);
        setRGB2(prim, 1, 1, g_ScratchPad.cells.halves[3]);
        g_ScratchPad.cells.halves[2] = 97 - k * 6;
        g_ScratchPad.cells.halves[3] = 193 - k * 12;
        setRGB1(prim, 1, 1, g_ScratchPad.cells.halves[3]);
        setRGB3(prim, 1, 1, g_ScratchPad.cells.halves[3]);
        GFX_AddPrim(3, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(3, tpage);
}

MATCH void func_801EFA4C(void) {
    POLY_G4* prim;
    s32      k;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(3, tpage);
    g_ScratchPad.cells.halves[0] = 12;
    k                            = g_Task->param.unk_0B;
    while (BMagic_Trail[g_Task->unk_04][k].x == -1) {
        k++;
    }
    g_ScratchPad.cells.halves[6] = BMagic_Trail[g_Task->unk_04][k].x;
    g_ScratchPad.cells.halves[7] = BMagic_Trail[g_Task->unk_04][k].y;
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][k + 1].x;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][k + 1].y;
    g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][k].x;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][k].y;
    for (k = k + 1; k < g_Task->timer; k++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][k].x;
        g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][k].y;
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
        g_ScratchPad.cells.halves[3] = 97 - (k - 1) * 6;
        setRGB0(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[3], 1, g_ScratchPad.cells.halves[3]);
        g_ScratchPad.cells.halves[3] = 97 - k * 6;
        setRGB1(prim, 1, 1, 1);
        setRGB3(prim, g_ScratchPad.cells.halves[3], 1, g_ScratchPad.cells.halves[3]);
        GFX_AddPrim(3, sizeof(POLY_G4));
    }
    k = g_Task->param.unk_0B;
    while (BMagic_Trail[g_Task->unk_04][k].x == -1) {
        k++;
    }
    g_ScratchPad.cells.halves[6] = BMagic_Trail[g_Task->unk_04][k].x;
    g_ScratchPad.cells.halves[7] = BMagic_Trail[g_Task->unk_04][k].y;
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][k + 1].x;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][k + 1].y;
    g_ScratchPad.cells.halves[1] = ratan2(g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[7]);
    g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][k].x;
    g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][k].y;
    for (k = k + 1; k < g_Task->timer; k++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[4] = BMagic_Trail[g_Task->unk_04][k].x;
        g_ScratchPad.cells.halves[5] = BMagic_Trail[g_Task->unk_04][k].y;
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
        g_ScratchPad.cells.halves[3] = 129 - (k - 1) * 8;
        setRGB0(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[3], 1, g_ScratchPad.cells.halves[3]);
        g_ScratchPad.cells.halves[3] = 129 - k * 8;
        setRGB1(prim, 1, 1, 1);
        setRGB3(prim, g_ScratchPad.cells.halves[3], 1, g_ScratchPad.cells.halves[3]);
        GFX_AddPrim(3, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(3, tpage);
}

/* func_801F02A0 */
#include "overlays/bmagic/Effect_RecordTrail.h"

/* func_801F0390 */
#include "overlays/bmagic/Effect_ClearTrail.h"

MATCH void func_801F0478(void) {
    SYS_DISPATCH_BYTE(D_801F0A2C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F06D8();
    }
}

MATCH void func_801F04F0(void) {
    Battle_ProjectRange();
    g_Task->unk_30.half += 8;
    g_Task->unk_5D = (RANDOM_MASK(3)) + 1;
    g_Task->unk_5E = (RANDOM_MASK(3)) + 1;
    g_Task->unk_5F = (RANDOM_MASK(3)) + 1;
    g_Task->unk_09 = 0;
    g_Task->timer  = 16;
    g_Task->header.step += 1;
}

MATCH void func_801F05AC(void) {
    PartyMember* work;
    PartyMember* next;
    PartyMember* state;

    rand();
    work = g_Task;
    work->unk_2E.half -= 1;
    FAKE_BARRIER(); /* FAKE: reloads the g_Task cell after the store, as retail does; plain C caches it (0x78 vs 0x8C), TASK_VOLATILE re-reads each use (0x84) and moves seven other functions. */
    next = g_Task;
    next->unk_09 += 4;
    next->unk_30.half -= 1;
    state = g_Task;
    if (state->unk_09 == 0x10) {
        state->header.step++;
    }
}

MATCH void func_801F0638(void) {
    PartyMember* work;
    PartyMember* next;
    PartyMember* state;
    u8           timer;

    work = g_Task;
    work->unk_30.half -= 2;
    work->unk_09 += 1;
    rand();
    next = g_Task;
    next->unk_2E.half -= 1;
    FAKE_BARRIER(); /* FAKE: reloads the g_Task cell before the timer, as retail does; plain C caches it (0x88 vs 0xA0), TASK_VOLATILE re-reads each use (0x98) and moves seven other functions. */
    state        = g_Task;
    timer        = state->timer - 1;
    state->timer = timer;
    if (timer == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Effect_Reset();
    }
}

/* The textured quad scratch: the corner radius and the colour channels, ahead of the quad corners. */
#define QUAD_RADIUS g_ScratchPad.cells.halves[0]
#define QUAD_RED    g_ScratchPad.cells.halves[5]
#define QUAD_GREEN  g_ScratchPad.cells.halves[6]
#define QUAD_BLUE   g_ScratchPad.cells.halves[7]

/* A 32x32 textured quad around the effect position, its corners twice the effect counter (byte 0x09) away,
 * coloured by the timer scaled per channel (bytes 0x5D-0x5F). */
MATCH void func_801F06D8(void) {
    POLY_FT4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    prim        = (POLY_FT4*)g_GfxPrimCursor;
    QUAD_RADIUS = g_Task->unk_09 * 2;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, g_Task->unk_2E.half + FIXED_MUL(rcos(ANGLE_45), QUAD_RADIUS), g_Task->unk_30.half + FIXED_MUL(rsin(ANGLE_45), QUAD_RADIUS), g_Task->unk_2E.half + FIXED_MUL(rcos(1536), QUAD_RADIUS),
           g_Task->unk_30.half + FIXED_MUL(rsin(1536), QUAD_RADIUS), g_Task->unk_2E.half + FIXED_MUL(rcos(3584), QUAD_RADIUS), g_Task->unk_30.half + FIXED_MUL(rsin(3584), QUAD_RADIUS),
           g_Task->unk_2E.half + FIXED_MUL(rcos(2560), QUAD_RADIUS), g_Task->unk_30.half + FIXED_MUL(rsin(2560), QUAD_RADIUS));
    setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 832, 256);
    setClut(prim, 32, 506);
    setUVWH(prim, 128, 32, 32, 32);
    QUAD_RED   = g_Task->timer * (s8)g_Task->unk_5D;
    QUAD_GREEN = g_Task->timer * (s8)g_Task->unk_5E;
    QUAD_BLUE  = g_Task->timer * (s8)g_Task->unk_5F;
    setRGB0(prim, QUAD_RED, QUAD_GREEN, QUAD_BLUE);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}
