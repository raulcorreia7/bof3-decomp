#include "magic006_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC38(void) {
    BMagic_DispatchTaskPair(func_801EEC90, func_801EEDA4);
}

MATCH void func_801EEC90(void) {
    u32 slot;
    s32 i;

    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&TASK(PartyMember)->pos, &g_BattleEffectBattler->pos);
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->header.mode += 1;
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 83) & BYTE_MASK;
        g_BattleEffects[slot].target.party = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        TASK(PartyMember)->param.unk_0B += 1;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEE04 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE48(void) {
    BMagicEffectSteps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        if (TASK(PartyMember)->param.unk_0B != 0) {
            func_801EFB6C();
        } else {
            func_801EF478();
        }
    }
}

MATCH void func_801EEF28(void) {
    PartyMember* battler;
    u8           value;

    value                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(128);
        Battle_ProjectRange();
        battler                   = g_Battle.selected_actor;
        TASK(PartyMember)->unk_0C = ratan2(battler->pos.x.fixed - TASK(PartyMember)->pos.x.fixed, battler->pos.y.fixed - TASK(PartyMember)->pos.y.fixed);
        TASK(PartyMember)->unk_10 = 0;
        TASK(PartyMember)->unk_14 =
            (ratan2((s16)battler->screen_x.value - (s16)TASK(PartyMember)->screen_x.value, (s16)battler->screen_y.value - (s16)TASK(PartyMember)->screen_y.value) - 0x200) & ANGLE_MASK;
        SND_SEQueueSelection(0x100);
        TASK(PartyMember)->unk_09 = 0x20;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF04C(void) {
    PartyMember* work = TASK(PartyMember);
    u8           timer;

    work->unk_14 += 0x80;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        TASK(PartyMember)->unk_09 = TASK(PartyMember)->param.unk_0B + 0xC;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF0B8(void) {
    PartyMember* work;

    work         = TASK(PartyMember);
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 0) {
        SND_SEQueueSelection(0x101);
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF118(void) {
    PartyMember* actor;
    VECTOR       pos;
    s32          diff;
    u8           ticker;

    actor = g_BattleSelectedActor;
    setVector(&pos, (actor->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (actor->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, (actor->pos.z.fixed + 0x800000) >> 17);
    Battle_StepRangeToward(pos, 0x60);
    TASK(PartyMember)->unk_10 = TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->unk_0C = ratan2(actor->pos.x.fixed - TASK(PartyMember)->pos.x.fixed, actor->pos.y.fixed - TASK(PartyMember)->pos.y.fixed);
    if (func_800AF66C((BattleRange*)actor, 0x20000) != 0) {
        ticker = TASK(PartyMember)->param.unk_0B;
    } else {
        diff                      = (TASK(PartyMember)->unk_10 & ANGLE_MASK) - (TASK(PartyMember)->unk_0C & ANGLE_MASK);
        TASK(PartyMember)->unk_10 = diff;
        if (diff < 0) {
            TASK(PartyMember)->unk_10 = ~diff + 1;
        }
        if ((u32)(TASK(PartyMember)->unk_10 - 0x601) >= 0x3FF) {
            return;
        }
        ticker = TASK(PartyMember)->param.unk_0B;
    }
    if (ticker == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    }
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF298(void) {
    u8 slot;
    u8 i;

    if (TASK(PartyMember)->param.unk_0B == 0) {
        i = 0;
        do {
            slot                               = Battle_AllocEffect(1, 83);
            g_BattleEffects[slot].target.party = g_BattleEffectBattler;
            g_BattleEffects[slot].header.mode  = 1;
            g_BattleEffects[slot].unk_0B       = i;
            i++;
            g_BattleEffects[slot].arg.unk_09 = (rand() & 0xF) + 1;
            g_BattleEffectBattler->param.unk_0B += 1;
        } while (i < 8);
        slot                               = Battle_AllocEffect(1, 83);
        g_BattleEffects[slot].target.party = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 2;
        g_BattleEffectBattler->param.unk_0B += 1;
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x02));
        TASK(PartyMember)->unk_09 = 0x10;
        TASK(PartyMember)->header.step += 1;
    } else {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

MATCH void func_801EF478(void) {
    POLY_G4* prim;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[2] = 8;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->screen_y.value;
    for (i = 2; i < 8; i += 2) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[3] = D_801F0A30[i / 2];
        g_ScratchPad.cells.halves[4] = (((i + 1) << 9) + TASK(PartyMember)->unk_14) & ANGLE_MASK;
        setXY0(prim, g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]),
               g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]));
        g_ScratchPad.cells.halves[4] = ((i << 9) + TASK(PartyMember)->unk_14) & ANGLE_MASK;
        prim->x1                     = g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
        prim->y1                     = g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
        g_ScratchPad.cells.halves[4] = (((i + 2) << 9) + TASK(PartyMember)->unk_14) & ANGLE_MASK;
        prim->x2                     = g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
        prim->y2                     = g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
        prim->x3                     = g_ScratchPad.cells.halves[0];
        prim->y3                     = g_ScratchPad.cells.halves[1];
        setRGB0(prim, 16, 64, 16);
        setRGB1(prim, 16, 64, 16);
        setRGB2(prim, 16, 64, 16);
        setRGB3(prim, 64, 64, 64);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    g_ScratchPad.cells.halves[3] = 64;
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->unk_14 + 0x200) & ANGLE_MASK;
    setXY0(prim, g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]),
           g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]));
    g_ScratchPad.cells.halves[3] = 56;
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->unk_14 + 0x230) & ANGLE_MASK;
    prim->x1                     = g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]);
    prim->y1                     = g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]);
    prim->x2                     = g_ScratchPad.cells.halves[0];
    prim->y2                     = g_ScratchPad.cells.halves[1];
    g_ScratchPad.cells.halves[4] = 0x400;
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->unk_14 + g_ScratchPad.cells.halves[4]) & ANGLE_MASK;
    prim->x3                     = g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
    prim->y3                     = g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
    setRGB0(prim, 32, 32, 224);
    setRGB1(prim, 32, 32, 224);
    setRGB2(prim, 224, 224, 224);
    setRGB3(prim, 32, 32, 224);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    g_ScratchPad.cells.halves[3] = 64;
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->unk_14 + 0x200) & ANGLE_MASK;
    setXY0(prim, g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]),
           g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]));
    g_ScratchPad.cells.halves[3] = 56;
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->unk_14 + 0x1D0) & ANGLE_MASK;
    prim->x1                     = g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]);
    prim->y1                     = g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]);
    prim->x2                     = g_ScratchPad.cells.halves[0];
    prim->y2                     = g_ScratchPad.cells.halves[1];
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->unk_14 & ANGLE_MASK;
    prim->x3                     = g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
    prim->y3                     = g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
    setRGB0(prim, 32, 32, 224);
    setRGB1(prim, 32, 32, 224);
    setRGB2(prim, 128, 128, 128);
    setRGB3(prim, 32, 32, 224);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
}

MATCH void func_801EFB6C(void) {
    POLY_G4* prim;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[2] = 8;
    prim                         = (POLY_G4*)g_GfxPrimCursor;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->screen_y.value;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    g_ScratchPad.cells.halves[3] = 64;
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->unk_14 + 0x200) & ANGLE_MASK;
    setXY0(prim, g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]),
           g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]));
    g_ScratchPad.cells.halves[3] = 56;
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->unk_14 + 0x230) & ANGLE_MASK;
    prim->x1                     = g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]);
    prim->y1                     = g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]);
    prim->x2                     = g_ScratchPad.cells.halves[0];
    prim->y2                     = g_ScratchPad.cells.halves[1];
    g_ScratchPad.cells.halves[4] = 0x400;
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->unk_14 + g_ScratchPad.cells.halves[4]) & ANGLE_MASK;
    prim->x3                     = g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
    prim->y3                     = g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
    setRGB0(prim, 16, 16, 96);
    setRGB1(prim, 16, 16, 96);
    setRGB2(prim, 16, 16, 48);
    setRGB3(prim, 16, 16, 48);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    g_ScratchPad.cells.halves[3] = 64;
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->unk_14 + 0x200) & ANGLE_MASK;
    setXY0(prim, g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]),
           g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]));
    g_ScratchPad.cells.halves[3] = 56;
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->unk_14 + 0x1D0) & ANGLE_MASK;
    prim->x1                     = g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]);
    prim->y1                     = g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]);
    prim->x2                     = g_ScratchPad.cells.halves[0];
    prim->y2                     = g_ScratchPad.cells.halves[1];
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->unk_14 & ANGLE_MASK;
    prim->x3                     = g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
    prim->y3                     = g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[2]);
    setRGB0(prim, 16, 16, 96);
    setRGB1(prim, 16, 16, 96);
    setRGB2(prim, 16, 16, 48);
    setRGB3(prim, 16, 16, 48);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
}

MATCH void func_801F0064(void) {
    Magic006Steps handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        func_801F0308();
    }
}

MATCH void func_801F0100(void) {
    PartyMember* actor;
    PartyMember* work;
    s16*         angle_cell;
    u8           count;
    u8           phase;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count == 0) {
        phase                                   = TASK(PartyMember)->param.unk_0B;
        angle_cell                              = &D_1F800008;
        *angle_cell                             = phase << 9;
        actor                                   = g_Battle.selected_actor;
        TASK(PartyMember)->pos.x.fixed          = actor->pos.x.fixed + ((rcos((s16)(phase << 9)) * 0xC000) >> 12);
        (work = TASK(PartyMember))->pos.y.fixed = actor->pos.y.fixed + ((rsin(*angle_cell) * 0xC000) >> 12);
        work->pos.z.fixed                       = actor->pos.z.fixed;
        work->unk_09                            = 0;
        TASK(PartyMember)->timer                = 4;
        TASK(PartyMember)->header.step++;
    }
}

MATCH void func_801F020C(void) {
    u8 counter;

    if (g_FrameCount & 0x1) {
        TASK(PartyMember)->timer += 1;
    }
    counter                   = TASK(PartyMember)->unk_09 + 0x10;
    TASK(PartyMember)->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x80) {
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F0290 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(8);
}

MATCH void func_801F0308(void) {
    POLY_G4* prim;
    s32      tpage;

    g_ScratchPad.cells.halves[2] = TASK(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[3] = TASK(PartyMember)->timer;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->screen_y.value;
    tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, g_ScratchPad.cells.halves[0] - g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[1] - g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[0] + g_ScratchPad.cells.halves[3],
           g_ScratchPad.cells.halves[1] - g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[0] - g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[1],
           g_ScratchPad.cells.halves[0] + g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[1]);
    setRGB0(prim, 1, 1, 1);
    setRGB1(prim, 1, 1, 1);
    setRGB2(prim, 0x80, 0x20, 1);
    setRGB3(prim, 0x80, 0x20, 1);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(POLY_G4));
}

MATCH void func_801F04F4(void) {
    Magic006SecondSteps handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    BMAGIC_DRAW_IF_RUNNING(func_801F0790);
}

MATCH void func_801F05A4(void) {
    PartyMember* src;

    src                            = g_Battle.selected_actor;
    TASK(PartyMember)->pos.x.fixed = src->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed = src->pos.y.fixed;
    TASK(PartyMember)->pos.z       = src->pos.z;
    TASK(PartyMember)->unk_09      = 0;
    TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
}

MATCH void func_801F05F4(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(unk_09, 4, 16);
}

#include "overlays/bmagic/shared/Effect_NextStepOnLastTick.h"

MATCH void Effect_TickOnTimerZero3(void) {
    PartyMember* work;

    BMAGIC_TICK_ON_TIMER_ZERO(EFFECT_TIMER_TICK);
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

MATCH void func_801F0790(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = 0x100;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->unk_09 << 3;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->unk_09 << 1;
    g_ScratchPad.cells.halves[7] = 1;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;

    for (i = 1; i <= 16; i++) {
        prim = GFX_BeginPolyG3(1);
        GFX_STEP_TRIANGLE_FAN(i << 8, g_ScratchPad.cells.halves[0]);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}
