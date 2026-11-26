#include "magic167_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_DispatchMode.h"

/* Copies the selected battler's pose into the effect, spawns one battle effect
 * at that position and eight more in a four-column grid, and queues the
 * selection sound. */
MATCH void func_801EEC94(void) {
    PartyMember* battler;
    PartyMember* target;
    u32          first_slot;
    u8           i;
    u8           slot;

    battler                         = g_BattleSelectedActor;
    TASK(PartyMember)->facing       = battler->facing;
    TASK(PartyMember)->pos.x        = battler->pos.x;
    TASK(PartyMember)->pos.y        = battler->pos.y;
    TASK(PartyMember)->pos.z        = battler->pos.z;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 16;
    TASK(PartyMember)->header.mode += 1;
    first_slot                                   = Battle_AllocEffect(1, 0x47) & BYTE_MASK;
    g_BattleEffects[first_slot].target.party     = TASK(PartyMember);
    g_BattleEffects[first_slot].header.mode      = 0;
    g_BattleEffects[first_slot].arg.unk_09       = 0;
    g_BattleEffects[first_slot].pos.x            = TASK(PartyMember)->pos.x;
    g_BattleEffects[first_slot].pos.y            = TASK(PartyMember)->pos.y;
    COORD_INT(g_BattleEffects[first_slot].pos.z) = COORD_INT(TASK(PartyMember)->pos.z);
    TASK(PartyMember)->param.unk_0B += 1;
    i = 0;
    do {
        slot                               = Battle_AllocEffect(1, 0x47);
        target                             = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = (i & 0x3) * 8;
        g_BattleEffects[slot].arg.unk_09   = ((i >> 2) * 40) + 17;
        g_BattleEffects[slot].target.party = target;
        g_BattleEffects[slot].pos.x        = TASK(PartyMember)->pos.x;
        g_BattleEffects[slot].pos.y        = TASK(PartyMember)->pos.y;
        g_BattleEffects[slot].pos.z        = TASK(PartyMember)->pos.z;
        TASK(PartyMember)->param.unk_0B += 1;
        i++;
    } while (i < 8);
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
}

/* func_801EEE88 */
#include "overlays/bmagic/shared/Effect_PreparePalette.h"

#include "overlays/bmagic/shared/Effect_BrightenPalette.h"

#include "overlays/bmagic/shared/Effect_Pause.h"

/* Darkens the palette fade row the effect timer indexes and, when its red reaches zero, releases the selected
 * battler's fades and advances the mode. */
MATCH void func_801EF080(void) {
    /* FAKE: retail frame reserves 0x10 bytes no statement uses. */
    FAKE_STACK_PADS(u8, 0x10);

    g_PaletteFades[TASK(PartyMember)->timer].offset.r -= 1;
    g_PaletteFades[TASK(PartyMember)->timer].offset.g -= 1;
    g_PaletteFades[TASK(PartyMember)->timer].offset.b -= 1;
    if (g_PaletteFades[TASK(PartyMember)->timer].offset.r == 0) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        TASK(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF2D8 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF31C(void) {
    SYS_DISPATCH_BYTE(D_801F08B8, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Effect_SetActorMatrix();
        D_1F800004 = TASK(PartyMember)->unk_09 * 5;
        func_801EF4B0();
        func_801EF708();
        PopMatrix();
    }
}

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

#include "overlays/bmagic/shared/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

MATCH void func_801EF4B0(void) {
    POLY_G3* poly;
    s32      tpage;
    s32      i;
    long     flag;
    long     depth;
    s32*     shade;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPadVectors[2].vx = (rsin(0) * 3U) >> 6;
    g_ScratchPadVectors[2].vy = (rcos(0) * 3U) >> 6;
    for (i = 1; i < 17; i++) {
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], (rsin(i << 8) * 3U) >> 6, (rcos(i << 8) * 3U) >> 6, 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        poly                      = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, &depth, &flag);
        shade = &D_1F800004;
        setRGB0(poly, *shade, *shade, *shade);
        setRGB1(poly, *shade, *shade / 2, 1);
        setRGB2(poly, *shade, *shade / 2, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801EF708(void) {
    POLY_G4* poly;
    s32      tpage;
    s32      i;
    long     depth;
    long     flag;
    s32*     shade;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPadVectors[1].vx = (rsin(0) * 3U) >> 6;
    g_ScratchPadVectors[1].vy = (rcos(0) * 3U) >> 6;
    g_ScratchPadVectors[3].vx = (u32)rsin(0) >> 4;
    g_ScratchPadVectors[3].vy = (u32)rcos(0) >> 4;
    for (i = 1; i < 17; i++) {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[1].vx = (rsin(i << 8) * 3U) >> 6;
        g_ScratchPadVectors[1].vy = (rcos(i << 8) * 3U) >> 6;
        setVector(&g_ScratchPadVectors[3], (u32)rsin(i << 8) >> 4, (u32)rcos(i << 8) >> 4, 0);
        g_ScratchPadVectors[2].vz = 0;
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        poly                      = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3,
                      &depth, &flag);
        shade = &D_1F800004;
        setRGB0(poly, *shade, *shade / 2, 1);
        setRGB1(poly, *shade, *shade / 2, 1);
        setRGB2(poly, 1, 1, 1);
        setRGB3(poly, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801EF9B8(void) {
    SYS_DISPATCH_BYTE(D_801F08C4, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Effect_SetActorMatrix();
        if (TASK(PartyMember)->header.step < 3) {
            func_801EFC44();
        }
        func_801F05C8(2);
        func_801F05C8(3);
        PopMatrix();
    }
}

MATCH void func_801EFA70(void) {
    u8 timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        TASK(PartyMember)->timer       = 1;
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EFACC(void) {
    u8 timer;

    TASK(PartyMember)->param.unk_0B += 2;
    TASK(PartyMember)->unk_09 += 1;
    timer = TASK(PartyMember)->timer;
    if (timer < 16U) {
        TASK(PartyMember)->timer = timer + 1;
    }
    if (TASK(PartyMember)->unk_09 == 0x18) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFB5C(void) {
    TASK(PartyMember)->param.unk_0B += 2;
    TASK(PartyMember)->unk_09 += 1;
    TASK(PartyMember)->timer -= 1;
    if (TASK(PartyMember)->unk_09 == 0x28) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFBE4(void) {
    PartyMember* work;
    u8           next;

    work        = TASK(PartyMember);
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0x18) {
        g_BattleEffectBattler->param.unk_0B--;
        Effect_Reset();
    }
}

/* Draws the Last Resort trail: every tick of the effect timer joins the rim point it turns to to the rim point the
 * previous tick left, four semi-transparent Gouraud quads around the join in two area cell packets. */
/* func_801EFC44 */
#ifdef NON_MATCHING
NON_MATCHING void func_801EFC44(void) {
    POLY_G4* poly;
    long     depth;
    long     flag;
    SVECTOR  rim;
    s32      fade;
    s32      i;
    s32      join;
    s32      shade;
    s32      span;
    s32      tpage;
    s32      x;
    s32      y;

    g_ScratchPad.cells.words[3]                  = (TASK(PartyMember)->param.unk_0B & 0x1F) << 7;
    g_ScratchPad.cells.words[0] = 0xC0 - TASK(PartyMember)->unk_09 * 2;
    g_ScratchPad.cells.words[2]                  = -(TASK(PartyMember)->unk_09 * 12);
    join                        = TASK(PartyMember)->timer * 2;
    rim.vx                      = FIXED_MUL(rsin(g_ScratchPad.cells.words[3]), g_ScratchPad.cells.words[0]);
    rim.vy                      = FIXED_MUL(rcos(g_ScratchPad.cells.words[3]), g_ScratchPad.cells.words[0]);
    rim.vz                      = g_ScratchPad.cells.words[2];
    for (i = 1; i < TASK(PartyMember)->timer; i++) {
        g_ScratchPad.cells.words[3]                  = ((TASK(PartyMember)->param.unk_0B - i) & 0x1F) << 7;
        g_ScratchPad.cells.words[0] = 0xC0 - (TASK(PartyMember)->unk_09 - i) * 2;
        g_ScratchPad.cells.words[2]                  = -((TASK(PartyMember)->unk_09 - i) * 12);
        span                        = TASK(PartyMember)->timer * 3 - i / 2;

        /* The join face: this tick's rim against the rim point the previous tick left. */
        g_ScratchPadVectors[1].vx = rim.vx;
        g_ScratchPadVectors[1].vy = rim.vy;
        g_ScratchPadVectors[3].vx = rim.vx;
        g_ScratchPadVectors[3].vy = rim.vy;
        g_ScratchPadVectors[1].vz = rim.vz - join;
        g_ScratchPadVectors[3].vz = rim.vz - join / 2;
        g_ScratchPadVectors[0].vx = FIXED_MUL(rsin(g_ScratchPad.cells.words[3]), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(g_ScratchPad.cells.words[3]), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[0].vz = g_ScratchPad.cells.words[2] - span;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[0].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz = g_ScratchPad.cells.words[2] - span / 2;
        x                         = (g_ScratchPadVectors[3].vx << 9) + TASK(PartyMember)->pos.x.fixed;
        y                         = (g_ScratchPadVectors[3].vy << 9) + TASK(PartyMember)->pos.y.fixed;
        tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
        poly = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3,
                      &depth, &flag);
        if (TASK(PartyMember)->header.step == 2) {
            /* The last tick darkens the join with the depth it has covered. */
            fade       = TASK(PartyMember)->unk_09 + i - 24;
            g_ScratchPad.cells.words[1] = fade;
            if (fade >= 17) {
                fade       = 15;
                g_ScratchPad.cells.words[1] = fade;
            }
            shade      = 0xC0 - fade * 12;
            g_ScratchPad.cells.words[1] = 0x30 - g_ScratchPad.cells.words[1] * 3;
        } else {
            g_ScratchPad.cells.words[1] = 0x30 - i * 3;
            shade      = 0xC0 - i * 12;
        }
        setRGB0(poly, 1, 1, 1);
        setRGB1(poly, 1, 1, 1);
        setRGB2(poly, shade, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
        if (i == 1) {
            setRGB3(poly, i, i, i);
        } else {
            setRGB3(poly, shade, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
        }
        Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));

        /* The near side of the join. */
        g_ScratchPadVectors[1].vx = rim.vx;
        g_ScratchPadVectors[1].vy = rim.vy;
        g_ScratchPadVectors[3].vx = rim.vx;
        g_ScratchPadVectors[3].vy = rim.vy;
        g_ScratchPadVectors[1].vz = rim.vz - join / 2;
        g_ScratchPadVectors[3].vz = rim.vz;
        g_ScratchPadVectors[0].vx = FIXED_MUL(rsin(g_ScratchPad.cells.words[3]), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(g_ScratchPad.cells.words[3]), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[0].vz = g_ScratchPad.cells.words[2] - span / 2;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[0].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz = g_ScratchPad.cells.words[2];
        poly                      = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3,
                      &depth, &flag);
        setRGB0(poly, shade, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
        setRGB1(poly, shade, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
        setRGB2(poly, shade, shade, shade);
        setRGB3(poly, shade, shade, shade);
        Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));

        /* The far side of the join. */
        g_ScratchPadVectors[1].vx = rim.vx;
        g_ScratchPadVectors[1].vy = rim.vy;
        g_ScratchPadVectors[3].vx = rim.vx;
        g_ScratchPadVectors[3].vy = rim.vy;
        g_ScratchPadVectors[1].vz = rim.vz;
        g_ScratchPadVectors[3].vz = rim.vz + join / 2;
        g_ScratchPadVectors[0].vx = FIXED_MUL(rsin(g_ScratchPad.cells.words[3]), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(g_ScratchPad.cells.words[3]), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[0].vz = g_ScratchPad.cells.words[2];
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[0].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz = g_ScratchPad.cells.words[2] + span / 2;
        poly                      = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3,
                      &depth, &flag);
        setRGB0(poly, shade, shade, shade);
        setRGB1(poly, shade, shade, shade);
        setRGB2(poly, shade, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
        setRGB3(poly, shade, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
        Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));

        /* The outer face of the join, in a second packet, which leaves this tick's rim for the next tick. */
        g_ScratchPadVectors[1].vx = rim.vx;
        g_ScratchPadVectors[1].vy = rim.vy;
        g_ScratchPadVectors[3].vx = rim.vx;
        g_ScratchPadVectors[3].vy = rim.vy;
        g_ScratchPadVectors[1].vz = rim.vz + join / 2;
        g_ScratchPadVectors[3].vz = rim.vz + join;
        g_ScratchPadVectors[0].vx = FIXED_MUL(rsin(g_ScratchPad.cells.words[3]), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(g_ScratchPad.cells.words[3]), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[0].vz = g_ScratchPad.cells.words[2] + span / 2;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[0].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz = g_ScratchPad.cells.words[2] + span;
        rim.vx                    = g_ScratchPadVectors[0].vx;
        rim.vy                    = g_ScratchPadVectors[0].vy;
        rim.vz                    = g_ScratchPad.cells.words[2];
        tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
        poly = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3,
                      &depth, &flag);
        setRGB0(poly, shade, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
        if (i == 1) {
            setRGB1(poly, i, i, i);
        } else {
            setRGB1(poly, shade, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
        }
        setRGB2(poly, 1, 1, 1);
        setRGB3(poly, 1, 1, 1);
        Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));
        join = span;
    }
}
#else
INCLUDE_ASM(func_801EFC44);
#endif

MATCH void func_801F05C8(s32 step) {
    TILE_1*      primitive;
    PartyMember* work;
    s32*         angle;
    s32*         shade;
    s32          tpage;
    s32          i;
    s32          rise;
    s32          height;
    s32          turn;
    s32          jitter;
    s32          x;
    s32          y;
    long         p;
    long         flag;

    /* The angle word sits three scratch words after the radius word; the depth word lies between them. */
    i     = 1;
    angle = &D_1F80000C;
    for (; i < 24; i += step) {
        if (i >= TASK(PartyMember)->unk_09) {
            break;
        }
        if (TASK(PartyMember)->header.step == 3) {
            if (TASK(PartyMember)->timer + i >= 25) {
                break;
            }
            jitter     = rand();
            rise       = (TASK(PartyMember)->timer + i) * (step + 2);
            D_1F800004 = 0x80 - (TASK(PartyMember)->timer + i) * 5;
            height     = rise + (jitter & 3);
        } else {
            jitter     = rand();
            rise       = i * (step + 2);
            D_1F800004 = 0x80 - i * 5;
            height     = rise + (jitter & 3);
        }
        work                      = TASK(PartyMember);
        turn                      = ((work->param.unk_0B - i) & 0x1F) << 7;
        angle[0]                  = turn;
        angle[-3]                 = 0xC0 - (work->unk_09 - i) * 2;
        angle[-1]                 = -((work->unk_09 - i) * 12);
        g_ScratchPadVectors[0].vx = FIXED_MUL(rsin(turn), angle[-3]);
        g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(angle[0]), angle[-3]);
        g_ScratchPadVectors[0].vz = angle[-1] + height + 8;
        if (g_ScratchPadVectors[0].vz > 0) {
            g_ScratchPadVectors[0].vz = 0;
        }
        x     = (g_ScratchPadVectors[0].vx << 9) + TASK(PartyMember)->pos.x.fixed;
        y     = (g_ScratchPadVectors[0].vy << 9) + TASK(PartyMember)->pos.y.fixed;
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
        primitive = (TILE_1*)g_GfxPrimCursor;
        SetTile1(primitive);
        SetSemiTrans(primitive, 1);
        RotTransPers(g_ScratchPadVectors, (long*)&primitive->x0, &p, &flag);
        shade = &D_1F800004;
        setRGB0(primitive, *shade, *shade, *shade);
        /* Retail advances the cell by 0x24 bytes here, more than the tile takes. */
        Area_CellAddPrim(x, y, 0, 0x24);
    }
}
