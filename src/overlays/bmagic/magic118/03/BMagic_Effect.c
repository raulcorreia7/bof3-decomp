#include "magic118_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC18 */
MATCH void BMagic_UpdateBurn(void) {
    Magic118Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.mode);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.mode != 0) {
        Effect_SetActorMatrix();
        BMagic_DrawBurnFlameQuads();
        BMagic_DrawBurnFlameTris();
        PopMatrix();
    }
}

MATCH void BMagic_SpawnBurnFlames(void) {
    u32          i;
    u8           slot;
    PartyMember* actor;
    PartyMember* task;
    PartyMember* work;
    u16*         src;
    u16*         dst;

    actor = g_Battle.selected_actor;
    task  = SELF(PartyMember);
    WorldPos_Copy(&task->pos, &actor->pos);
    task->param.unk_0B = 0;
    for (i = 0; i < 8; i++) {
        slot                               = Battle_AllocEffect(1, 47);
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].arg.unk_09   = (i + 1) * 4;
        g_BattleEffects[slot].target.party = work;
        SELF(PartyMember)->param.unk_0B++;
    }
    i   = 1;
    dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (; i < 16; i++) {
        dst[i]      = src[i] | PSX_COLOR_STP_BIT;
        dst[i + 16] = src[i + 16] | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0]             = 0;
    *MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW) + 0x20) = 0;
    g_GfxPalettePending                                                      = 1;
    SND_SEQueueSelection(0x100);
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->header.mode += 1;
}

/* Counts the effect timer up; at 16 applies the damage flags 0x10 to the battlers of the target selector and advances the mode. */
/* func_801EEE20 */
MATCH void BMagic_ApplyBurnDamage(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 16) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode + 1;
    }
}

#include "overlays/bmagic/shared/Effect_NextStepOnWorkLastTick.h"

#include "overlays/bmagic/shared/Effect_CountDownTimerNextStep.h"

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEF6C */
MATCH void BMagic_UpdateBurnSprites(void) {
    SYS_DISPATCH_BYTE(D_801EFCD4, SELF(PartyMember)->header.mode);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.mode != 0) {
        BMAGIC_DRAW_IN_ACTOR_MATRIX(BMagic_DrawBurnSprites);
    }
}

MATCH void func_801EEFF4(void) {
    PartyMember* src;
    PartyMember* dst;
    s32          z;

    if (--SELF(PartyMember)->unk_09 == 0) {
        src                             = BATTLE_ACTIVE_WORK;
        dst                             = SELF(PartyMember);
        dst->pos.x.fixed                = src->pos.x.fixed;
        dst->pos.y.fixed                = src->pos.y.fixed;
        z                               = src->pos.z.fixed;
        dst->unk_20                     = 8;
        dst->timer                      = 2;
        dst->pos.z.fixed                = z;
        dst->unk_14                     = 0;
        SELF(PartyMember)->param.unk_0B = 0x10;
        SELF(PartyMember)->unk_09       = 0x20;
        SELF(PartyMember)->header.mode++;
    }
}

MATCH void func_801EF0A4(void) {
    PartyMember* work;
    s32          sum;

    work         = SELF(PartyMember);
    sum          = work->unk_20 + work->timer;
    work->unk_20 = sum;
    work->unk_14 += sum;
    work->unk_09 -= 2;
    if (SELF(PartyMember)->unk_09 == 16) {
        SELF(PartyMember)->header.mode++;
    }
}

MATCH void func_801EF108(void) {
    PartyMember* work;
    u8           timer;

    SELF(PartyMember)->param.unk_0B--;
    work         = SELF(PartyMember);
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->unk_20 += work->timer;
    work->unk_14 += work->unk_20;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B--;
        Effect_Reset();
    }
}

/* Draws the flame's ring of 32 textured quads around the effect cell, its texture row scrolling with the frame count. */
MATCH void BMagic_DrawBurnSprites(void) {
    POLY_GT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;
    s32       x;
    s32       y;

    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->param.unk_0B * 8;
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09 * 4;
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_14 + 0x20;
    g_ScratchPad.cells.halves[4] = (g_FrameCount & 0xF) << 8;
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vz    = -(g_ScratchPad.cells.halves[3] + FIXED_MUL(rsin(0), 0x20));
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), 0);
    for (i = 1; i <= 32; i++) {
        g_ScratchPad.cells.halves[4] = ((i + g_FrameCount) & 0xF) << 8;
        g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz    = g_ScratchPadVectors[1].vz;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz    = -(g_ScratchPad.cells.halves[3] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), 0x20));
        g_ScratchPadVectors[2].vx    = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[2].vz    = 0;
        g_ScratchPadVectors[3].vx    = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[3].vy    = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[3].vz    = 0;
        x                            = (g_ScratchPadVectors[1].vx << 9) + SELF(PartyMember)->pos.x.fixed;
        y                            = (g_ScratchPadVectors[1].vx << 9) + SELF(PartyMember)->pos.y.fixed;
        tpage                        = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 2, sizeof(DR_MODE));
        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
        setRGB3(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x340, 0x100);
        prim->clut  = GetClut(0, 0x1FA);
        setUV4(prim, i << 3, SELF(PartyMember)->timer * 4 + 0x20, (i << 3) + 8, SELF(PartyMember)->timer * 4 + 0x20, i << 3, SELF(PartyMember)->timer * 4 + 0x28, (i << 3) + 8,
               SELF(PartyMember)->timer * 4 + 0x28);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_CellAddPrim(x, y, 2, sizeof(POLY_GT4));
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* The dark ring scratch: the inner and outer radius and the inner-edge shade, then the quad corners
 * (g_ScratchPadVectors). */
#define DARK_RING_INNER g_ScratchPad.cells.halves[1]
#define DARK_RING_OUTER g_ScratchPad.cells.halves[2]
#define DARK_RING_SHADE g_ScratchPad.cells.halves[5]

/* A ring of 32 subtractive quads from radius 128 to 192 that darkens toward its inner edge by six times the
 * effect counter (byte 0x09), then the draw mode back to plain blending. */
MATCH void BMagic_DrawBurnFlameQuads(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256));
    DARK_RING_INNER           = 0x80;
    DARK_RING_OUTER           = 0xC0;
    DARK_RING_SHADE           = SELF(PartyMember)->unk_09 * 6;
    g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), DARK_RING_OUTER);
    g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), DARK_RING_OUTER);
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(0), DARK_RING_INNER), FIXED_MUL(rcos(0), DARK_RING_INNER), 0);
    g_ScratchPadVectors[2].vz = 0;
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 32; i++) {
        prim                      = GFX_BeginPolyG4(1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 7), DARK_RING_OUTER);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 7), DARK_RING_OUTER);
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 7), DARK_RING_INNER);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 7), DARK_RING_INNER);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, DARK_RING_SHADE, DARK_RING_SHADE, DARK_RING_SHADE);
        setRGB3(prim, DARK_RING_SHADE, DARK_RING_SHADE, DARK_RING_SHADE);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
}

MATCH void BMagic_DrawBurnFlameTris(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = 0x80;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->unk_09 * 4;
    g_ScratchPad.cells.halves[6] = SELF(PartyMember)->unk_09 * 6;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;

    for (i = 1; i <= 32; i++) {
        prim = GFX_BeginPolyG3(1);
        GFX_STEP_TRIANGLE_FAN(i << 7, g_ScratchPad.cells.halves[0]);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6]);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}
