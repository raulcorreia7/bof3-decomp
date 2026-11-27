#include "magic086_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_DispatchMode.h"

MATCH void func_801EEC94(void) {
    PartyMember* actor;
    PartyMember* task;
    u8           slot;

    actor                                  = g_Battle.selected_actor;
    task                                   = SELF(PartyMember);
    task->pos.x.fixed                      = actor->pos.x.fixed;
    task->pos.y.fixed                      = actor->pos.y.fixed;
    task->pos.z.fixed                      = actor->pos.z.fixed;
    slot                                   = Battle_AllocEffect(1, 29);
    g_BattleEffects[slot].target.party     = SELF(PartyMember);
    g_BattleEffects[slot].header.mode      = 0;
    g_BattleEffects[slot].arg.unk_09       = 0;
    g_BattleEffects[slot].unk_0A           = 0;
    g_BattleEffects[slot].pos.x            = SELF(PartyMember)->pos.x;
    g_BattleEffects[slot].pos.y            = SELF(PartyMember)->pos.y;
    COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(SELF(PartyMember)->pos.z);
    slot                                   = Battle_AllocEffect(1, 29);
    g_BattleEffects[slot].target.party     = SELF(PartyMember);
    g_BattleEffects[slot].header.mode      = 1;
    g_BattleEffects[slot].unk_0B           = 48;
    g_BattleEffects[slot].arg.unk_09       = 0;
    g_BattleEffects[slot].unk_0A           = 0;
    g_BattleEffects[slot].pos.x            = SELF(PartyMember)->pos.x;
    g_BattleEffects[slot].pos.y            = SELF(PartyMember)->pos.y;
    COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(SELF(PartyMember)->pos.z);
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
}

MATCH void func_801EEE44(void) {
    PartyMember* battler;

    battler = g_Battle.selected_actor;
    if (SELF(PartyMember)->param.unk_0B == 1) {
        GFX_PaletteFreeFadeTarget(battler);
        SELF(PartyMember)->timer  = GFX_PaletteAllocFade(battler, 1, 1, 1, 0);
        SELF(PartyMember)->unk_09 = 0x10;
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_BrightenPalette.h"

MATCH void func_801EEFF0(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    if (work->param.unk_0B == 2) {
        work->header.mode = (work->header.mode + 1);
    }
}

MATCH void func_801EF024(void) {
    PartyMember* battler;

    battler = g_Battle.selected_actor;
    g_PaletteFades[SELF(PartyMember)->timer].offset.r--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b--;
    if (g_PaletteFades[SELF(PartyMember)->timer].offset.r == 0) {
        func_80196718(battler);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        SELF(PartyMember)->header.mode++;
    }
}

#include "overlays/bmagic/shared/Effect_PlayOnIdleTick.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF278 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF2BC(void) {
    SYS_DISPATCH_BYTE(D_801F0360, SELF(PartyMember)->header.step);
    BMAGIC_DRAW_IF_ALIVE(func_801EF424);
}

MATCH void func_801EF334(void) {
    SELF(PartyMember)->unk_09 += 1;
    SELF(PartyMember)->timer += 1;
    if (SELF(PartyMember)->unk_09 == 0x10) {
        BMagic_NextStep();
    }
}

MATCH void func_801EF3A0(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 2) {
        work              = SELF(PartyMember);
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EF3E0(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        Effect_Reset();
    }
}

MATCH void func_801EF424(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    D_1F800000_WORD[0]        = SELF(PartyMember)->timer * 12;
    g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(0), D_1F800000_WORD[0]);
    g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(0), D_1F800000_WORD[0]);

    for (i = 1; i <= 32; i++) {
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(i << 7), D_1F800000_WORD[0]), FIXED_MUL(rcos(i << 7), D_1F800000_WORD[0]), 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        prim                      = GFX_BeginPolyG3(1);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, SELF(PartyMember)->unk_09 * 6, SELF(PartyMember)->unk_09 * 6, SELF(PartyMember)->unk_09 * 4);
        setRGB1(prim, SELF(PartyMember)->unk_09 * 4, SELF(PartyMember)->unk_09 * 4, SELF(PartyMember)->unk_09 * 2);
        setRGB2(prim, prim->r1, prim->g1, prim->b1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801EF70C(void) {
    SYS_DISPATCH_BYTE(D_801F036C, SELF(PartyMember)->header.step);
    BMAGIC_DRAW_IF_ALIVE(func_801EF9E0);
}

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

MATCH void func_801EF7D4(void) {
    u8 count;

    SELF(PartyMember)->timer += 1;
    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x18) {
        g_BattleEffectBattler->param.unk_0B = 1;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF850(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(timer, 1, 22);
}

#include "overlays/bmagic/shared/Effect_CountDownTickerAndStep.h"

MATCH void func_801EF8EC(void) {
    SELF(PartyMember)->unk_09 -= 1;
    SELF(PartyMember)->timer -= 1;
    if (SELF(PartyMember)->unk_09 == 0x10) {
        g_BattleEffectBattler->param.unk_0B = 2;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF974(void) {
    u8 count;
    u8 timer_next;

    count = SELF(PartyMember)->unk_09;
    if (count != 0) {
        SELF(PartyMember)->unk_09 = count - 1;
    }
    timer_next               = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        Effect_Reset();
    }
}

/* Draws a ring of 64 semi-transparent Gouraud quads between the radii in scratch words 0 and 1. While the effect is
 * past its first step, the quads away from the two eighths that g_FrameCount picks become a green wall raised by
 * scratch word 3 and a sine wave, each one placed in its area cell. */
MATCH void func_801EF9E0(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32      i;
    s32      spark;
    s32      next;
    s32      x;
    s32      y;
    s32      wave;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    if (SELF(PartyMember)->header.step != 0) {
        D_1F800000_WORD[0] = 0xC0;
    } else {
        D_1F800000_WORD[0] = SELF(PartyMember)->unk_09 * 12;
    }
    D_1F800000_WORD[1] = SELF(PartyMember)->unk_09 * 14;
    D_1F800000_WORD[3] = SELF(PartyMember)->timer << 4;
    spark              = g_FrameCount & 7;
    next               = (g_FrameCount + 1) & 7;
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rcos(0), D_1F800000_WORD[0]), FIXED_MUL(rsin(0), D_1F800000_WORD[0]), 0);
    for (i = 1; i <= 64; i++) {
        if ((i & 7) == spark || (i & 7) == next || SELF(PartyMember)->header.step == 0) {
            g_ScratchPadVectors[0].vx = FIXED_MUL(rcos((i - 1) << 6), D_1F800000_WORD[1]);
            g_ScratchPadVectors[0].vy = FIXED_MUL(rsin((i - 1) << 6), D_1F800000_WORD[1]);
            g_ScratchPadVectors[0].vz = 0;
            setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(i << 6), D_1F800000_WORD[1]), FIXED_MUL(rsin(i << 6), D_1F800000_WORD[1]), 0);
            setVector(&g_ScratchPadVectors[2], g_ScratchPadVectors[3].vx, g_ScratchPadVectors[3].vy, 0);
            setVector(&g_ScratchPadVectors[3], FIXED_MUL(rcos(i << 6), D_1F800000_WORD[0]), FIXED_MUL(rsin(i << 6), D_1F800000_WORD[0]), 0);
        } else {
            wave                      = ((i + g_FrameCount) & 0x1F) << 7;
            g_ScratchPadVectors[0].vx = FIXED_MUL(rcos((i - 1) << 6), D_1F800000_WORD[0]);
            g_ScratchPadVectors[0].vy = FIXED_MUL(rsin((i - 1) << 6), D_1F800000_WORD[0]);
            g_ScratchPadVectors[0].vz = -(D_1F800000_WORD[3] + FIXED_MUL(rsin(wave), 32));
            g_ScratchPadVectors[1].vx = FIXED_MUL(rcos(i << 6), D_1F800000_WORD[0]);
            g_ScratchPadVectors[1].vy = FIXED_MUL(rsin(i << 6), D_1F800000_WORD[0]);
            g_ScratchPadVectors[1].vz = -(D_1F800000_WORD[3] + FIXED_MUL(rsin(wave), 32));
            g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[2].vz = 0;
            g_ScratchPadVectors[3].vx = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[3].vy = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[3].vz = 0;
            x                         = (g_ScratchPadVectors[3].vx << 9) + SELF(PartyMember)->pos.x.fixed;
            y                         = (g_ScratchPadVectors[3].vy << 9) + SELF(PartyMember)->pos.y.fixed;
            tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
        }
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        if ((i & 7) == spark || (i & 7) == next || SELF(PartyMember)->header.step == 0) {
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
            setRGB2(prim, SELF(PartyMember)->unk_09 * 2, SELF(PartyMember)->unk_09 * 2, SELF(PartyMember)->unk_09);
            setRGB3(prim, SELF(PartyMember)->unk_09 * 2, SELF(PartyMember)->unk_09 * 2, SELF(PartyMember)->unk_09);
            GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
        } else {
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
            setRGB2(prim, 0x20, 0xC0, 0x20);
            setRGB3(prim, 0x20, 0xC0, 0x20);
            Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));
        }
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801F0038(void) {
    BMAGIC_DISPATCH_AND_DRAW(D_801F0384, func_801F01A8);
}

#include "overlays/bmagic/shared/Effect_NextStepOnLastTick.h"

MATCH void func_801F0100(void) {
    u8 count;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        SELF(PartyMember)->unk_14 = 0x20;
        SELF(PartyMember)->unk_20 = -1;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F0154(void) {
    s32 dz;

    dz                                  = SELF(PartyMember)->unk_14 + SELF(PartyMember)->unk_20;
    SELF(PartyMember)->unk_14           = dz;
    COORD_INT(SELF(PartyMember)->pos.z) = COORD_INT(SELF(PartyMember)->pos.z) + dz;
    if (SELF(PartyMember)->unk_14 < -0x10) {
        Effect_Reset();
    }
}

MATCH void func_801F01A8(void) {
    LINE_G3* prim;
    s32      tpage;
    long     depth;
    long     flag;

    setVector(&g_ScratchPadVectors[0], g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = rsin(SELF(PartyMember)->param.unk_0B << 9) >> 5,
              g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = rcos(SELF(PartyMember)->param.unk_0B << 9) >> 5, 32);
    g_ScratchPadVectors[1].vz = 24;
    g_ScratchPadVectors[2].vz = 0;
    tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (LINE_G3*)g_GfxPrimCursor;
    SetLineG3(prim);
    SetSemiTrans(prim, 1);
    RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    setRGB0(prim, 0x40, 0x40, 0x40);
    setRGB1(prim, 0xC0, 0x80, 0x80);
    setRGB2(prim, 1, 1, 1);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(LINE_G3));
}
