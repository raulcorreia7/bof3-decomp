#include "magic105_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    PartyMember* saved_work;
    PartyMember* saved_active;
    PartyMember* swap;
    s32          count;

    BMagic_DispatchTaskPair(func_801EED1C, Effect_MarkDamagedOnZeroTick);
    count = 0;
    do {
        if (BMAGIC_EFFECT_SLOTS[(u8)count].header.flags & 0x1) {
            saved_work            = TASK(PartyMember);
            saved_active          = g_BattleEffectBattler;
            swap                  = BMAGIC_EFFECT_SLOTS[(u8)count].target.party;
            g_Task                = MEM_PTR(PartyMember, &BMAGIC_EFFECT_SLOTS[(u8)count]);
            g_BattleEffectBattler = swap;
            func_801EF880();
            func_801EFCF0();
            g_BattleEffectBattler = saved_active;
            g_Task                = saved_work;
        }
        count += 1;
    } while ((u8)count < BMAGIC_EFFECT_COUNT);
}

MATCH void func_801EED1C(void) {
    PartyMember* owner;
    u8           i;
    u8           slot;

    BMAGIC_CLEAR_EFFECTS(i);
    Battle_CenterCamera();
    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    TASK(PartyMember)->unk_0C = -0x80000;
    TASK(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    TASK(PartyMember)->pos.x.fixed  = g_AreaScrollTargetCoordX.fixed + TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed  = g_AreaScrollTargetCoordY.fixed + TASK(PartyMember)->unk_10;
    TASK(PartyMember)->unk_0C       = ratan2(g_AreaScrollTargetCoordX.fixed - TASK(PartyMember)->pos.x.fixed, g_AreaScrollTargetCoordY.fixed - TASK(PartyMember)->pos.y.fixed);
    TASK(PartyMember)->param.unk_0B = 0;
    for (i = 0; i < 7; i++) {
        slot                               = Battle_AllocEffect(1, 51);
        owner                              = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].target.party = owner;
        TASK(PartyMember)->param.unk_0B++;
    }
    for (i = 0; i < 16; i++) {
        MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] = MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = 0;
    g_GfxPalettePending                                          = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
    TASK(PartyMember)->header.mode++;
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEF78 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFBC(void) {
    Magic105Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 3) {
        func_801EF2F0();
        func_801EF3A0();
        PopMatrix();
    }
}

MATCH void func_801EF06C(void) {
    PartyMember* src;
    PartyMember* work;
    FAKE_STACK_PADS(u8, 8);

    src                       = BATTLE_ACTIVE_WORK;
    work                      = TASK(PartyMember);
    work->pos.x.fixed         = src->pos.x.fixed;
    work->pos.y.fixed         = src->pos.y.fixed;
    work->pos.z               = src->pos.z;
    work->unk_0C              = src->unk_0C + D_801F004C[work->unk_04];
    work->unk_10              = src->unk_0C + D_801F004E[work->unk_04];
    work->param.unk_0B        = 0;
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->timer  = 0;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF124(void) {
    u8 slot;
    u8 tick;

    if ((g_FrameCount & 0x3) == (TASK(PartyMember)->unk_04 & 0x3)) {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            BMAGIC_EFFECT_SLOTS[slot].target.party = TASK(PartyMember);
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
            BMAGIC_EFFECT_SLOTS[slot].header.step  = 0;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = TASK(PartyMember)->unk_09;
            BMAGIC_EFFECT_SLOTS[slot].unk_10       = TASK(PartyMember)->unk_10;
            TASK(PartyMember)->param.unk_0B += 1;
        }
    }
    if (g_FrameCount & 0x1) {
        tick                      = TASK(PartyMember)->unk_09 + 1;
        TASK(PartyMember)->unk_09 = tick;
        if (tick == 0x20) {
            TASK(PartyMember)->header.step += 1;
        }
    }
}

MATCH void func_801EF250(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(timer, 1, 64);
}

#include "overlays/bmagic/shared/Effect_TickOnZeroTick.h"

MATCH void func_801EF2F0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(TASK(PartyMember));
}

MATCH void func_801EF3A0(void) {
    POLY_G4*     prim;
    long         depth;
    long         flag;
    s32          tpage;
    s32          x;
    s32          y;
    s32          i;
    PartyMember* work;
    u8           row;

    work                         = TASK(PartyMember);
    row                          = work->unk_04;
    g_ScratchPad.cells.halves[2] = D_801F005C[row][0] - (D_801F005C[row][0] >> 6) * work->timer;
    g_ScratchPad.cells.halves[3] = D_801F005C[row][1] - (D_801F005C[row][1] >> 6) * work->timer;
    g_ScratchPad.cells.halves[4] = D_801F005C[row][2] - (D_801F005C[row][2] >> 6) * work->timer;
    g_ScratchPad.cells.halves[5] = D_801F005C[row + 1][0] - (D_801F005C[row + 1][0] >> 6) * work->timer;
    g_ScratchPad.cells.halves[6] = D_801F005C[row + 1][1] - (D_801F005C[row + 1][1] >> 6) * work->timer;
    g_ScratchPad.cells.halves[7] = D_801F005C[row + 1][2] - (D_801F005C[row + 1][2] >> 6) * work->timer;
    setVector(&g_ScratchPadVectors[0], (u32)rsin(TASK(PartyMember)->unk_0C) >> 6, (u32)rcos(TASK(PartyMember)->unk_0C) >> 6, 0);
    setVector(&g_ScratchPadVectors[1], (u32)rsin(TASK(PartyMember)->unk_10) >> 6, (u32)rcos(TASK(PartyMember)->unk_10) >> 6, 0);
    for (i = 1; i < TASK(PartyMember)->unk_09 + 1; i++) {
        g_ScratchPad.cells.halves[1] = -FIXED_MUL(rsin(i << 6), 384);
        g_ScratchPadVectors[2].vx    = g_ScratchPadVectors[0].vx;
        g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz    = g_ScratchPadVectors[0].vz;
        g_ScratchPadVectors[3].vx    = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[3].vy    = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[3].vz    = g_ScratchPadVectors[1].vz;
        g_ScratchPad.cells.halves[0] = (i << 6) + 64;
        setVector(&g_ScratchPadVectors[0], FIXED_MUL(rsin(TASK(PartyMember)->unk_0C), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(TASK(PartyMember)->unk_0C), g_ScratchPad.cells.halves[0]),
                  g_ScratchPad.cells.halves[1]);
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(TASK(PartyMember)->unk_10), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(TASK(PartyMember)->unk_10), g_ScratchPad.cells.halves[0]),
                  g_ScratchPad.cells.halves[1]);
        x     = (g_ScratchPadVectors[0].vx << 9) + TASK(PartyMember)->pos.x.fixed;
        y     = (g_ScratchPadVectors[0].vy << 9) + TASK(PartyMember)->pos.y.fixed;
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 2, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        PSX_SET_SEMI_TRANSPARENT(prim);
        setRGB0(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4]);
        setRGB1(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        setRGB2(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4]);
        setRGB3(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_CellAddPrim(x, y, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801EF880(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 11), 1, g_Task);
}

MATCH void func_801EF8C4(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0078, TASK(PartyMember)->header.step);
    Battle_ProjectRange();
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF930(void) {
    u16*         cell;
    s8           tint;
    s32          height;
    PartyMember* work;

    cell                                = &g_ScratchPad.cells.halves[1];
    *cell                               = ((u32)(rsin(TASK(PartyMember)->unk_09 << 6) * 3) >> 4);
    g_ScratchPad.cells.halves[0]        = (TASK(PartyMember)->unk_09 << 6) + 0x40;
    TASK(PartyMember)->pos.x.fixed      = BATTLE_ACTIVE_WORK->pos.x.fixed + ((rsin(TASK(PartyMember)->unk_10) * g_ScratchPad.cells.halves[0]) >> 3);
    TASK(PartyMember)->pos.y.fixed      = BATTLE_ACTIVE_WORK->pos.y.fixed + ((rcos(TASK(PartyMember)->unk_10) * g_ScratchPad.cells.halves[0]) >> 3);
    COORD_INT(TASK(PartyMember)->pos.z) = (COORD_INT(BATTLE_ACTIVE_WORK->pos.z) + *cell) - 0x20;
    height                              = Area_HeightSample(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed) << 16;
    work                                = TASK(PartyMember);
    work->unk_25                        = 0x1D;
    work->unk_14                        = height >> 16;
    TASK(PartyMember)->unk_26           = 0;
    TASK(PartyMember)->unk_27           = 0xA0;
    TASK(PartyMember)->unk_28           = 0;
    TASK(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    tint                            = -0x40;
    TASK(PartyMember)->unk_5D       = tint;
    TASK(PartyMember)->unk_5E       = tint;
    TASK(PartyMember)->unk_5F       = tint;
    TASK(PartyMember)->unk_5C       = 1;
    TASK(PartyMember)->unk_2A       = 0;
    TASK(PartyMember)->unk_29       = 3;
    TASK(PartyMember)->unk_24       = 4;
    TASK(PartyMember)->unk_2C.value = 0;
    TASK(PartyMember)->unk_2B       = 0;
    Script_Select((RANDOM_MASK(1)) + 1);
    TASK(PartyMember)->timer = RANDOM_MASK(0x3F);
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EFB68(void) {
    TASK(PartyMember)->timer += 1;
    TASK(PartyMember)->pos.x.fixed += (rsin((TASK(PartyMember)->timer & 0x3F) << 8) * 8) >> 3;
    TASK(PartyMember)->pos.y.fixed += (rcos((TASK(PartyMember)->timer & 0x3F) << 8) * 8) >> 3;
    COORD_INT(TASK(PartyMember)->pos.z) = COORD_INT(TASK(PartyMember)->pos.z) - 8;
    if ((Script_AnimStepOnce() & BYTE_MASK) || (COORD_INT(TASK(PartyMember)->pos.z) < TASK(PartyMember)->unk_14)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        TASK(PartyMember)->header.flags = 0;
        TASK(PartyMember)->header.mode  = 0;
        TASK(PartyMember)->header.step  = 0;
    }
}

/* func_801EFC8C */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

MATCH void func_801EFCF0(void) {
    SPRT*        prim;
    u8*          cell;
    u8*          head;
    s32          shade;
    PartyMember* work;
    PartyMember* task;
    u8           count;
    u16          clut;
    u16          tpage;

    if (TASK(PartyMember)->header.flags & 0x40) {
        return;
    }
    if ((u16)(TASK(PartyMember)->screen_x.value + 0x40) >= 0x1C1) {
        return;
    }
    if ((u16)(TASK(PartyMember)->screen_y.value + 0x40) >= 0x171) {
        return;
    }
    head  = (u8*)TASK(PartyMember)->unk_54 + TASK(PartyMember)->unk_5A;
    count = *head;
    cell  = head + 1;
    if (TASK(PartyMember)->unk_28) {
        clut = getClut(0, TASK(PartyMember)->unk_27 + 0x1E0);
    } else {
        clut = getClut((TASK(PartyMember)->unk_27 & 0xF) << 4, (TASK(PartyMember)->unk_27 >> 4) + 0x1F0);
    }
    for (; count != 0; count--) {
        tpage = getTPage(TASK(PartyMember)->unk_28 != 0, TASK(PartyMember)->unk_5C, 832, 256);
        GFX_ADD_LAYER_DRAW_MODE((u8)TASK(PartyMember)->unk_29, tpage);
        prim = (SPRT*)g_GfxPrimCursor;
        SetSprt(prim);
        setWH(prim, D_801F0080[cell[0] & 0xF][0], D_801F0080[cell[0] & 0xF][1]);
        setUV0(prim, cell[3], TASK(PartyMember)->unk_26 + cell[4]);
        prim->clut = clut;
        shade      = TASK(PartyMember)->unk_5D - 0x80;
        prim->r0   = shade;
        shade      = TASK(PartyMember)->unk_5E - 0x80;
        prim->g0   = shade;
        shade      = TASK(PartyMember)->unk_5F - 0x80;
        prim->b0   = shade;
        if ((cell[0] & 0x80) && (work = TASK(PartyMember), (u8)work->unk_2A != 0)) {
            setXY0(prim, work->screen_x.value - (s8)cell[1] - prim->w, work->screen_y.value + (s8)cell[2]);
        } else {
            task = TASK(PartyMember);
            setXY0(prim, task->screen_x.value + (s8)cell[1], task->screen_y.value + (s8)cell[2]);
        }
        SetSemiTrans(prim, (TASK(PartyMember)->header.flags >> 5) & 1);
        GFX_AddPrim((u8)TASK(PartyMember)->unk_29, sizeof(SPRT));
        cell += 5;
    }
}
