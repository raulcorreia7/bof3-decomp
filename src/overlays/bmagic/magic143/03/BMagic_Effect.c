#include "magic143_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED24};

    SYS_DISPATCH_TASK(handlers, 1, g_Self);
}

MATCH void func_801EEC5C(void) {
    PartyMember* src;
    u32          slot;
    PartyMember* task;

    src                                = g_Battle.selected_actor;
    slot                               = Battle_AllocEffect(1, 53) & BYTE_MASK;
    task                               = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = task;
    g_BattleEffects[slot].pos.x.fixed  = src->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = src->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = src->pos.z.fixed;
    SELF(PartyMember)->param.unk_0B    = 1;
    SND_SEQueueSelection(0x100);
    SELF(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EED70 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEDB4(void) {
    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 1), SELF(PartyMember)->header.step);
    func_800AF764();
    if (SELF(PartyMember)->header.step != 0 && SELF(PartyMember)->header.flags != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF23C(48, 16, 0x3);
        SELF(PartyMember)->param.unk_0B += 4;
        func_801EF23C(32, 80, 0xF);
        SELF(PartyMember)->param.unk_0B += 2;
        Effect_DrawBolt();
        SELF(PartyMember)->param.unk_0B += 4;
        func_801EF23C(24, BOLT_RADIUS, BOLT_FLICKER_MASK);
        SELF(PartyMember)->param.unk_0B -= 10;
        SELF(PartyMember)->screen_x.value += 16;
        func_801EFC74();
        SELF(PartyMember)->screen_x.value -= 32;
        func_801EFC74();
        PopMatrix();
    }
}

MATCH void func_801EEF10(void) {
    SELF(PartyMember)->param.unk_0B = RANDOM_MASK(15);
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->timer        = 0;
    SELF(PartyMember)->header.step++;
}

MATCH void func_801EEF78(void) {
    u8 timer;

    SELF(PartyMember)->timer += 4;
    SELF(PartyMember)->param.unk_0B += 1;
    timer = SELF(PartyMember)->timer;
    if (timer == 16) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        GFX_PaletteAllocFade(g_Battle.selected_actor, -8, -8, -8, 1);
        Battle_ApplyDamageFlags(g_Battle.target_selector, 16);
        SELF(PartyMember)->unk_09 = 32;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF054(void) {
    u8  timer;
    u8* selector;

    SELF(PartyMember)->param.unk_0B++;
    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        selector = &g_BattleTargetSelector;
        Battle_MarkDamaged(*selector);
        func_80196718(g_BattleSelectedActor);
        Battle_FadePoisonedBattler(*selector);
        SELF(PartyMember)->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrixRolled.h"

/* Draws twenty-three steps of four quads: the ring sways with the effect counter and its radius jitters by jitter_mask. */
MATCH void func_801EF23C(s16 band_height, s16 radius, s16 jitter_mask) {
    POLY_G4* prim;
    long     p;
    long     flag;
    s32      tpage;
    s32      i;

    g_ScratchPad.cells.words[0] = radius / 2;
    g_ScratchPad.cells.words[1] = (SELF(PartyMember)->param.unk_0B & 0xF) * 256;
    g_ScratchPad.cells.words[2] = SELF(PartyMember)->timer * 8;
    g_ScratchPad.cells.words[3] = SELF(PartyMember)->timer * 13;
    g_ScratchPadVectors[0].vy   = FIXED_MUL(rsin(g_ScratchPad.cells.words[1]), g_ScratchPad.cells.words[0]);
    g_ScratchPadVectors[0].vz   = 0;
    tpage                       = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    for (i = 1; i < 24; i++) {
        g_ScratchPad.cells.words[1] = ((SELF(PartyMember)->param.unk_0B + i) & 0xF) << 8;
        if RANDOM_MASK (1) {
            g_ScratchPad.cells.words[0] = radius + (rand() & jitter_mask);
        } else {
            g_ScratchPad.cells.words[0] = radius - (rand() & jitter_mask);
        }
        g_ScratchPadVectors[2].vx = 0;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[0].vz;
        g_ScratchPadVectors[3].vx = 0;
        g_ScratchPadVectors[3].vy = g_ScratchPadVectors[0].vy - band_height;
        g_ScratchPadVectors[3].vz = g_ScratchPadVectors[0].vz;
        setVector(&g_ScratchPadVectors[0], 0, FIXED_MUL(rsin(g_ScratchPad.cells.words[1]), g_ScratchPad.cells.words[0]), -(i * 48));
        g_ScratchPadVectors[1].vx = 0;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[0].vy - band_height;
        g_ScratchPadVectors[1].vz = -(i * 48);
        prim                      = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2]);
        setRGB1(prim, 1, 1, g_ScratchPad.cells.words[3]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        } else {
            setRGB2(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2]);
            setRGB3(prim, 1, 1, g_ScratchPad.cells.words[3]);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        g_ScratchPadVectors[0].vy -= band_height;
        g_ScratchPadVectors[1].vy -= band_height;
        g_ScratchPadVectors[2].vy -= band_height;
        g_ScratchPadVectors[3].vy -= band_height;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, g_ScratchPad.cells.words[3]);
        setRGB1(prim, 1, 1, 1);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        } else {
            setRGB2(prim, 1, 1, g_ScratchPad.cells.words[3]);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        g_ScratchPadVectors[0].vy += band_height * 2;
        g_ScratchPadVectors[1].vy += band_height * 2;
        g_ScratchPadVectors[2].vy += band_height * 2;
        g_ScratchPadVectors[3].vy += band_height * 2;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, g_ScratchPad.cells.words[3]);
        setRGB1(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        } else {
            setRGB2(prim, 1, 1, g_ScratchPad.cells.words[3]);
            setRGB3(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2]);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        g_ScratchPadVectors[0].vy += band_height;
        g_ScratchPadVectors[1].vy += band_height;
        g_ScratchPadVectors[2].vy += band_height;
        g_ScratchPadVectors[3].vy += band_height;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, g_ScratchPad.cells.words[3]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        } else {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, g_ScratchPad.cells.words[3]);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        g_ScratchPadVectors[0].vy -= band_height * 2;
    }
}

#include "overlays/bmagic/shared/Effect_DrawBolt.h"

MATCH void func_801EFC74(void) {
    POLY_G3* prim;
    s32*     radius;
    s32      i;

    g_ScratchPad.cells.words[0] = (rand() & 7) + SELF(PartyMember)->timer * 4;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    i      = 0;
    radius = &g_ScratchPad.cells.words[0];
    for (; i < 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, SELF(PartyMember)->screen_x.value, SELF(PartyMember)->screen_y.value, SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 9), *radius),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 9), *radius), SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin((i + 1) << 9), *radius),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos((i + 1) << 9), *radius));
        setRGB0(prim, SELF(PartyMember)->timer * 8, SELF(PartyMember)->timer * 8, SELF(PartyMember)->timer * 6);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}
