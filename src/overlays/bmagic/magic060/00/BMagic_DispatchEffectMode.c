#include "magic060_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EFF44 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EFF88(void) {
    SYS_DISPATCH_BYTE(D_801F0BBC, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        func_801F012C();
    }
}

#include "overlays/bmagic/shared/Effect_ClearTimerNextStep.h"

MATCH void func_801F0030(void) {
    u8 count;

    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        g_BattleEffectBattler->param.unk_0B = 1;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F0090(void) {
    PartyMember* work;

    MAGIC060_ADVANCE_AT_EFFECT_PARAM(0x83);
}

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

/* The shade the screen tile fades to. */
#define SCREEN_SHADE g_ScratchPad.cells.words[1]

MATCH void func_801F012C(void) {
    TILE* tile;

    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    tile->w      = SCREEN_WIDTH;
    tile->y0     = 0;
    tile->x0     = 0;
    tile->h      = SCREEN_HEIGHT;
    SCREEN_SHADE = SELF(PartyMember)->unk_09;
    setRGB0(tile, SCREEN_SHADE, SCREEN_SHADE, SCREEN_SHADE);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(TILE));
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
}

MATCH void func_801F0254(void) {
    SYS_DISPATCH_BYTE(D_801F0BCC, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        func_801F0428();
    }
}

MATCH void func_801F02CC(void) {
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        SELF(PartyMember)->unk_09 = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F031C(void) {
    u8 count;

    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x1E) {
        g_BattleEffectBattler->param.unk_0B = 2;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F037C(void) {
    PartyMember* work;

    MAGIC060_ADVANCE_AT_EFFECT_PARAM(0x83);
}

MATCH void func_801F03BC(void) {
    PartyMember* active;

    SELF(PartyMember)->unk_09 = SELF(PartyMember)->unk_09 - 2;
    if (SELF(PartyMember)->unk_09 == 0) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = active->param.unk_0B - 1;
        Effect_Reset();
    }
}

/* Draws the turning grey square at the screen centre: four corners a quarter turn apart
 * on a circle that grows with byte 0x09, shaded by a third of it. */
MATCH void func_801F0428(void) {
    POLY_G4* prim;
    u8       shade;

    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256));
    prim                        = GFX_BeginPolyG4(1);
    g_ScratchPad.cells.words[0] = SELF(PartyMember)->unk_09 * 3 + 18;
    g_ScratchPad.cells.words[2] = ((SELF(PartyMember)->unk_09 + 6) & 0x1F) << 7;
    setXY0(prim, FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]) + 160, FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]) + 120);
    g_ScratchPad.cells.words[2] = ((SELF(PartyMember)->unk_09 + 14) & 0x1F) << 7;
    prim->x1                    = FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]) + 160;
    prim->y1                    = FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]) + 120;
    g_ScratchPad.cells.words[2] = ((SELF(PartyMember)->unk_09 + 30) & 0x1F) << 7;
    prim->x2                    = FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]) + 160;
    prim->y2                    = FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]) + 120;
    g_ScratchPad.cells.words[2] = ((SELF(PartyMember)->unk_09 + 22) & 0x1F) << 7;
    prim->x3                    = FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]) + 160;
    prim->y3                    = FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]) + 120;
    shade                       = SELF(PartyMember)->unk_09 / 3;
    g_ScratchPad.cells.words[1] = shade * 6;
    GFX_SET_RGB_ALL(prim, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
}

MATCH void func_801F07E8(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 11, 2, g_Self);
}

MATCH void func_801F082C(void) {
    PartyMember** actor;

    actor = &g_Battle.selected_actor;
    GFX_PaletteFreeFadeTarget(*actor);
    SELF(PartyMember)->param.unk_0B = GFX_PaletteAllocFade(*actor, 0, 0, 0, 1);
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801F08B8(void) {
    if (g_FrameCount & 1) {
        g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r += 1;
        g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.g += 1;
        g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.b += 1;
    }
    if (g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r == 8) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F09E0(void) {
    if (g_FrameCount & 1) {
        g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r -= 1;
        g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.g -= 1;
        g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.b -= 1;
    }
    if (g_PaletteFades[SELF(PartyMember)->param.unk_0B].offset.r == 0) {
        SELF(PartyMember)->header.step = 1;
    }
    if (g_BattleEffectBattler->param.unk_0B & 0x80) {
        func_80196718(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}
