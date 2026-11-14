#include "magic105_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    PartyMember* saved_work;
    PartyMember* saved_active;
    PartyMember* swap;
    s32          count;

    BMagic_DispatchTaskPair(func_801EED1C, Effect_PlayOnZeroTick);
    count = 0;
    do {
        if (BMAGIC_EFFECT_SLOTS[(u8)count].header.flags & 0x1) {
            saved_work            = g_Task;
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

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    Battle_CenterCamera();
    g_Task->facing = g_BattleEffectBattler->facing;
    g_Task->unk_0C = -0x80000;
    g_Task->unk_10 = 0;
    func_801DD350(g_Task);
    /* FAKE: retail reloads both scroll targets for the angle after storing the position; AREA_SCROLL_TARGET_VOLATILE covers X only and moves the scratchpad base load. */
    g_Task->pos.x.fixed  = VOL(s32, g_AreaScrollTargetX) + g_Task->unk_0C;
    g_Task->pos.y.fixed  = VOL(s32, g_AreaScrollTargetY) + g_Task->unk_10;
    g_Task->unk_0C       = ratan2(VOL(s32, g_AreaScrollTargetX) - g_Task->pos.x.fixed, VOL(s32, g_AreaScrollTargetY) - g_Task->pos.y.fixed);
    g_Task->param.unk_0B = 0;
    for (i = 0; i < 7; i++) {
        slot                               = Battle_AllocEffect(1, 51);
        owner                              = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].target.party = owner;
        g_Task->param.unk_0B++;
    }
    for (i = 0; i < 16; i++) {
        MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[i] = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW)[i] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = 0;
    g_GfxPalettePending                                      = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
    g_Task->header.mode++;
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEF78 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFBC(void) {
    Magic105Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 3) {
        func_801EF2F0();
        func_801EF3A0();
        PopMatrix();
    }
}

MATCH void func_801EF06C(void) {
    PartyMember* src;
    PartyMember* work;
    FAKE_STACK_PADS(u8, 8);

    src                = BATTLE_ACTIVE_WORK;
    work               = g_Task;
    work->pos.x.fixed  = src->pos.x.fixed;
    work->pos.y.fixed  = src->pos.y.fixed;
    work->pos.z        = src->pos.z;
    work->unk_0C       = src->unk_0C + D_801F004C[work->unk_04];
    work->unk_10       = src->unk_0C + D_801F004E[work->unk_04];
    work->param.unk_0B = 0;
    g_Task->unk_09     = 0;
    g_Task->timer      = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF124(void) {
    u8 slot;
    u8 tick;

    if ((g_FrameCount & 0x3) == (g_Task->unk_04 & 0x3)) {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            BMAGIC_EFFECT_SLOTS[slot].target.party = g_Task;
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
            BMAGIC_EFFECT_SLOTS[slot].header.step  = 0;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = g_Task->unk_09;
            BMAGIC_EFFECT_SLOTS[slot].unk_10       = g_Task->unk_10;
            g_Task->param.unk_0B += 1;
        }
    }
    if (g_FrameCount & 0x1) {
        tick           = g_Task->unk_09 + 1;
        g_Task->unk_09 = tick;
        if (tick == 0x20) {
            g_Task->header.step += 1;
        }
    }
}

MATCH void func_801EF250(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 64) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801EF2F0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
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

    work                             = g_Task;
    row                              = work->unk_04;
    D_1F800000.view.effect.params[2] = D_801F005C[row][0] - (D_801F005C[row][0] >> 6) * work->timer;
    D_1F800000.view.effect.params[3] = D_801F005C[row][1] - (D_801F005C[row][1] >> 6) * work->timer;
    D_1F800000.view.effect.params[4] = D_801F005C[row][2] - (D_801F005C[row][2] >> 6) * work->timer;
    D_1F800000.view.effect.params[5] = D_801F005C[row + 1][0] - (D_801F005C[row + 1][0] >> 6) * work->timer;
    D_1F800000.view.effect.params[6] = D_801F005C[row + 1][1] - (D_801F005C[row + 1][1] >> 6) * work->timer;
    D_1F800000.view.effect.params[7] = D_801F005C[row + 1][2] - (D_801F005C[row + 1][2] >> 6) * work->timer;
    D_1F800014[0].vx                 = (u32)rsin(g_Task->unk_0C) >> 6;
    D_1F800014[0].vy                 = (u32)rcos(g_Task->unk_0C) >> 6;
    D_1F800014[0].vz                 = 0;
    D_1F800014[1].vx                 = (u32)rsin(g_Task->unk_10) >> 6;
    D_1F800014[1].vy                 = (u32)rcos(g_Task->unk_10) >> 6;
    D_1F800014[1].vz                 = 0;
    for (i = 1; i < g_Task->unk_09 + 1; i++) {
        D_1F800000.view.effect.params[1] = -FIXED_MUL(rsin(i << 6), 384);
        D_1F800014[2].vx                 = D_1F800014[0].vx;
        D_1F800014[2].vy                 = D_1F800014[0].vy;
        D_1F800014[2].vz                 = D_1F800014[0].vz;
        D_1F800014[3].vx                 = D_1F800014[1].vx;
        D_1F800014[3].vy                 = D_1F800014[1].vy;
        D_1F800014[3].vz                 = D_1F800014[1].vz;
        D_1F800000.view.effect.params[0] = (i << 6) + 64;
        D_1F800014[0].vx                 = FIXED_MUL(rsin(g_Task->unk_0C), D_1F800000.view.effect.params[0]);
        D_1F800014[0].vy                 = FIXED_MUL(rcos(g_Task->unk_0C), D_1F800000.view.effect.params[0]);
        D_1F800014[0].vz                 = D_1F800000.view.effect.params[1];
        D_1F800014[1].vx                 = FIXED_MUL(rsin(g_Task->unk_10), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(g_Task->unk_10), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz                 = D_1F800000.view.effect.params[1];
        x                                = (D_1F800014[0].vx << 9) + g_Task->pos.x.fixed;
        y                                = (D_1F800014[0].vy << 9) + g_Task->pos.y.fixed;
        tpage                            = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(x, y, 2, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4]);
        setRGB1(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[7]);
        setRGB2(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4]);
        setRGB3(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[7]);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        Area_AddCellPrim(x, y, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801EF880(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 11), 1, g_Task);
}

MATCH void func_801EF8C4(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0078, g_Task->header.step);
    Battle_ProjectRange();
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF930(void) {
    u16*         cell;
    s8           tint;
    s32          height;
    PartyMember* work;

    cell                                = &D_1F800000.view.area.entry_data;
    *cell                               = ((u32)(rsin(g_Task->unk_09 << 6) * 3) >> 4);
    D_1F800000.view.area.entity_counter = (g_Task->unk_09 << 6) + 0x40;
    g_Task->pos.x.fixed                 = BATTLE_ACTIVE_WORK->pos.x.fixed + ((rsin(g_Task->unk_10) * D_1F800000.view.area.entity_counter) >> 3);
    g_Task->pos.y.fixed                 = BATTLE_ACTIVE_WORK->pos.y.fixed + ((rcos(g_Task->unk_10) * D_1F800000.view.area.entity_counter) >> 3);
    COORD_INT(g_Task->pos.z)            = (COORD_INT(BATTLE_ACTIVE_WORK->pos.z) + *cell) - 0x20;
    height                              = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) << 16;
    work                                = g_Task;
    work->unk_25                        = 0x1D;
    work->unk_14                        = height >> 16;
    g_Task->unk_26                      = 0;
    g_Task->unk_27                      = 0xA0;
    g_Task->unk_28                      = 0;
    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    tint                = -0x40;
    g_Task->unk_5D      = tint;
    g_Task->unk_5E      = tint;
    g_Task->unk_5F      = tint;
    g_Task->unk_5C      = 1;
    g_Task->unk_2A      = 0;
    g_Task->unk_29      = 3;
    g_Task->unk_24      = 4;
    g_Task->unk_2C.half = 0;
    g_Task->unk_2B      = 0;
    Actor_SelectScript((RANDOM_MASK(1)) + 1);
    g_Task->timer = RANDOM_MASK(0x3F);
    g_Task->header.step += 1;
}

MATCH void func_801EFB68(void) {
    g_Task->timer += 1;
    g_Task->pos.x.fixed += (rsin((g_Task->timer & 0x3F) << 8) * 8) >> 3;
    g_Task->pos.y.fixed += (rcos((g_Task->timer & 0x3F) << 8) * 8) >> 3;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) - 8;
    if ((Actor_StepAnimOnce() & BYTE_MASK) || (COORD_INT(g_Task->pos.z) < g_Task->unk_14)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.flags = 0;
        g_Task->header.mode  = 0;
        g_Task->header.step  = 0;
    }
}

/* func_801EFC8C */
#include "overlays/bmagic/BMagic_AllocEffect.h"

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

    if (g_Task->header.flags & 0x40) {
        return;
    }
    if ((u16)(g_Task->unk_2E.half + 0x40) >= 0x1C1) {
        return;
    }
    if ((u16)(g_Task->unk_30.half + 0x40) >= 0x171) {
        return;
    }
    head  = (u8*)g_Task->unk_54 + g_Task->unk_5A;
    count = *head;
    cell  = head + 1;
    if (g_Task->unk_28) {
        clut = getClut(0, g_Task->unk_27 + 0x1E0);
    } else {
        clut = getClut((g_Task->unk_27 & 0xF) << 4, (g_Task->unk_27 >> 4) + 0x1F0);
    }
    for (; count != 0; count--) {
        tpage = getTPage(g_Task->unk_28 != 0, g_Task->unk_5C, 832, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
        GFX_AddPrim((u8)g_Task->unk_29, sizeof(DR_MODE));
        prim = (SPRT*)g_GfxPrimCursor;
        SetSprt(prim);
        prim->w = D_801F0080[cell[0] & 0xF][0];
        prim->h = D_801F0080[cell[0] & 0xF][1];
        setUV0(prim, cell[3], g_Task->unk_26 + cell[4]);
        prim->clut = clut;
        shade      = g_Task->unk_5D - 0x80;
        prim->r0   = shade;
        shade      = g_Task->unk_5E - 0x80;
        prim->g0   = shade;
        shade      = g_Task->unk_5F - 0x80;
        prim->b0   = shade;
        if ((cell[0] & 0x80) && (work = g_Task, (u8)work->unk_2A != 0)) {
            setXY0(prim, work->unk_2E.half - (s8)cell[1] - prim->w, work->unk_30.half + (s8)cell[2]);
        } else {
            task = g_Task;
            setXY0(prim, task->unk_2E.half + (s8)cell[1], task->unk_30.half + (s8)cell[2]);
        }
        SetSemiTrans(prim, (g_Task->header.flags >> 5) & 1);
        GFX_AddPrim((u8)g_Task->unk_29, sizeof(SPRT));
        cell += 5;
    }
}
