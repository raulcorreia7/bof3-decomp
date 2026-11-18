#include "magic041_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EECB0(void) {
    PartyMember* battler;
    PartyMember* task;
    u8           slot;
    u8           count;

    battler              = g_BattleEffectBattler;
    g_Task->pos.x.fixed  = battler->pos.x.fixed;
    g_Task->pos.y.fixed  = battler->pos.y.fixed;
    g_Task->pos.z.fixed  = battler->pos.z.fixed;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0xA;
    g_Task->timer        = 0;
    g_Task->header.mode += 1;

    count = 0;
    do {
        slot                               = Battle_AllocEffect(1, 0x3D) & BYTE_MASK;
        task                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].arg.unk_09   = ((count & BYTE_MASK) << 3) + 1;
        g_BattleEffects[slot].target.party = task;
        FAKE_BARRIER(); /* FAKE: retail re-reads the g_Task cell for the ticker; plain C keeps the copy. */
        g_Task->param.unk_0B++;
        count++;
    } while (count < 8);

    slot                               = Battle_AllocEffect(1, 0x3D) & BYTE_MASK;
    task                               = g_Task;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].target.party = task;
    FAKE_BARRIER(); /* FAKE: retail re-reads the g_Task cell for the ticker; plain C keeps the copy. */
    g_Task->param.unk_0B++;
    SND_QueueSelectionSE(0x100);
}
#else
INCLUDE_ASM(func_801EECB0);
#endif

MATCH void func_801EEE14(void) {
    u8            timer;
    PartyMember** selected;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        selected = &g_Battle.selected_actor;
        GFX_FreePaletteFadeTarget(*selected);
        g_Task->unk_09 = GFX_AllocPaletteFade(*selected, 0, 0, 0, 1);
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEEB4(void) {
    u8 timer;

    g_PaletteFades[g_Task->unk_09].offset.r += 2;
    g_PaletteFades[g_Task->unk_09].offset.g += 1;
    g_PaletteFades[g_Task->unk_09].offset.b += 1;
    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 8) {
        g_Task->header.mode++;
    }
}

#include "overlays/bmagic/Effect_NextStepOnWorkLastTick.h"

MATCH void func_801EEFF8(void) {
    g_PaletteFades[g_Task->unk_09].offset.r -= 2;
    g_PaletteFades[g_Task->unk_09].offset.g -= 1;
    g_PaletteFades[g_Task->unk_09].offset.b -= 1;
    if (--g_Task->timer == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF190 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF1D4(void) {
    Magic041Steps handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (ACTOR_IN_USE(*g_Task) && g_Task->header.step != 0) {
        BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801EF670);
    }
}

MATCH void func_801EF27C(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--g_Task->unk_09 == 0) {
        src              = g_BattleEffectBattler;
        dst              = g_Task;
        dst->pos.x.fixed = src->pos.x.fixed;
        dst->pos.y.fixed = src->pos.y.fixed;
        dst->pos.z       = src->pos.z;
        dst->unk_09      = 0;
        g_Task->timer    = 0;
        g_Task->header.step++;
    }
}

MATCH void func_801EF308(void) {
    u8 timer;

    timer         = g_Task->timer + 4;
    g_Task->timer = timer;
    if (timer == 32) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF358(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = g_Task;
    work->unk_09 += 4;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        Effect_Reset();
    }
}

MATCH void func_801EF3D0(void) {
    Magic041SecondSteps handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (ACTOR_IN_USE(*g_Task) && g_Task->header.step != 0) {
        BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801EFAB8);
    }
}

MATCH void func_801EF484(void) {
    PartyMember* src;

    src                 = (PartyMember*)g_BattleEffectBattler;
    g_Task->pos.x.fixed = src->pos.x.fixed;
    g_Task->pos.y.fixed = src->pos.y.fixed;
    g_Task->pos.z       = src->pos.z;
    g_Task->unk_09      = 0;
    g_Task->header.step = g_Task->header.step + 1;
}

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

#include "overlays/bmagic/Effect_NextStepOnLastTick.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EF670(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      x;
    s32      y;
    s32      tpage;

    g_ScratchPad.cells.halves[0] = g_Task->unk_09 * 24;
    g_ScratchPad.cells.halves[1] = g_Task->unk_09 << 5;
    g_ScratchPad.cells.halves[5] = g_Task->timer * 12;
    g_ScratchPad.cells.halves[6] = g_Task->timer * 6;
    g_ScratchPad.cells.halves[7] = g_Task->timer * 6;
    g_ScratchPadVectors[0].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[0].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[1].vz    = -64;
    g_ScratchPadVectors[0].vz    = -64;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vz    = 0;
    g_ScratchPadVectors[2].vz    = 0;
    for (i = 1; i <= 32; i++) {
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[0].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[0].vx = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[3].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[3].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[0]);
        x                         = (g_ScratchPadVectors[2].vx << 9) + g_Task->pos.x.fixed;
        y                         = (g_ScratchPadVectors[2].vy << 9) + g_Task->pos.y.fixed;
        tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        setRGB3(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        /* Retail advances the cursor 40 bytes, a POLY_FT4, past this 36-byte POLY_G4. */
        Area_AddCellPrim(x, y, 0, sizeof(POLY_FT4));
    }
}
#else
INCLUDE_ASM(func_801EF670);
#endif

MATCH void func_801EFAB8(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = 0x88;
    g_ScratchPad.cells.halves[3] = g_Task->unk_09 << 3;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;

    for (i = 1; i <= 16; i++) {
        prim = GFX_BeginPolyG3(1);
        GFX_STEP_TRIANGLE_FAN(i << 8, g_ScratchPad.cells.halves[0]);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 4, g_ScratchPad.cells.halves[3] / 4);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 4, g_ScratchPad.cells.halves[3] / 4);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}
