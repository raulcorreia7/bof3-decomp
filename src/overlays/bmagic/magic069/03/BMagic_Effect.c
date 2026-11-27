#include "magic069_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The module entry: runs the init, then Effect_MarkDamagedOnZeroTick. */
/* func_801EEC04 */
MATCH void BMagic_InfluenceUpdate(void) {
    ACTOR_RUN_MODE_HANDLER(BMagic_InfluenceInit, Effect_MarkDamagedOnZeroTick);
}

/* Takes the selected actor's screen point, spawns 3 right rings and 3 left rings with delays of 1 to 3 frames, copies the palette and plays the sound. */
/* func_801EEC5C */
MATCH void BMagic_InfluenceInit(void) {
    u8           i;
    u8           slot;
    PartyMember* actor;
    u16*         dst;
    u16*         src;

    actor                             = g_Battle.selected_actor;
    SELF(PartyMember)->screen_x.value = actor->screen_x.value;
    SELF(PartyMember)->screen_y.value = actor->screen_y.value;
    SELF(PartyMember)->param.unk_0B   = 0;
    SELF(PartyMember)->header.mode += 1;
    for (i = 0; i < BMAGIC_INFLUENCE_RING_COUNT; i++) {
        PartyMember* work;

        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_INFLUENCE);
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = BMAGIC_INFLUENCE_EFFECT_RIGHT_RING;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        g_BattleEffects[slot].target.party = work;
        SELF(PartyMember)->param.unk_0B += 1;
    }
    for (i = 0; i < BMAGIC_INFLUENCE_RING_COUNT; i++) {
        PartyMember* work;

        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_INFLUENCE);
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = BMAGIC_INFLUENCE_EFFECT_LEFT_RING;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        g_BattleEffects[slot].target.party = work;
        SELF(PartyMember)->param.unk_0B += 1;
    }
    /* Copies the first three CLUTs of arena palette row 26 into the work copy. */
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
        dst[i + 32] = src[i + 32];
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEE90 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* Runs the right ring step that header.step selects and draws its ring and fans, and from step 3 a cross. */
/* func_801EEED4 */
MATCH void BMagic_InfluenceRightRingUpdate(void) {
    s32 tpage;

    SYS_DISPATCH_BYTE(g_BMagicInfluenceRightRingSteps, SELF(PartyMember)->header.step);
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    if (SELF(PartyMember)->header.flags & 0x1) {
        if (SELF(PartyMember)->header.step != 0) {
            BMagic_InfluenceDrawRing();
            BMagic_InfluenceDrawFans();
        }
    }
    if (SELF(PartyMember)->header.flags & 0x1) {
        if (SELF(PartyMember)->header.step >= 3) {
            BMagic_InfluenceDrawCross();
        }
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

/* Right ring step 0: after its delay places the ring 0x37 right of the effect battler's screen point and sets its radius to 32. */
/* func_801EF034 */
MATCH void BMagic_InfluenceRightRingStart(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--SELF(PartyMember)->unk_09 == 0) {
        dst                      = SELF(PartyMember);
        src                      = g_BattleEffectBattler;
        dst->unk_0C              = 0xB;
        dst->screen_x.value      = src->screen_x.value + 0x37;
        dst->screen_y.value      = src->screen_y.value - 0x10;
        dst->unk_09              = 0;
        SELF(PartyMember)->timer = 32;
        SELF(PartyMember)->header.step++;
    }
}

/* Right ring step 1: moves the ring left over 11 frames; the first ring plays the sound and advances, the others end. */
/* func_801EF0C4 */
MATCH void BMagic_InfluenceRightRingApproach(void) {
    s32 step_next;

    step_next                 = SELF(PartyMember)->unk_0C - 1;
    SELF(PartyMember)->unk_0C = step_next;
    SELF(PartyMember)->screen_x.value -= step_next;
    if (SELF(PartyMember)->unk_0C == 0) {
        if (SELF(PartyMember)->param.unk_0B == 0) {
            SND_SEQueueSelection(0x103);
            SELF(PartyMember)->header.step += 1;
            return;
        }
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

/* Right ring step 2: after 16 frames spawns the marks and advances. */
/* func_801EF15C */
MATCH void BMagic_InfluenceRightRingSpawnMarks(void) {
    u8 count;

    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        BMagic_InfluenceSpawnMarks();
        SELF(PartyMember)->param.unk_0B = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

/* Right ring step 3: pulses its shade until the effect battler's count of live pieces is 1, then plays the sound and advances. */
/* func_801EF1D0 */
MATCH void BMagic_InfluenceRightRingPulse(void) {
    u8 value;
    u8 value2;

    if (SELF(PartyMember)->param.unk_0B != 0) {
        value                     = SELF(PartyMember)->unk_09 + 4;
        SELF(PartyMember)->unk_09 = value;
        if ((value & BYTE_MASK) == 0x10) {
            SELF(PartyMember)->param.unk_0B = 0;
        }
    } else {
        value2                    = SELF(PartyMember)->unk_09 - 2;
        SELF(PartyMember)->unk_09 = value2;
        if (!(value2 & BYTE_MASK)) {
            SELF(PartyMember)->param.unk_0B = 1;
        }
    }
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        SND_SEQueueSelection(0x101);
        SELF(PartyMember)->unk_09 = 0x10;
        SELF(PartyMember)->header.step += 1;
    }
}

/* Right ring step 4: shrinks the radius by 2 per frame to 8, then lowers the count of live pieces and clears the effect. */
/* func_801EF2AC */
MATCH void BMagic_InfluenceRightRingEnd(void) {
    PartyMember* work;
    u8           next;

    work        = SELF(PartyMember);
    next        = work->timer - 2;
    work->timer = next;
    if (next == 8) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        Effect_Reset();
    }
}

/* Runs the left ring step that header.step selects and draws its ring and fans. */
/* func_801EF30C */
MATCH void BMagic_InfluenceLeftRingUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicInfluenceLeftRingSteps, SELF(PartyMember)->header.step);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    if (SELF(PartyMember)->header.flags & 0x1 && SELF(PartyMember)->header.step != 0) {
        BMagic_InfluenceDrawRing();
        BMagic_InfluenceDrawFans();
    }
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
}

/* Left ring step 0: after its delay places the ring 0x37 left of the effect battler's screen point and sets its radius to 32. */
/* func_801EF430 */
MATCH void BMagic_InfluenceLeftRingStart(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--SELF(PartyMember)->unk_09 == 0) {
        dst                      = SELF(PartyMember);
        src                      = g_BattleEffectBattler;
        dst->unk_0C              = 0xB;
        dst->screen_x.value      = src->screen_x.value - 0x37;
        dst->screen_y.value      = src->screen_y.value - 0x10;
        dst->unk_09              = 0;
        SELF(PartyMember)->timer = 32;
        SELF(PartyMember)->header.step++;
    }
}

/* Left ring step 1: moves the ring right over 11 frames, then lowers the count of live pieces and clears the effect. */
/* func_801EF4C0 */
MATCH void BMagic_InfluenceLeftRingApproach(void) {
    s32 count;

    count                     = SELF(PartyMember)->unk_0C - 1;
    SELF(PartyMember)->unk_0C = count;
    SELF(PartyMember)->screen_x.value += count;
    if (SELF(PartyMember)->unk_0C == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Effect_Reset();
    }
}

/* Runs the mark step that header.step selects from g_BMagicInfluenceMarkSteps. */
/* func_801EF520 */
MATCH void BMagic_InfluenceMarkUpdate(void) {
    SYS_DISPATCH_TASK(g_BMagicInfluenceMarkSteps, 2, g_Self);
}

/* Mark step 0: starts a palette fade on the mark's battler and places the mark's quad at its upper left. */
/* func_801EF564 */
MATCH void BMagic_InfluenceMarkStart(void) {
    PartyMember* battler;
    u8           slot;
    u16          y;

    if (SELF(PartyMember)->param.unk_0B < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[SELF(PartyMember)->param.unk_0B];
    } else {
        battler = (PartyMember*)(g_BattleEnemies + SELF(PartyMember)->param.unk_0B * BATTLE_ENEMY_STRIDE);
    }
    GFX_PaletteFreeFadeTarget(battler);
    SELF(PartyMember)->timer          = GFX_PaletteAllocFade(battler, 0, 0, 0, 1);
    SELF(PartyMember)->screen_x.value = battler->screen_x.value - 32;
    y                                 = battler->screen_y.value - 12;
    SELF(PartyMember)->screen_y.value = y;
    slot                              = SELF(PartyMember)->param.unk_0B;
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        if (g_Game.members[slot].facing < 2) {
            SELF(PartyMember)->screen_y.value = y - s_BattlePanelYOffsets[g_Game.members[slot].chr.character_id * 2];
        } else {
            SELF(PartyMember)->screen_y.value = y - D_801EB109[g_Game.members[slot].chr.character_id * 2];
        }
    } else {
        SELF(PartyMember)->screen_y.value = y - ENCOUNTER_ENEMIES[g_BattleEnemyBattlers[slot - BATTLE_PARTY_CHARACTERS_COUNT].type].height;
    }
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->header.step += 1;
}

/* Mark step 1: raises the battler's palette fade by 1 per frame to 16. */
/* func_801EF724 */
MATCH void BMagic_InfluenceMarkFadeIn(void) {
    g_PaletteFades[SELF(PartyMember)->timer].offset.r += 1;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g += 1;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b += 1;
    if (g_PaletteFades[SELF(PartyMember)->timer].offset.r == 16) {
        SELF(PartyMember)->header.step += 1;
    }
}

/* Mark step 2: lowers the battler's palette fade to 0, plays the sound for the first mark, frees the fade and restores the battler's poison fade. */
/* func_801EF834 */
MATCH void BMagic_InfluenceMarkFadeOut(void) {
    g_PaletteFades[SELF(PartyMember)->timer].offset.r -= 1;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g -= 1;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b -= 1;
    if (g_PaletteFades[SELF(PartyMember)->timer].offset.r == 0) {
        if (SELF(PartyMember)->unk_04 == 0) {
            SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 2));
        }
        GFX_PaletteFreeFade(SELF(PartyMember)->timer);
        Battle_FadePoisonedBattler(SELF(PartyMember)->param.unk_0B);
        SELF(PartyMember)->unk_09 = 0;
        SELF(PartyMember)->timer  = 4;
        SELF(PartyMember)->header.step += 1;
    }
}

/* Mark step 3: draws the mark's quad, which grows 4 per frame to 24 tall, for 20 frames. */
/* func_801EF9C4 */
MATCH void BMagic_InfluenceMarkGrow(void) {
    u8 timer;
    u8 counter;

    BMagic_InfluenceDrawMark();
    timer = SELF(PartyMember)->timer;
    if ((timer & BYTE_MASK) != 24) {
        SELF(PartyMember)->timer = timer + 4;
    }
    counter                   = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x14) {
        SELF(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"

/* Draws the mark: a 48 wide textured quad as tall as the effect's timer. */
/* func_801EFA84 */
MATCH void BMagic_InfluenceDrawMark(void) {
    POLY_FT4* prim;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    setXY4(prim, SELF(PartyMember)->screen_x.value, SELF(PartyMember)->screen_y.value, SELF(PartyMember)->screen_x.value + 48, SELF(PartyMember)->screen_y.value, SELF(PartyMember)->screen_x.value,
           SELF(PartyMember)->screen_y.value + SELF(PartyMember)->timer, SELF(PartyMember)->screen_x.value + 48, SELF(PartyMember)->screen_y.value + SELF(PartyMember)->timer);
    setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 896, 256);
    setClut(prim, 32, 506);
    setUV4(prim, 0, 32, 64, 32, 0, SELF(PartyMember)->timer + 32, 64, SELF(PartyMember)->timer + 32);
    setRGB0(prim, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
}

/* Draws four fans of three shaded triangles round the effect's screen point, one per quarter turn at the timer radius; their red and green shades change with the step. */
/* func_801EFC00 */
MATCH void BMagic_InfluenceDrawFans(void) {
    POLY_G3* prim;
    s32      i;
    s32      j;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[1] = (SELF(PartyMember)->timer >> 2) + 1;
    if (SELF(PartyMember)->header.step < 2) {
        g_ScratchPad.cells.halves[3] = 0x80 - SELF(PartyMember)->param.unk_0B * 48;
        g_ScratchPad.cells.halves[4] = 0x80 - SELF(PartyMember)->param.unk_0B * 48;
    } else {
        g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_09 * 6 + 0x80;
        g_ScratchPad.cells.halves[4] = 0x80 - SELF(PartyMember)->unk_09 * 6;
    }
    for (i = 0; i < 4; i++) {
        g_ScratchPad.cells.halves[6] = SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 10), g_ScratchPad.cells.halves[0]);
        g_ScratchPad.cells.halves[7] = SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 10), g_ScratchPad.cells.halves[0]);
        for (j = 0; j < 3; j++) {
            prim = (POLY_G3*)g_GfxPrimCursor;
            SetPolyG3(prim);
            SetSemiTrans(prim, 1);
            setXY0(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
            g_ScratchPad.cells.halves[2] = ((g_BMagicInfluenceFanPhases[j] + i * 16) & 0x3F) << 6;
            prim->x1                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
            prim->y1                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
            g_ScratchPad.cells.halves[2] = ((g_BMagicInfluenceFanPhases[j + 1] + i * 16) & 0x3F) << 6;
            prim->x2                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
            prim->y2                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
            setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], 1);
            setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], 1);
            setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], 1);
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));
        }
    }
}

/* Draws a ring of 64 line segments round the effect's screen point, keeping the middle half of every sixteen, at the timer radius. */
/* func_801EFF14 */
MATCH void BMagic_InfluenceDrawRing(void) {
    LINE_F2* prim;
    s32      i;
    s32      segment;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[6] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[7] = SELF(PartyMember)->screen_y.value;
    if (SELF(PartyMember)->header.step < 2) {
        g_ScratchPad.cells.halves[3] = 0x80 - SELF(PartyMember)->param.unk_0B * 48;
    } else {
        g_ScratchPad.cells.halves[3] = 0x80;
    }
    for (segment = 0, i = 0; i < 64; i++, segment++) {
        if ((segment & 0xC) == 4 || (segment & 0xC) == 8) {
            prim = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(prim);
            SetSemiTrans(prim, 1);
            g_ScratchPad.cells.halves[2] = i << 6;
            setXY0(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
                   g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
            g_ScratchPad.cells.halves[2] = (i + 1) << 6;
            prim->x1                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
            prim->y1                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
            setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_F2));
        }
    }
}

/* Draws a cross of two 8 long lines at the effect's screen point. */
/* func_801F0104 */
MATCH void BMagic_InfluenceDrawCross(void) {
    LINE_F2*      line;
    volatile u16* shade;

    shade      = (volatile u16*)&D_1F800006;
    line       = (LINE_F2*)g_GfxPrimCursor;
    *shade     = 0x80;
    D_1F80000C = SELF(PartyMember)->screen_x.value;
    /* FAKE: retail stores each staged coordinate before loading the next. */
    FAKE_ORDER_FENCE();
    D_1F80000E = SELF(PartyMember)->screen_y.value;
    /* FAKE: retail keeps the argument move in the call's delay slot. */
    FAKE_ORDER_FENCE();
    SetLineF2(line);
    SetSemiTrans(line, 1);
    line->x0 = D_1F80000C - 4;
    /* FAKE: retail keeps each staged coordinate access in order. */
    FAKE_ORDER_FENCE();
    line->y0 = D_1F80000E;
    FAKE_ORDER_FENCE();
    line->x1 = D_1F80000C + 4;
    FAKE_ORDER_FENCE();
    line->y1 = D_1F80000E;
    setRGB0(line, *shade, *shade, *shade);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_F2));
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 1);
    line->x0 = D_1F80000C;
    FAKE_ORDER_FENCE();
    line->y0 = D_1F80000E + 4;
    FAKE_ORDER_FENCE();
    line->x1 = D_1F80000C;
    FAKE_ORDER_FENCE();
    line->y1 = D_1F80000E - 4;
    setRGB0(line, *shade, *shade, *shade);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_F2));
}

/* Spawns a mark on every selectable battler other than the actor and the target that is confused, charging or has under 2 intelligence, and counts them in the effect battler's byte 0x0B. */
/* func_801F0274 */
MATCH void BMagic_InfluenceSpawnMarks(void) {
    s32          i;
    s32          count;
    s32          slot;
    PartyMember* work;

    count = 0;
    for (i = 0; i < 8; i++) {
        if (Battle_SlotIsBlocked((u8)(i + BATTLE_PARTY_CHARACTERS_COUNT)) == 0 && g_Battle.active_battler != i + BATTLE_PARTY_CHARACTERS_COUNT &&
            g_Battle.target_selector != i + BATTLE_PARTY_CHARACTERS_COUNT) {
            if (g_BattleEnemyBattlers[i].stats.intelligence < 2 || (g_BattleEnemyBattlers[i].status & STATUS_CONFUSED) ||
                (g_BattleEnemyBattlers[i].turn.action_flags.value & BATTLER_ACTION_CHARGING)) {
                slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_INFLUENCE) & BYTE_MASK;
                work                               = g_BattleEffectBattler;
                g_BattleEffects[slot].header.mode  = BMAGIC_INFLUENCE_EFFECT_MARK;
                g_BattleEffects[slot].unk_04       = count;
                g_BattleEffects[slot].unk_0B       = i + BATTLE_PARTY_CHARACTERS_COUNT;
                g_BattleEffects[slot].target.party = work;
                g_BattleEffectBattler->param.unk_0B += 1;
                count++;
            }
        }
    }
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        if (Battle_SlotIsBlocked((u8)i) == 0 && g_Battle.active_battler != i && g_Battle.target_selector != i) {
            if (g_Game.members[i].chr.stats.intelligence < 2 || (g_Game.members[i].chr.status & STATUS_CONFUSED) || (g_Game.members[i].u.turn.action_flags.value & BATTLER_ACTION_CHARGING) ||
                (g_Game.members[i].u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED)) {
                slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_INFLUENCE) & BYTE_MASK;
                work                               = g_BattleEffectBattler;
                g_BattleEffects[slot].header.mode  = BMAGIC_INFLUENCE_EFFECT_MARK;
                g_BattleEffects[slot].unk_04       = count;
                g_BattleEffects[slot].unk_0B       = i;
                g_BattleEffects[slot].target.party = work;
                g_BattleEffectBattler->param.unk_0B += 1;
                count++;
            }
        }
    }
}
