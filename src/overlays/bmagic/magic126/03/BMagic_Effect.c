#include "magic126_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved;
    PartyMember* swap;
    s32          count;

    BMagic_DispatchTaskPair(func_801EECE4, Effect_MarkDamagedOnZeroTick);
    count = 0;
    do {
        if (D_801F12BC[(u8)count].header.flags & 0x1) {
            saved                 = g_BattleEffectBattler;
            swap                  = D_801F12BC[(u8)count].battler;
            D_801F22BC            = &D_801F12BC[(u8)count];
            g_BattleEffectBattler = swap;
            func_801F091C();
            g_BattleEffectBattler = saved;
        }
        count += 1;
    } while ((u8)count < 128);
}

MATCH void func_801EECE4(void) {
    u16 i;
    u8  slot;

    for (i = 0; i < 128; i++) {
        D_801F12BC[i].header.flags = 0;
        D_801F12BC[i].header.mode  = 0;
        D_801F12BC[i].header.step  = 0;
    }
    Battle_CenterCamera();
    Battle_ProjectRange();
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->header.mode += 1;
    for (i = 0; i < 8; i++) {
        slot                               = Battle_AllocEffect(1, 78);
        g_BattleEffects[slot].target.party = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = 2;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        TASK(PartyMember)->param.unk_0B += 1;
    }
    SND_SEQueueSelection(0x102);
    for (i = 0; i < AREA_PALETTE_COLORS; i++) {
        MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] = MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] | PSX_COLOR_STP_BIT;
    }
    g_GfxPalettePending = 1;
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEED0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF14(void) {
    SYS_DISPATCH_BYTE(D_801F1268, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Effect_SetActorMatrix();
        BMagic_DrawGlowRingOuter();
        BMagic_DrawGlowRingInner();
        func_801EF1C8();
        PopMatrix();
    }
}

#include "overlays/bmagic/shared/Effect_CopyBattlerCoords.h"

MATCH void func_801EF00C(void) {
    TASK(PartyMember)->unk_09 += 2;
    TASK(PartyMember)->timer += 24;
    if (TASK(PartyMember)->unk_09 == 0x10) {
        BMagic_NextStep();
    }
}

#include "overlays/bmagic/shared/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* The glow ring scratch: the inner and outer radius and the inner-edge colour, then the quad corners (g_ScratchPadVectors). */
#define GLOW_RING_INNER g_ScratchPad.cells.halves[0]
#define GLOW_RING_OUTER g_ScratchPad.cells.halves[1]
#define GLOW_RING_RED   g_ScratchPad.cells.halves[3]
#define GLOW_RING_GREEN g_ScratchPad.cells.halves[4]
#define GLOW_RING_BLUE  g_ScratchPad.cells.halves[5]

MATCH void func_801EF1C8(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    GLOW_RING_INNER = TASK(PartyMember)->timer * 2;
    GLOW_RING_RED   = TASK(PartyMember)->unk_09 * 12;
    GLOW_RING_GREEN = TASK(PartyMember)->unk_09 * 12;
    GLOW_RING_BLUE  = TASK(PartyMember)->unk_09 * 12;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), GLOW_RING_INNER), FIXED_MUL(rcos(0), GLOW_RING_INNER), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 32; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        GFX_STEP_TRIANGLE_FAN(i << 8, GLOW_RING_INNER);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_BLUE);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
}

/* The outer half of the glow ring: 16 additive quads from twice the effect timer (byte 0x0A) out to three
 * times it, plus a random 0 to 3 for flicker, fading out at the outer edge. */
MATCH void BMagic_DrawGlowRingOuter(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    GLOW_RING_INNER           = TASK(PartyMember)->timer * 2;
    GLOW_RING_OUTER           = TASK(PartyMember)->timer * 3 + (RANDOM_MASK(3));
    GLOW_RING_RED             = TASK(PartyMember)->unk_09 * 15;
    GLOW_RING_GREEN           = TASK(PartyMember)->unk_09 * 4;
    GLOW_RING_BLUE            = TASK(PartyMember)->unk_09 * 15;
    g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(0), GLOW_RING_INNER), FIXED_MUL(rcos(0), GLOW_RING_INNER), 0);
    g_ScratchPadVectors[2].vz = 0;
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim                      = GFX_BeginPolyG4(1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 8), GLOW_RING_OUTER);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 8), GLOW_RING_OUTER);
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 8), GLOW_RING_INNER);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 8), GLOW_RING_INNER);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_BLUE);
        setRGB3(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_BLUE);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }
}

/* The inner half: from the timer out to twice it, coloured at the outer edge where the outer half starts. */
MATCH void BMagic_DrawGlowRingInner(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    GLOW_RING_INNER           = TASK(PartyMember)->timer;
    GLOW_RING_OUTER           = TASK(PartyMember)->timer * 2;
    GLOW_RING_RED             = TASK(PartyMember)->unk_09 * 15;
    GLOW_RING_GREEN           = TASK(PartyMember)->unk_09 * 4;
    GLOW_RING_BLUE            = TASK(PartyMember)->unk_09 * 15;
    g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(0), GLOW_RING_INNER), FIXED_MUL(rcos(0), GLOW_RING_INNER), 0);
    g_ScratchPadVectors[2].vz = 0;
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim                      = GFX_BeginPolyG4(1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 8), GLOW_RING_OUTER);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 8), GLOW_RING_OUTER);
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 8), GLOW_RING_INNER);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 8), GLOW_RING_INNER);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_BLUE);
        setRGB1(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_BLUE);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }
}

MATCH void func_801EFAF4(void) {
    SYS_DISPATCH_BYTE(D_801F1278, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        func_801EFD5C();
    }
}

MATCH void func_801EFB74(void) {
    u8           timer = TASK(PartyMember)->unk_09 - 1;
    PartyMember* work;
    PartyMember* actor;
    s32          z;

    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SND_SEQueueSelection(0x100);
        work                      = TASK(PartyMember);
        actor                     = g_BattleEffectBattler;
        work->pos.x.fixed         = actor->pos.x.fixed;
        work->pos.y.fixed         = actor->pos.y.fixed;
        z                         = actor->pos.z.fixed;
        work->param.unk_0B        = 0;
        work->pos.z.fixed         = z;
        TASK(PartyMember)->unk_09 = 0x14;
        TASK(PartyMember)->timer  = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpTimersAndStep.h"

MATCH void func_801EFC94(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(unk_09, 2, 150);
}

/* func_801EFCE4 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

MATCH void func_801EFD5C(void) {
    POLY_GT4* prim;
    s32       tpage;

    g_ScratchPad.cells.halves[0] = 40;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[2] = TASK(PartyMember)->timer * 8;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[7] = TASK(PartyMember)->screen_y.value;
    tpage                        = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[0], -(g_ScratchPad.cells.halves[1] + 16) + g_ScratchPad.cells.halves[7],
           g_ScratchPad.cells.halves[6] + g_ScratchPad.cells.halves[0], -(g_ScratchPad.cells.halves[1] + 16) + g_ScratchPad.cells.halves[7],
           g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[7] - 16, g_ScratchPad.cells.halves[6] + g_ScratchPad.cells.halves[0],
           g_ScratchPad.cells.halves[7] - 16);
    setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    setClut(prim, 0, 506);
    setUV4(prim, 8, 8, 87, 8, 8, g_ScratchPad.cells.halves[1] + 8, 87, g_ScratchPad.cells.halves[1] + 8);
    GFX_SET_RGB_ALL(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_GT4));
    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[7] - 16, g_ScratchPad.cells.halves[6] + g_ScratchPad.cells.halves[0],
           g_ScratchPad.cells.halves[7] - 16, g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[6] + g_ScratchPad.cells.halves[0],
           g_ScratchPad.cells.halves[7]);
    setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    setClut(prim, 0, 506);
    setUV4(prim, 8, g_ScratchPad.cells.halves[1] + 8, 87, g_ScratchPad.cells.halves[1] + 8, 8, g_ScratchPad.cells.halves[1] + 24, 87, g_ScratchPad.cells.halves[1] + 24);
    setRGB0(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
    setRGB1(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
    setRGB2(prim, 1, 1, 1);
    setRGB3(prim, 1, 1, 1);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_GT4));
}

MATCH void func_801F01C0(void) {
    SYS_DISPATCH_BYTE(D_801F1288, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        func_801F06AC();
    }
}

MATCH void func_801F0240(void) {
    PartyMember* work;
    u8           timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        TASK(PartyMember)->facing = D_8014637C->facing;
        work                      = TASK(PartyMember);
        work->pos.x.fixed         = D_8014637C->pos.x.fixed;
        /* FAKE: retail re-reads the party cell for the next copy. */
        FAKE_BARRIER();
        work->pos.y.fixed = D_8014637C->pos.y.fixed;
        /* FAKE: retail re-reads the party cell for the next copy. */
        FAKE_BARRIER();
        work->pos.z.fixed = D_8014637C->pos.z.fixed;
        work->unk_0C      = 0x8000;
        work->unk_10      = 0;
        Effect_RotatePosition(work);
        TASK(PartyMember)->pos.x.fixed += TASK(PartyMember)->unk_0C;
        TASK(PartyMember)->pos.y.fixed += TASK(PartyMember)->unk_10;
        TASK(PartyMember)->pos.z.fixed += 0x800000;
        TASK(PartyMember)->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - TASK(PartyMember)->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - TASK(PartyMember)->pos.y.fixed);
        TASK(PartyMember)->unk_09 = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F037C(void) {
    s32 diff;
    u8  count;
    u8  scratch[16]; /* FAKE: unreferenced local pads the frame to 0x28. */

    count = TASK(PartyMember)->unk_09;
    if (count < 16) {
        TASK(PartyMember)->unk_09 = count + 4;
    }

    func_800AF2B4((BattleRange*)g_BattleEffectBattler, 0x60);
    TASK(PartyMember)->unk_10 = TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - TASK(PartyMember)->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - TASK(PartyMember)->pos.y.fixed);

    if (func_800AF66C((BattleRange*)g_BattleEffectBattler, 0xC000) != 0) {
        TASK(PartyMember)->header.step += 1;
        return;
    }

    diff                      = (TASK(PartyMember)->unk_10 & ANGLE_MASK) - (TASK(PartyMember)->unk_0C & ANGLE_MASK);
    TASK(PartyMember)->unk_10 = diff;
    if (diff < 0) {
        TASK(PartyMember)->unk_10 = ~diff + 1;
    }
    if ((u32)(TASK(PartyMember)->unk_10 - 0x601) < 0x3FF) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F0494(void) {
    u8 slot;
    u8 i;

    if (TASK(PartyMember)->param.unk_0B == 0) {
        SND_SEQueueSelection(0x101);
        slot                               = Battle_AllocEffect(1, 78);
        g_BattleEffects[slot].target.party = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffectBattler->param.unk_0B += 1;
        slot                               = Battle_AllocEffect(1, 78);
        g_BattleEffects[slot].target.party = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].arg.unk_09   = 46;
        g_BattleEffectBattler->param.unk_0B += 1;
        for (i = 0; i < 64; i++) {
            slot                         = BMagic_AllocEffect();
            D_801F12BC[slot].battler     = g_BattleEffectBattler;
            D_801F12BC[slot].header.mode = 0;
            D_801F12BC[slot].unk_04      = i;
            D_801F12BC[slot].unk_05      = ((i & 1) << 4) + (rand() & 0xF) + 24;
            g_BattleEffectBattler->param.unk_0B += 1;
        }
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    }
    TASK(PartyMember)->header.step += 1;
}

#include "overlays/bmagic/shared/Effect_TickOnTimerNegative.h"

MATCH void func_801F06AC(void) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[2] = 0;
    g_ScratchPad.cells.halves[0] = 24;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[7] = TASK(PartyMember)->screen_y.value;
    g_ScratchPad.cells.halves[3] = TASK(PartyMember)->unk_09 * D_801F1298[TASK(PartyMember)->param.unk_0B].r;
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->unk_09 * D_801F1298[TASK(PartyMember)->param.unk_0B].b;
    for (i = 0; i < 16; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY2(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
               g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        g_ScratchPad.cells.halves[2] = (i + 1) << 8;
        prim->x2                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y2                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));
    }
}

MATCH void func_801F091C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 19), 1, D_801F22BC);
}

MATCH void func_801F0960(void) {
    SYS_DISPATCH_BYTE(D_801F12AC, D_801F22BC->header.step);
    if (D_801F22BC->header.flags != 0 && D_801F22BC->header.step != 0) {
        func_801F11AC();
        BMagic_DrawMote();
    }
}

/* The effect record with the word at +0x08 as a member. */
typedef struct EffectWords {
    u8  pad_00[8];
    s32 unk_08;
} EffectWords;

MATCH void func_801F09E0(void) {
    s16* angle_cell;
    u8   timer;
    s32  angle;

    timer            = D_801F22BC->slot - 1;
    D_801F22BC->slot = timer;
    if (timer != 0) {
        return;
    }
    angle_cell                         = &D_1F800004;
    angle                              = D_801F22BC->unk_04 & 0xF;
    *angle_cell                        = angle << 8;
    g_ScratchPadHalves                 = ((D_801F22BC->unk_04 >> 4) + 1) << 3;
    D_801F22BC->unk_10                 = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_ScratchPadHalves;
    D_801F22BC->unk_14                 = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_ScratchPadHalves;
    D_801F22BC->unk_18                 = g_BattleEffectBattler->pos.z.fixed + 0x800000;
    ((EffectWords*)D_801F22BC)->unk_08 = D_801F22BC->slot = 0;
    D_801F22BC->pad_06                                    = 0;
    D_801F22BC->unk_07                                    = (u16)g_ScratchPadHalves;
    D_801F22BC->header.step += 1;
}

MATCH void func_801F0B34(void) {
    s16* angle_cell;
    s32  angle;
    u8   count;

    if (g_FrameCount & 1) {
        D_801F22BC->slot += 1;
        D_801F22BC->unk_07 += 1;
    }
    angle              = D_801F22BC->unk_04 & 0xF;
    angle_cell         = &D_1F800004;
    *angle_cell        = angle << 8;
    D_801F22BC->unk_10 = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(angle << 8)) * D_801F22BC->unk_07;
    D_801F22BC->unk_14 = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * D_801F22BC->unk_07;
    D_801F22BC->unk_18 += PARTY_MEMBER_WORD_08(D_801F22BC);
    count              = D_801F22BC->pad_06 + 1;
    D_801F22BC->pad_06 = count;
    if (count == 16) {
        D_801F22BC->header.step += 1;
    }
}

MATCH void func_801F0C7C(void) {
    s16* angle_cell;
    s32  angle;

    if (g_FrameCount & 0x1) {
        D_801F22BC->unk_07 += 1;
    }
    PARTY_MEMBER_WORD_08(D_801F22BC) += 0x80000;
    angle              = D_801F22BC->unk_04 & 0xF;
    angle_cell         = &D_1F800004;
    *angle_cell        = angle << 8;
    D_801F22BC->unk_10 = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(angle << 8)) * D_801F22BC->unk_07;
    D_801F22BC->unk_14 = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * D_801F22BC->unk_07;
    D_801F22BC->unk_18 += PARTY_MEMBER_WORD_08(D_801F22BC);
    if ((s32)PARTY_MEMBER_WORD_08(D_801F22BC) > 0x7FFFFF) {
        D_801F22BC->header.step += 1;
    }
}

MATCH void func_801F0DA4(void) {
    s16* angle_cell;
    s32  angle;
    u8   count;

    if (g_FrameCount & 0x1) {
        D_801F22BC->unk_07 += 1;
    }
    angle              = D_801F22BC->unk_04 & 0xF;
    angle_cell         = &D_1F800004;
    *angle_cell        = angle << 8;
    D_801F22BC->unk_10 = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(angle << 8)) * D_801F22BC->unk_07;
    D_801F22BC->unk_14 = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * D_801F22BC->unk_07;
    D_801F22BC->unk_18 += PARTY_MEMBER_WORD_08(D_801F22BC);
    count              = D_801F22BC->pad_06 - 1;
    D_801F22BC->pad_06 = count;
    if (count == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801F116C();
    }
}

/* The mote's quad: the screen point at unk_0C/unk_0E, half-width unk_05, height unk_05*4, coloured by unk_06*6,
 * blitted from the 0x340/0x100 page. */
MATCH void BMagic_DrawMote(void) {
    POLY_FT4* prim;

    g_ScratchPad.cells.halves[0] = MAGIC126_MOTE->unk_05;
    g_ScratchPad.cells.halves[1] = MAGIC126_MOTE->unk_05 * 4;
    g_ScratchPad.cells.halves[2] = MAGIC126_MOTE->unk_06 * 6;
    g_ScratchPad.cells.halves[6] = MAGIC126_MOTE->unk_0C;
    g_ScratchPad.cells.halves[7] = MAGIC126_MOTE->unk_0E;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(MAGIC126_MOTE->unk_10, MAGIC126_MOTE->unk_14, 2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[7] - g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[6] + g_ScratchPad.cells.halves[0],
           g_ScratchPad.cells.halves[7] - g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[7],
           g_ScratchPad.cells.halves[6] + g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[7]);
    setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    setClut(prim, 0, 506);
    setUVWH(prim, 88, 8, 16, 64);
    setRGB0(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
    Area_CellAddPrim(MAGIC126_MOTE->unk_10, MAGIC126_MOTE->unk_14, 2, sizeof(POLY_FT4));
}

/* func_801F1110 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

MATCH void func_801F116C(void) {
    D_801F22BC->header.flags = 0;
    D_801F22BC->header.mode  = 0;
    D_801F22BC->header.step  = 0;
    D_801F22BC->unk_03       = 0;
}

MATCH void func_801F11AC(void) {
    PartyMember* work;
    s16          vec[3];
    TILE_1*      primitive;

    work      = D_801F22BC;
    vec[0]    = (work->unk_10 >> 9) - AREA_CELL_ORIGIN;
    primitive = (TILE_1*)g_GfxPrimCursor;
    vec[1]    = (work->unk_14 >> 9) - AREA_CELL_ORIGIN;
    vec[2]    = -((s16)(*(u16*)((u8*)work + 0x1A)) / 2);
    SetTile1(primitive);
    RotTransPers((SVECTOR*)vec, (long*)&primitive->x0, (long*)vec, (long*)&vec[2]);
    ((s16*)&D_801F22BC->unk_0C)[0] = primitive->x0;
    ((s16*)&D_801F22BC->unk_0C)[1] = primitive->y0;
}
