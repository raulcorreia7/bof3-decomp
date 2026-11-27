#include "magic099_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC18.h"

MATCH void func_801EEC88(void) {
    PartyMember* actor;
    PartyMember* work;
    u32          slot;
    u32          i;

    actor                          = g_Battle.selected_actor;
    SELF(PartyMember)->facing      = actor->facing;
    SELF(PartyMember)->pos.x.fixed = actor->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = actor->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed = actor->pos.z.fixed;
    GFX_PaletteFreeFadeTarget(actor);
    SELF(PartyMember)->timer           = GFX_PaletteAllocFade(actor, 0, 0, 0, 1);
    slot                               = Battle_AllocEffect(1, 12) & BYTE_MASK;
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 12) & BYTE_MASK;
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].unk_03       = i;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i * 4;
        g_BattleEffects[slot].target.party = work;
    }
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 12) & BYTE_MASK;
        g_BattleEffects[slot].target.party = SELF(PartyMember);
        g_BattleEffects[slot].unk_03       = i;
        g_BattleEffects[slot].header.mode  = 2;
    }
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    SELF(PartyMember)->unk_09       = 8;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
}

MATCH void func_801EEE70(void) {
    g_PaletteFades[SELF(PartyMember)->timer].offset.r--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b--;
    if (--SELF(PartyMember)->unk_09 == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 16);
        SELF(PartyMember)->header.mode++;
    }
}

MATCH void func_801EEF98(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    if (work->param.unk_0B != 0) {
        work->unk_09      = 8;
        work              = SELF(PartyMember);
        work->header.mode = work->header.mode + 1;
    }
}

#include "overlays/bmagic/shared/Effect_BrightenPalette.h"

MATCH void func_801EF0EC(void) {
    if (SELF(PartyMember)->param.unk_0B == 9) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EF16C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrixRolled.h"

MATCH void func_801EF264(void) {
    D_801F09A0[SELF(PartyMember)->header.step]();
    Battle_ProjectRange();
    if (SELF(PartyMember)->header.step != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF8F0(0x60, 0x20, 7);
        PopMatrix();
    }
}

MATCH void func_801EF2EC(void) {
    SELF(PartyMember)->param.unk_0B = RANDOM_MASK(0xF);
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->timer        = 0;
    SELF(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF374(void) {
    BattleEffectTimerStep();
}

#include "overlays/bmagic/shared/Effect_Wait.h"

MATCH void func_801EF44C(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = SELF(PartyMember);
    work->param.unk_0B++;
    work        = SELF(PartyMember);
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B++;
        Effect_Reset();
    }
}

MATCH void func_801EF4C4(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    D_801F09B0[work->header.step]();
    Battle_ProjectRange();
    if (SELF(PartyMember)->header.flags != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF8F0(0x20, 0x50, 0xF);
        func_801F070C();
        PopMatrix();
    }
}

MATCH void func_801EF554(void) {
    PartyMember* work;
    s32          temp;
    s32          angle;
    s32*         angle_cell;
    s32          velocity;

    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->timer  = 0;

    work                             = SELF(PartyMember);
    temp                             = work->unk_03 << 5;
    angle_cell                       = &D_1F800004;
    angle                            = (temp & 0x7F) << 5;
    FAKE_VOLATILE(s32, work->unk_0C) = temp;
    *angle_cell                      = angle;
    g_ScratchPad                     = 0x28;

    velocity          = rcos(angle) * g_ScratchPad;
    work              = SELF(PartyMember);
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity                       = rsin(*angle_cell) * g_ScratchPad;
    SELF(PartyMember)->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    SELF(PartyMember)->pos.z.part.integer = BATTLE_ACTIVE_WORK->pos.z.part.integer;
    SELF(PartyMember)->header.step++;
}

MATCH void func_801EF654(void) {
    BattleEffectTimerStep();
}

MATCH void func_801EF6C4(void) {
    MagicOrbitProjectionStep(0x28);
}

MATCH void func_801EF7D8(void) {
    PartyMember* work;
    s32          counter;
    s32          angle;
    s32*         angle_cell;
    s32          velocity;

    SELF(PartyMember)->param.unk_0B++;

    work                             = SELF(PartyMember);
    counter                          = work->unk_0C + 1;
    FAKE_VOLATILE(s32, work->unk_0C) = counter;
    angle                            = (counter & 0x7F) << 5;
    angle_cell                       = &D_1F800004;
    *angle_cell                      = angle;
    g_ScratchPad                     = 0x28;

    velocity          = rcos(angle) * g_ScratchPad;
    work              = SELF(PartyMember);
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity                       = rsin(*angle_cell) * g_ScratchPad;
    SELF(PartyMember)->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    if (--SELF(PartyMember)->timer == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B++;
        Effect_Reset();
    }
}

#ifdef NON_MATCHING
/* Draws seventeen bands of three projected POLY_G4 quads, each band 0x40 deeper than the last: the
 * quads sway with the effect counter, their radius jitters by jitter_mask and their height by
 * band_height; the shades follow the counter and the first band fades to black. */
NON_MATCHING void func_801EF8F0(s16 band_height, s16 radius, s16 jitter_mask) {
    POLY_G4*    prim;
    long        p;
    long        flag;
    s32         tpage;
    s32         shade;
    s32         i;
    ScratchPad* scratch;

    scratch                   = (ScratchPad*)&g_ScratchPad;
    scratch->cells.words[0]   = 16;
    scratch->cells.words[1]   = (SELF(PartyMember)->param.unk_0B & 0xF) * 256;
    scratch->cells.words[2]   = SELF(PartyMember)->timer * 15;
    shade                     = SELF(PartyMember)->timer * 15;
    g_ScratchPadVectors[0].vy = FIXED_MUL(rsin(scratch->cells.words[1]), scratch->cells.words[0]);
    g_ScratchPadVectors[0].vz = 0;
    tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    for (i = 1; i < 18; i++) {
        scratch                 = (ScratchPad*)&g_ScratchPad;
        scratch->cells.words[1] = ((SELF(PartyMember)->param.unk_0B + i) & 0xF) << 8;
        if RANDOM_MASK (1) {
            scratch->cells.words[0] = radius + (rand() & jitter_mask);
        } else {
            scratch->cells.words[0] = radius - (rand() & jitter_mask);
        }
        g_ScratchPadVectors[2].vx = 0;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[0].vz;
        g_ScratchPadVectors[3].vx = 0;
        g_ScratchPadVectors[3].vy = g_ScratchPadVectors[0].vy - band_height;
        g_ScratchPadVectors[3].vz = g_ScratchPadVectors[0].vz;
        setVector(&g_ScratchPadVectors[0], 0, FIXED_MUL(rsin(scratch->cells.words[1]), scratch->cells.words[0]), -(i << 6));
        g_ScratchPadVectors[1].vx = 0;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[0].vy - band_height;
        g_ScratchPadVectors[1].vz = -(i << 6);
        prim                      = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, scratch->cells.words[2], scratch->cells.words[2], scratch->cells.words[2]);
        setRGB1(prim, 1, 1, shade);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        } else {
            setRGB2(prim, scratch->cells.words[2], scratch->cells.words[2], scratch->cells.words[2]);
            setRGB3(prim, 1, 1, shade);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        if (prim->y2 > 0) {
            Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
            prim = (POLY_G4*)g_GfxPrimCursor;
            g_ScratchPadVectors[0].vy -= band_height;
            g_ScratchPadVectors[1].vy -= band_height;
            g_ScratchPadVectors[2].vy -= band_height;
            g_ScratchPadVectors[3].vy -= band_height;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            setRGB0(prim, 1, 1, shade);
            setRGB1(prim, 1, 1, 1);
            if (i == 1) {
                setRGB2(prim, 1, 1, 1);
                setRGB3(prim, 1, 1, 1);
            } else {
                setRGB2(prim, 1, 1, shade);
                setRGB3(prim, 1, 1, 1);
            }
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &p, &flag);
            Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
            prim = (POLY_G4*)g_GfxPrimCursor;
            g_ScratchPadVectors[0].vy += band_height * 2;
            g_ScratchPadVectors[1].vy += band_height * 2;
            g_ScratchPadVectors[2].vy += band_height * 2;
            g_ScratchPadVectors[3].vy += band_height * 2;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            setRGB0(prim, 1, 1, shade);
            setRGB1(prim, scratch->cells.words[2], scratch->cells.words[2], scratch->cells.words[2]);
            if (i == 1) {
                setRGB2(prim, 1, 1, 1);
                setRGB3(prim, 1, 1, 1);
            } else {
                setRGB2(prim, 1, 1, shade);
                setRGB3(prim, scratch->cells.words[2], scratch->cells.words[2], scratch->cells.words[2]);
            }
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &p, &flag);
            Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
            prim = (POLY_G4*)g_GfxPrimCursor;
            g_ScratchPadVectors[0].vy += band_height;
            g_ScratchPadVectors[1].vy += band_height;
            g_ScratchPadVectors[2].vy += band_height;
            g_ScratchPadVectors[3].vy += band_height;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, shade);
            if (i == 1) {
                setRGB2(prim, 1, 1, 1);
                setRGB3(prim, 1, 1, 1);
            } else {
                setRGB2(prim, 1, 1, 1);
                setRGB3(prim, 1, 1, shade);
            }
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &p, &flag);
            Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
            g_ScratchPadVectors[0].vy -= band_height * 2;
        }
    }
}
#else
INCLUDE_ASM(func_801EF8F0);
#endif

MATCH void func_801F0008(void) {
    D_801F09C0[SELF(PartyMember)->header.step]();
    Battle_ProjectRange();
    if (SELF(PartyMember)->header.step != 0) {
        Effect_SetActorMatrixRolled();
        Effect_DrawBolt();
        func_801F070C();
        PopMatrix();
    }
}

MATCH void func_801F0090(void) {
    PartyMember* work;
    s32          counter;
    s32          angle;
    s32*         angle_cell;
    s32          velocity;

    SELF(PartyMember)->param.unk_0B = RANDOM_MASK(0xF);
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->timer        = 0;

    work                             = SELF(PartyMember);
    counter                          = (work->unk_03 << 5) + 0x10;
    angle                            = (counter & 0x7F) << 5;
    FAKE_VOLATILE(s32, work->unk_0C) = counter;
    angle_cell                       = &D_1F800004;
    *angle_cell                      = angle;
    g_ScratchPad                     = 0x18;

    velocity                       = rcos(angle) * g_ScratchPad;
    SELF(PartyMember)->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity                       = rsin(*angle_cell) * g_ScratchPad;
    SELF(PartyMember)->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    COORD_INT(SELF(PartyMember)->pos.z) = COORD_INT(BATTLE_ACTIVE_WORK->pos.z);
    SELF(PartyMember)->header.step++;
}

MATCH void func_801F01AC(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    if (work->timer < 16) {
        work->timer += 2;
    } else {
        work->unk_09 = 60;
        work         = SELF(PartyMember);
        work->header.step++;
    }
}

MATCH void func_801F0200(void) {
    MagicOrbitProjectionStep(0x10);
}

MATCH void func_801F0314(void) {
    PartyMember* work;
    PartyMember* scratch;
    s32          counter;
    s32          angle;
    s32*         angle_cell;
    s32          velocity;

    SELF(PartyMember)->param.unk_0B++;

    work                             = SELF(PartyMember);
    counter                          = work->unk_0C + 1;
    FAKE_VOLATILE(s32, work->unk_0C) = counter;
    angle                            = (counter & 0x7F) << 5;
    angle_cell                       = &D_1F800004;
    *angle_cell                      = angle;
    g_ScratchPad                     = 0x18;

    velocity          = rcos(angle) * g_ScratchPad;
    work              = SELF(PartyMember);
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity             = rsin(*angle_cell) * g_ScratchPad;
    scratch              = SELF(PartyMember);
    scratch->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;
    scratch->timer -= 2;

    if (SELF(PartyMember)->timer == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B++;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_DrawBolt.h"

MATCH void func_801F070C(void) {
    POLY_G3* primitive;
    s32*     radius;
    s32      angle;
    s32      i;

    g_ScratchPad = RANDOM_MASK(7) + SELF(PartyMember)->timer * 3;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    i      = 0;
    radius = &g_ScratchPad;
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));

    do {
        primitive = GFX_BeginPolyG3(1);

        setXY0(primitive, SELF(PartyMember)->screen_x.value, SELF(PartyMember)->screen_y.value);
        angle         = i << 9;
        primitive->x1 = SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(angle), *radius);
        primitive->y1 = SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(angle), *radius);
        i++;
        angle         = i << 9;
        primitive->x2 = SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(angle), *radius);
        primitive->y2 = SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(angle), *radius);
        setRGB0(primitive, SELF(PartyMember)->timer * 14, SELF(PartyMember)->timer * 14, SELF(PartyMember)->timer * 12);
        setRGB1(primitive, 1, 1, 1);
        setRGB2(primitive, 1, 1, 1);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
    } while (i < 8);
}
