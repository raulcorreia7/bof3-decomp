#include "magic132_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC18.h"

MATCH void func_801EEC88(void) {
    u8            slot;
    u32           i;
    u16*          dst;
    u16*          src;
    PartyMember*  work;
    PartyMember** selected;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    Battle_CenterCamera();
    slot                               = Battle_AllocEffect(1, 100);
    work                               = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 24;
    g_BattleEffects[slot].target.party = work;
    for (i = 0, dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors, src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors; i < AREA_PALETTE_COLORS; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    selected            = &g_BattleActiveActor;
    g_GfxPalettePending = 1;
    GFX_PaletteFreeFadeTarget(*selected);
    SELF(PartyMember)->timer = GFX_PaletteAllocFade(*selected, 0, 0, 0, 1);
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
}

MATCH void func_801EEDD0(void) {
    g_PaletteFades[SELF(PartyMember)->timer].offset.r++;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g++;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b++;
    if (++SELF(PartyMember)->unk_09 == 16) {
        g_BattleActiveActor->unk_29 = 2;
        SELF(PartyMember)->header.mode++;
    }
}

MATCH void func_801EEEF4(void) {
    g_PaletteFades[SELF(PartyMember)->timer].offset.r--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b--;
    if (--SELF(PartyMember)->unk_09 == 0) {
        GFX_PaletteFreeFadeTarget(g_BattleActiveActor);
        Battle_FadePoisonedBattler(g_Battle.active_battler);
        SELF(PartyMember)->unk_09 = 16;
        SELF(PartyMember)->header.mode++;
    }
}

#include "overlays/bmagic/shared/Effect_RequestTargetOnTimerZero.h"

MATCH void func_801EF0A4(void) {
    if (SELF(PartyMember)->param.unk_0B == 0xFF) {
        g_BattleActiveActor->unk_29 = 4;
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EF114 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF158(void) {
    D_801EFD5C[SELF(PartyMember)->header.step]();
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        if (SELF(PartyMember)->header.step >= 2) {
            SELF(PartyMember)->timer += 1;
        }
        func_801EF4A4();
        func_801EF5B0();
        func_801EF914();
        PopMatrix();
    }
}

MATCH void func_801EF200(void) {
    u8  timer;
    s32 z;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if ((timer & BYTE_MASK) == 0) {
        SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
        SELF(PartyMember)->unk_0C = -0x80000;
        SELF(PartyMember)->unk_10 = -0xF0000;
        Effect_RotatePosition(g_Self);
        SELF(PartyMember)->pos.x.fixed = g_AreaScrollTargetX + SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.y.fixed = g_AreaScrollTargetY + SELF(PartyMember)->unk_10;
        z                              = g_BattleEffectBattler->pos.z.fixed + 0x800000;
        SELF(PartyMember)->unk_0C      = 0x8000;
        SELF(PartyMember)->unk_10      = 0;
        SELF(PartyMember)->pos.z.fixed = z;
        Effect_RotatePosition(g_Self);
        SELF(PartyMember)->param.unk_0B = 0x1A;
        SELF(PartyMember)->unk_09       = 0x2C;
        SELF(PartyMember)->timer        = 0;
        SELF(PartyMember)->unk_1C       = 0;
        SELF(PartyMember)->unk_20       = 0x80;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF324(void) {
    PartyMember* work;
    u8           count;

    work         = SELF(PartyMember);
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    if (count == 0) {
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF388(void) {
    s32 phase;

    SELF(PartyMember)->param.unk_0B = (SELF(PartyMember)->param.unk_0B - 1) & 0x3F;
    phase                           = SELF(PartyMember)->unk_1C + 2;
    SELF(PartyMember)->unk_1C       = phase;
    if (phase == 0x80) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF3E0(void) {
    SELF(PartyMember)->param.unk_0B = (SELF(PartyMember)->param.unk_0B - 1) & 0x3F;
    SELF(PartyMember)->unk_1C -= 2;
    SELF(PartyMember)->unk_20 -= 2;
    if (SELF(PartyMember)->unk_1C == 0x20) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF44C(void) {
    SELF(PartyMember)->unk_1C -= 1;
    SELF(PartyMember)->unk_20 -= 2;
    if (SELF(PartyMember)->unk_1C == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        Effect_Reset();
    }
}

MATCH void func_801EF4A4(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    switch (SELF(PartyMember)->facing) {
        case 0:
            rot.vz = 1024;
            break;
        case 1:
            rot.vz = 2048;
            break;
        case 2:
            rot.vz = 3072;
            break;
        default:
            rot.vz = 0;
            break;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(SELF(PartyMember));
}

/* Draw the magic132 breath as a strip of 63 textured quads whose height follows a sine wave
 * running with the effect ticker, its texture rows cycling with the timer. */
MATCH void func_801EF5B0(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_20;
    g_ScratchPad.cells.halves[1] = (SELF(PartyMember)->param.unk_0B & 0x3F) << 7;
    if (SELF(PartyMember)->header.step == 4) {
        g_ScratchPad.cells.halves[2] = (SELF(PartyMember)->unk_1C / 2) << 3;
    } else {
        g_ScratchPad.cells.halves[2] = 0x80;
    }
    setVector(&g_ScratchPadVectors[2], 0, 0, FIXED_MUL(rsin(g_ScratchPad.cells.halves[1]), g_ScratchPad.cells.halves[0]));
    for (i = 1; i < 64; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[2].vz;
        setVector(&g_ScratchPadVectors[1], 0xE00, g_ScratchPadVectors[2].vy, g_ScratchPadVectors[2].vz);
        g_ScratchPad.cells.halves[1] = ((SELF(PartyMember)->param.unk_0B + i) & 0x3F) << 7;
        setVector(&g_ScratchPadVectors[2], 0, i << 6, FIXED_MUL(rsin(g_ScratchPad.cells.halves[1]), g_ScratchPad.cells.halves[0]));
        setVector(&g_ScratchPadVectors[3], 0xE00, g_ScratchPadVectors[2].vy, g_ScratchPadVectors[2].vz);
        setRGB0(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        prim->tpage                  = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 832, 256);
        prim->clut                   = GetClut(0, 506);
        g_ScratchPad.cells.halves[3] = ((SELF(PartyMember)->timer + i) % 14) * 16 + 8;
        setUV4(prim, 8, g_ScratchPad.cells.halves[3], 248, g_ScratchPad.cells.halves[3], 8, g_ScratchPad.cells.halves[3] + 16, 248, g_ScratchPad.cells.halves[3] + 16);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
    }
    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
}

/* Draw the two magic132 breath bands as shaded quads along the sine wave of the effect ticker,
 * the first tinted red at its far edge and the second at its near edge, dark at the other. */
MATCH void func_801EF914(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;
    s32      phase;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    if (SELF(PartyMember)->header.step == 4) {
        g_ScratchPad.cells.halves[2] = (SELF(PartyMember)->unk_1C / 2) << 3;
    } else {
        g_ScratchPad.cells.halves[2] = 0x80;
    }
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_20;
    phase                        = SELF(PartyMember)->param.unk_0B & 0x3F;
    g_ScratchPadVectors[2].vx    = 0;
    g_ScratchPadVectors[2].vy    = -0x80;
    g_ScratchPad.cells.halves[1] = phase << 7;
    g_ScratchPadVectors[2].vz    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[1]), g_ScratchPad.cells.halves[0]);
    for (i = 1; i < 3; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPadVectors[0].vx    = 0;
        g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[0].vz    = g_ScratchPadVectors[2].vz;
        g_ScratchPadVectors[1].vx    = 0xC00;
        g_ScratchPadVectors[1].vy    = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[1].vz    = g_ScratchPadVectors[2].vz;
        g_ScratchPad.cells.halves[1] = ((SELF(PartyMember)->param.unk_0B + i) & 0x3F) << 7;
        setVector(&g_ScratchPadVectors[2], 0, (i - 1) << 6, FIXED_MUL(rsin(g_ScratchPad.cells.halves[1]), g_ScratchPad.cells.halves[0]));
        g_ScratchPadVectors[3].vx = 0xC00;
        g_ScratchPadVectors[3].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[3].vz = g_ScratchPadVectors[2].vz;
        if (SELF(PartyMember)->header.step == 4) {
            g_ScratchPad.cells.halves[2] = (SELF(PartyMember)->unk_1C / 2) * 12;
        } else {
            g_ScratchPad.cells.halves[2] = 0xC0;
        }
        if (i == 1) {
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
            setRGB2(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2] / 4, g_ScratchPad.cells.halves[2] / 4);
            setRGB3(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2] / 4, g_ScratchPad.cells.halves[2] / 4);
        } else {
            setRGB0(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2] / 4, g_ScratchPad.cells.halves[2] / 4);
            setRGB1(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2] / 4, g_ScratchPad.cells.halves[2] / 4);
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
}
