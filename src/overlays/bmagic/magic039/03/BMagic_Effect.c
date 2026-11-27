#include "magic039_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC94(void) {
    u8   i;
    u8   slot;
    u16* dst;
    u16* src;

    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->unk_04       = func_801EEF3C();
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
    slot = Battle_AllocEffect(1, 59);
    {
        PartyMember* work;

        work                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_04       = SELF(PartyMember)->unk_04 - 2;
    }
    SELF(PartyMember)->param.unk_0B += 1;
    for (i = 0; i < 8; i++) {
        PartyMember* work;

        slot                               = Battle_AllocEffect(1, 59);
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_04       = SELF(PartyMember)->unk_04 - 2;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = D_801F041C[i] + 9;
        SELF(PartyMember)->param.unk_0B += 1;
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/shared/Effect_NextStepOnZeroTick.h"

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

MATCH s32 func_801EEF3C(void) {
    switch (g_Battle.action_id) {
        case ABILITY_FOCUS:
        default:
            return 2;
        case ABILITY_MEDITATION:
            return 3;
    }
}

/* func_801EEF64 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFA8(void) {
    BMagicEffectSteps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if ((SELF(PartyMember)->header.flags & 0x1) && SELF(PartyMember)->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFAA4();
        func_801F0054();
        PopMatrix();
    }
}

MATCH void func_801EF070(void) {
    PartyMember* src;

    src                            = (PartyMember*)g_BattleEffectBattler;
    SELF(PartyMember)->pos.x.fixed = src->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = src->pos.y.fixed;
    SELF(PartyMember)->pos.z       = src->pos.z;
    SELF(PartyMember)->unk_09      = 0;
    SELF(PartyMember)->timer       = 1;
    SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
}

MATCH void func_801EF0D4(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 + 2;
    SELF(PartyMember)->unk_09 = timer;
    if ((timer & BYTE_MASK) == 16) {
        SELF(PartyMember)->timer = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF134(void) {
    u8            timer_next;
    PartyMember** selected;

    SELF(PartyMember)->unk_09 += 1;
    timer_next               = SELF(PartyMember)->timer + 2;
    SELF(PartyMember)->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 0x18) {
        selected = &g_Battle.selected_actor;
        GFX_PaletteFreeFadeTarget(*selected);
        SELF(PartyMember)->param.unk_0B = GFX_PaletteAllocFade(*selected, 0, 0, 0, 1);
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF1F4(void) {
    SELF(PartyMember)->unk_09 += 1;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r += 2;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.g += 2;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.b += 2;
    if (g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r == 0x10) {
        SELF(PartyMember)->header.step += 1;
    }
}

/* Counts the effect counter up and fades the palette row the effect claimed down to zero, then steps. */
MATCH void func_801EF320(void) {
    SELF(PartyMember)->unk_09 += 1;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r -= 2;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.g -= 2;
    g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.b -= 2;
    if (g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r == 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF44C(void) {
    u8 timer_next;

    SELF(PartyMember)->unk_09 += 1;
    timer_next               = SELF(PartyMember)->timer - 2;
    SELF(PartyMember)->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void func_801EF4E4(void) {
    Magic039Steps handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (ACTOR_IN_USE(*SELF(PartyMember)) && SELF(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        func_801EF758();
    }
}

MATCH void func_801EF584(void) {
    PartyMember* work;
    s16*         angle_cell;
    u8           count;
    u8           phase;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        phase                                   = SELF(PartyMember)->param.unk_0B;
        angle_cell                              = &g_ScratchPad.cells.halves[5];
        *angle_cell                             = phase << 9;
        SELF(PartyMember)->pos.x.fixed          = g_BattleEffectBattler->pos.x.fixed + ((rcos((s16)(phase << 9)) * 0xC000) >> 12);
        (work = SELF(PartyMember))->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rsin(*angle_cell) * 0xC000) >> 12);
        work->pos.z.fixed                       = g_BattleEffectBattler->pos.z.fixed;
        work->unk_09                            = 0;
        SELF(PartyMember)->timer                = 4;
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF690(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(unk_09, 16, 128);
}

MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(8);
}

/* Draw the effect as a shaded box above its screen point, white at the top edge and tinted
 * at the bottom by the colour row the effect picks. */
MATCH void func_801EF758(void) {
    POLY_G4* prim;
    s32      tpage;

    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[6] = SELF(PartyMember)->screen_y.value;
    g_ScratchPad.cells.halves[0] = D_801F040C[SELF(PartyMember)->unk_04][0];
    g_ScratchPad.cells.halves[1] = D_801F040C[SELF(PartyMember)->unk_04][1];
    g_ScratchPad.cells.halves[2] = D_801F040C[SELF(PartyMember)->unk_04][2];
    tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[5] + g_ScratchPad.cells.halves[4],
           g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[5] - g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[6],
           g_ScratchPad.cells.halves[5] + g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[6]);
    setRGB0(prim, 1, 1, 1);
    setRGB1(prim, 1, 1, 1);
    setRGB2(prim, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[2]);
    setRGB3(prim, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[2]);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 0, sizeof(POLY_G4));
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* Draw the magic039 flame as 64 shaded quads round the effect, each with a random wobble in its
 * height and outer radius, dark at the base and tinted at the top by the colour row it picks. */
MATCH void func_801EFAA4(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      x;
    s32      y;
    s32      tpage;
    s32      wobble;

    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[5] = (((rand() & 3) + SELF(PartyMember)->unk_09) & 0xF) * 256;
    g_ScratchPad.cells.halves[3] = FIXED_MUL(rsin(g_ScratchPad.cells.halves[5]) << 1, g_ScratchPad.cells.halves[4]) - g_ScratchPad.cells.halves[4] * 6;
    g_ScratchPad.cells.halves[6] = 0x80;
    wobble                       = FIXED_MUL(rsin(g_ScratchPad.cells.halves[5]) << 2, g_ScratchPad.cells.halves[4]) - 0x80;
    g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[4] * 8 - wobble;
    if (SELF(PartyMember)->unk_09 < 16) {
        g_ScratchPad.cells.halves[0] = D_801F0414[SELF(PartyMember)->unk_04][0] * SELF(PartyMember)->unk_09;
        g_ScratchPad.cells.halves[1] = D_801F0414[SELF(PartyMember)->unk_04][1] * SELF(PartyMember)->unk_09;
        g_ScratchPad.cells.halves[2] = D_801F0414[SELF(PartyMember)->unk_04][2] * SELF(PartyMember)->unk_09;
    } else {
        g_ScratchPad.cells.halves[0] = D_801F0414[SELF(PartyMember)->unk_04][0] * 16;
        g_ScratchPad.cells.halves[1] = D_801F0414[SELF(PartyMember)->unk_04][1] * 16;
        g_ScratchPad.cells.halves[2] = D_801F0414[SELF(PartyMember)->unk_04][2] * 16;
    }
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[7]), FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[3]);
    g_ScratchPadVectors[3].vx = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[6]);
    g_ScratchPadVectors[3].vy = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[6]);
    g_ScratchPadVectors[2].vz = 0;
    g_ScratchPadVectors[3].vz = 0;
    for (i = 1; i <= 64; i++) {
        g_ScratchPad.cells.halves[5] = (((rand() & 3) + i + SELF(PartyMember)->unk_09) & 0xF) * 256;
        g_ScratchPad.cells.halves[3] = FIXED_MUL(rsin(g_ScratchPad.cells.halves[5]) << 1, g_ScratchPad.cells.halves[4]) - g_ScratchPad.cells.halves[4] * 6;
        wobble                       = FIXED_MUL(rsin(g_ScratchPad.cells.halves[5]) << 2, g_ScratchPad.cells.halves[4]) - 0x80;
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[4] * 8 - wobble;
        g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz    = g_ScratchPadVectors[1].vz;
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(i << 6), g_ScratchPad.cells.halves[7]), FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[3]);
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[3].vx = FIXED_MUL(rcos(i << 6), g_ScratchPad.cells.halves[6]);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[6]);
        x                         = (g_ScratchPadVectors[3].vx << 9) + SELF(PartyMember)->pos.x.fixed;
        y                         = (g_ScratchPadVectors[3].vx << 9) + SELF(PartyMember)->pos.y.fixed;
        tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[2]);
        setRGB3(prim, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[2]);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));
    }
}

/* Draw the magic039 disc as a fan of sixteen shaded triangles, white at the centre and tinted at
 * the rim by the colour row the effect picks, the tint growing with the effect size up to 16. */
MATCH void func_801F0054(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[3] = 0x88;
    if (SELF(PartyMember)->unk_09 < 16) {
        g_ScratchPad.cells.halves[0] = D_801F0404[SELF(PartyMember)->unk_04][0] * SELF(PartyMember)->unk_09;
        g_ScratchPad.cells.halves[1] = D_801F0404[SELF(PartyMember)->unk_04][1] * SELF(PartyMember)->unk_09;
        g_ScratchPad.cells.halves[2] = D_801F0404[SELF(PartyMember)->unk_04][2] * SELF(PartyMember)->unk_09;
    } else {
        g_ScratchPad.cells.halves[0] = D_801F0404[SELF(PartyMember)->unk_04][0] * 16;
        g_ScratchPad.cells.halves[1] = D_801F0404[SELF(PartyMember)->unk_04][1] * 16;
        g_ScratchPad.cells.halves[2] = D_801F0404[SELF(PartyMember)->unk_04][2] * 16;
    }
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[3]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[3]), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        GFX_STEP_TRIANGLE_FAN(i << 8, g_ScratchPad.cells.halves[3]);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[2]);
        setRGB2(prim, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[2]);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}
