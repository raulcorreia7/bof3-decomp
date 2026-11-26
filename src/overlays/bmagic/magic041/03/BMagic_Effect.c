#include "magic041_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_DispatchMode.h"

/* Places the effect on its battler and spawns its eight numbered parts and one mode-1 part, counting each. */
MATCH void func_801EECB0(void) {
    PartyMember* battler;
    u8           slot;
    u8           count;

    battler                         = g_BattleEffectBattler;
    TASK(PartyMember)->pos.x.fixed  = battler->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed  = battler->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed  = battler->pos.z.fixed;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0xA;
    TASK(PartyMember)->timer        = 0;
    TASK(PartyMember)->header.mode += 1;

    for (count = 0; count < 8; count++) {
        slot                               = Battle_AllocEffect(1, 61);
        g_BattleEffects[slot].target.party = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].arg.unk_09   = count * 8 + 1;
        TASK(PartyMember)->param.unk_0B++;
    }
    slot                               = Battle_AllocEffect(1, 61);
    g_BattleEffects[slot].target.party = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 1;
    TASK(PartyMember)->param.unk_0B++;
    SND_SEQueueSelection(0x100);
}

MATCH void func_801EEE14(void) {
    u8            timer;
    PartyMember** selected;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        selected = &g_Battle.selected_actor;
        GFX_PaletteFreeFadeTarget(*selected);
        TASK(PartyMember)->unk_09 = GFX_PaletteAllocFade(*selected, 0, 0, 0, 1);
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEEB4(void) {
    u8 timer;

    g_PaletteFades[TASK(PartyMember)->unk_09].offset.r += 2;
    g_PaletteFades[TASK(PartyMember)->unk_09].offset.g += 1;
    g_PaletteFades[TASK(PartyMember)->unk_09].offset.b += 1;
    timer                    = TASK(PartyMember)->timer + 1;
    TASK(PartyMember)->timer = timer;
    if (timer == 8) {
        TASK(PartyMember)->header.mode++;
    }
}

#include "overlays/bmagic/shared/Effect_NextStepOnWorkLastTick.h"

MATCH void func_801EEFF8(void) {
    g_PaletteFades[TASK(PartyMember)->unk_09].offset.r -= 2;
    g_PaletteFades[TASK(PartyMember)->unk_09].offset.g -= 1;
    g_PaletteFades[TASK(PartyMember)->unk_09].offset.b -= 1;
    if (--TASK(PartyMember)->timer == 0) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        TASK(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF190 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF1D4(void) {
    Magic041Steps handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (ACTOR_IN_USE(*TASK(PartyMember)) && TASK(PartyMember)->header.step != 0) {
        BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801EF670);
    }
}

MATCH void func_801EF27C(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--TASK(PartyMember)->unk_09 == 0) {
        src                      = g_BattleEffectBattler;
        dst                      = TASK(PartyMember);
        dst->pos.x.fixed         = src->pos.x.fixed;
        dst->pos.y.fixed         = src->pos.y.fixed;
        dst->pos.z               = src->pos.z;
        dst->unk_09              = 0;
        TASK(PartyMember)->timer = 0;
        TASK(PartyMember)->header.step++;
    }
}

MATCH void func_801EF308(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(timer, 4, 32);
}

MATCH void func_801EF358(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = TASK(PartyMember);
    work->unk_09 += 4;
    work        = TASK(PartyMember);
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
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (ACTOR_IN_USE(*TASK(PartyMember)) && TASK(PartyMember)->header.step != 0) {
        BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801EFAB8);
    }
}

MATCH void func_801EF484(void) {
    PartyMember* src;

    src                            = (PartyMember*)g_BattleEffectBattler;
    TASK(PartyMember)->pos.x.fixed = src->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed = src->pos.y.fixed;
    TASK(PartyMember)->pos.z       = src->pos.z;
    TASK(PartyMember)->unk_09      = 0;
    TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
}

#include "overlays/bmagic/shared/Effect_CountUpByTwoAndStep.h"

#include "overlays/bmagic/shared/Effect_NextStepOnLastTick.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* Draws the effect's ring of 64 red quads, each joining the inner ring of jittered radius and height to the outer ring of radius 0x80. */
MATCH void func_801EF670(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      start;
    s32      x;
    s32      y;
    s32      tpage;

    g_ScratchPad.cells.halves[2] = (((rand() & 3) + TASK(PartyMember)->unk_09) & 0xF) * 256;
    start                        = g_ScratchPad.cells.halves[2];
    g_ScratchPad.cells.halves[0] = 0x80;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_09 + 160 - FIXED_MUL(rsin(start), 16);
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->timer << 3) + 32 - FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), 8);
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]), FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]), -g_ScratchPad.cells.halves[4]);
    g_ScratchPadVectors[3].vx = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vy = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vz = 0;
    g_ScratchPadVectors[3].vz = 0;
    for (i = 1; i <= 64; i++) {
        g_ScratchPad.cells.halves[2] = (((rand() & 3) + i + TASK(PartyMember)->unk_09) & 0xF) * 256;
        if (i == 64) {
            g_ScratchPad.cells.halves[2] = start;
        }
        g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_09 + 160 - FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), 16);
        g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->timer << 3) + 32 - FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), 8);
        g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz    = g_ScratchPadVectors[1].vz;
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(i << 6), g_ScratchPad.cells.halves[1]), FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[1]), -g_ScratchPad.cells.halves[4]);
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[3].vx = FIXED_MUL(rcos(i << 6), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[0]);
        x                         = (g_ScratchPadVectors[3].vx << 9) + TASK(PartyMember)->pos.x.fixed;
        y                         = (g_ScratchPadVectors[3].vx << 9) + TASK(PartyMember)->pos.y.fixed;
        tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 0xC0, 0x30, 0x30);
        setRGB3(prim, 0xC0, 0x30, 0x30);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));
    }
}

MATCH void func_801EFAB8(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = 0x88;
    g_ScratchPad.cells.halves[3] = TASK(PartyMember)->unk_09 << 3;
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
