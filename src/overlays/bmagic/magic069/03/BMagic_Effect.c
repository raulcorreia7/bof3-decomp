#include "magic069_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EEE30);
}

MATCH void func_801EEC5C(void) {
    u8           i;
    u8           slot;
    PartyMember* actor;
    u16*         dst;
    u16*         src;

    actor                             = g_Battle.selected_actor;
    TASK(PartyMember)->screen_x.value = actor->screen_x.value;
    TASK(PartyMember)->screen_y.value = actor->screen_y.value;
    TASK(PartyMember)->param.unk_0B   = 0;
    TASK(PartyMember)->header.mode += 1;
    for (i = 0; i < 3; i++) {
        PartyMember* work;

        slot                               = Battle_AllocEffect(1, 57);
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        g_BattleEffects[slot].target.party = work;
        TASK(PartyMember)->param.unk_0B += 1;
    }
    for (i = 0; i < 3; i++) {
        PartyMember* work;

        slot                               = Battle_AllocEffect(1, 57);
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        g_BattleEffects[slot].target.party = work;
        TASK(PartyMember)->param.unk_0B += 1;
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

MATCH void func_801EEED4(void) {
    s32 tpage;

    SYS_DISPATCH_BYTE(D_801F0504, TASK(PartyMember)->header.step);
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    if (TASK(PartyMember)->header.flags & 0x1) {
        if (TASK(PartyMember)->header.step != 0) {
            func_801EFF14();
            func_801EFC00();
        }
    }
    if (TASK(PartyMember)->header.flags & 0x1) {
        if (TASK(PartyMember)->header.step >= 3) {
            func_801F0104();
        }
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

MATCH void func_801EF034(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--TASK(PartyMember)->unk_09 == 0) {
        dst                      = g_Task;
        src                      = g_BattleEffectBattler;
        dst->unk_0C              = 0xB;
        dst->screen_x.value      = src->screen_x.value + 0x37;
        dst->screen_y.value      = src->screen_y.value - 0x10;
        dst->unk_09              = 0;
        TASK(PartyMember)->timer = 32;
        TASK(PartyMember)->header.step++;
    }
}

MATCH void func_801EF0C4(void) {
    s32 step_next;

    step_next                 = TASK(PartyMember)->unk_0C - 1;
    TASK(PartyMember)->unk_0C = step_next;
    TASK(PartyMember)->screen_x.value -= step_next;
    if (TASK(PartyMember)->unk_0C == 0) {
        if (TASK(PartyMember)->param.unk_0B == 0) {
            SND_SEQueueSelection(0x103);
            TASK(PartyMember)->header.step += 1;
            return;
        }
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void func_801EF15C(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        func_801F0274();
        TASK(PartyMember)->param.unk_0B = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF1D0(void) {
    u8 value;
    u8 value2;

    if (TASK(PartyMember)->param.unk_0B != 0) {
        value                     = TASK(PartyMember)->unk_09 + 4;
        TASK(PartyMember)->unk_09 = value;
        if ((value & BYTE_MASK) == 0x10) {
            TASK(PartyMember)->param.unk_0B = 0;
        }
    } else {
        value2                    = TASK(PartyMember)->unk_09 - 2;
        TASK(PartyMember)->unk_09 = value2;
        if (!(value2 & BYTE_MASK)) {
            TASK(PartyMember)->param.unk_0B = 1;
        }
    }
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        SND_SEQueueSelection(0x101);
        TASK(PartyMember)->unk_09 = 0x10;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF2AC(void) {
    PartyMember* work;
    u8           next;

    work        = g_Task;
    next        = work->timer - 2;
    work->timer = next;
    if (next == 8) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        Effect_Reset();
    }
}

MATCH void func_801EF30C(void) {
    SYS_DISPATCH_BYTE(D_801F0518, TASK(PartyMember)->header.step);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    if (TASK(PartyMember)->header.flags & 0x1 && TASK(PartyMember)->header.step != 0) {
        func_801EFF14();
        func_801EFC00();
    }
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
}

MATCH void func_801EF430(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--TASK(PartyMember)->unk_09 == 0) {
        dst                      = g_Task;
        src                      = g_BattleEffectBattler;
        dst->unk_0C              = 0xB;
        dst->screen_x.value      = src->screen_x.value - 0x37;
        dst->screen_y.value      = src->screen_y.value - 0x10;
        dst->unk_09              = 0;
        TASK(PartyMember)->timer = 32;
        TASK(PartyMember)->header.step++;
    }
}

MATCH void func_801EF4C0(void) {
    s32 count;

    count                     = TASK(PartyMember)->unk_0C - 1;
    TASK(PartyMember)->unk_0C = count;
    TASK(PartyMember)->screen_x.value += count;
    if (TASK(PartyMember)->unk_0C == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void func_801EF520(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 10, 2, g_Task);
}

MATCH void func_801EF564(void) {
    PartyMember* battler;
    u8           slot;
    u16          y;

    if (TASK(PartyMember)->param.unk_0B < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[TASK(PartyMember)->param.unk_0B];
    } else {
        battler = (PartyMember*)(g_BattleEnemies + TASK(PartyMember)->param.unk_0B * BATTLE_ENEMY_STRIDE);
    }
    GFX_PaletteFreeFadeTarget(battler);
    TASK(PartyMember)->timer          = GFX_PaletteAllocFade(battler, 0, 0, 0, 1);
    TASK(PartyMember)->screen_x.value = battler->screen_x.value - 32;
    y                                 = battler->screen_y.value - 12;
    TASK(PartyMember)->screen_y.value = y;
    slot                              = TASK(PartyMember)->param.unk_0B;
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        if (g_Game.members[slot].facing < 2) {
            TASK(PartyMember)->screen_y.value = y - s_BattlePanelYOffsets[g_Game.members[slot].chr.character_id * 2];
        } else {
            TASK(PartyMember)->screen_y.value = y - D_801EB109[g_Game.members[slot].chr.character_id * 2];
        }
    } else {
        TASK(PartyMember)->screen_y.value = y - ENCOUNTER_ENEMIES[g_BattleEnemyBattlers[slot - BATTLE_PARTY_CHARACTERS_COUNT].type].height;
    }
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF724(void) {
    g_PaletteFades[TASK(PartyMember)->timer].offset.r += 1;
    g_PaletteFades[TASK(PartyMember)->timer].offset.g += 1;
    g_PaletteFades[TASK(PartyMember)->timer].offset.b += 1;
    if (g_PaletteFades[TASK(PartyMember)->timer].offset.r == 16) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF834(void) {
    g_PaletteFades[TASK(PartyMember)->timer].offset.r -= 1;
    g_PaletteFades[TASK(PartyMember)->timer].offset.g -= 1;
    g_PaletteFades[TASK(PartyMember)->timer].offset.b -= 1;
    if (g_PaletteFades[TASK(PartyMember)->timer].offset.r == 0) {
        if (TASK(PartyMember)->unk_04 == 0) {
            SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 2));
        }
        GFX_PaletteFreeFade(TASK(PartyMember)->timer);
        Battle_FadePoisonedBattler(TASK(PartyMember)->param.unk_0B);
        TASK(PartyMember)->unk_09 = 0;
        TASK(PartyMember)->timer  = 4;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF9C4(void) {
    u8 timer;
    u8 counter;

    func_801EFA84();
    timer = TASK(PartyMember)->timer;
    if ((timer & BYTE_MASK) != 24) {
        TASK(PartyMember)->timer = timer + 4;
    }
    counter                   = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x14) {
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"

/* The effect's screen-cell quad: 48 wide, the timer tall, its texture page chosen by graph type. */
MATCH void func_801EFA84(void) {
    POLY_FT4* prim;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    setXY4(prim, TASK(PartyMember)->screen_x.value, TASK(PartyMember)->screen_y.value, TASK(PartyMember)->screen_x.value + 48, TASK(PartyMember)->screen_y.value, TASK(PartyMember)->screen_x.value,
           TASK(PartyMember)->screen_y.value + TASK(PartyMember)->timer, TASK(PartyMember)->screen_x.value + 48, TASK(PartyMember)->screen_y.value + TASK(PartyMember)->timer);
    setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 896, 256);
    setClut(prim, 32, 506);
    setUV4(prim, 0, 32, 64, 32, 0, TASK(PartyMember)->timer + 32, 64, TASK(PartyMember)->timer + 32);
    setRGB0(prim, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
}

/* Draw four fans of three shaded triangles round the effect screen point, one per quarter turn
 * at the timer radius; their red and green shades fade in by step. */
MATCH void func_801EFC00(void) {
    POLY_G3* prim;
    s32      i;
    s32      j;

    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->timer;
    g_ScratchPad.cells.halves[1] = (TASK(PartyMember)->timer >> 2) + 1;
    if (TASK(PartyMember)->header.step < 2) {
        g_ScratchPad.cells.halves[3] = 0x80 - TASK(PartyMember)->param.unk_0B * 48;
        g_ScratchPad.cells.halves[4] = 0x80 - TASK(PartyMember)->param.unk_0B * 48;
    } else {
        g_ScratchPad.cells.halves[3] = TASK(PartyMember)->unk_09 * 6 + 0x80;
        g_ScratchPad.cells.halves[4] = 0x80 - TASK(PartyMember)->unk_09 * 6;
    }
    for (i = 0; i < 4; i++) {
        g_ScratchPad.cells.halves[6] = TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 10), g_ScratchPad.cells.halves[0]);
        g_ScratchPad.cells.halves[7] = TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 10), g_ScratchPad.cells.halves[0]);
        for (j = 0; j < 3; j++) {
            prim = (POLY_G3*)g_GfxPrimCursor;
            SetPolyG3(prim);
            SetSemiTrans(prim, 1);
            setXY0(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
            g_ScratchPad.cells.halves[2] = ((D_801F0534[j] + i * 16) & 0x3F) << 6;
            prim->x1                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
            prim->y1                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
            g_ScratchPad.cells.halves[2] = ((D_801F0534[j + 1] + i * 16) & 0x3F) << 6;
            prim->x2                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
            prim->y2                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
            setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], 1);
            setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], 1);
            setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], 1);
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));
        }
    }
}

/* Draws a ring of the timer radius round the effect's screen point as 64 line segments, keeping
 * the middle half of every sixteen; the scratchpad holds the radius, angle, shade and centre. */
MATCH void func_801EFF14(void) {
    LINE_F2* prim;
    s32      i;
    s32      segment;

    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->timer;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[7] = TASK(PartyMember)->screen_y.value;
    if (TASK(PartyMember)->header.step < 2) {
        g_ScratchPad.cells.halves[3] = 0x80 - TASK(PartyMember)->param.unk_0B * 48;
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

MATCH void func_801F0104(void) {
    LINE_F2*      line;
    volatile u16* shade;

    shade      = (volatile u16*)&D_1F800006;
    line       = (LINE_F2*)g_GfxPrimCursor;
    *shade     = 0x80;
    D_1F80000C = TASK(PartyMember)->screen_x.value;
    /* FAKE: retail stores each staged coordinate before loading the next. */
    FAKE_ORDER_FENCE();
    D_1F80000E = TASK(PartyMember)->screen_y.value;
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

/* Spawn a piece on every selectable battler other than the actor and the target that is
 * confused, charging or under 2 intelligence, counting the pieces in the effect battler ticker. */
MATCH void func_801F0274(void) {
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
                slot                               = Battle_AllocEffect(1, 57) & BYTE_MASK;
                work                               = g_BattleEffectBattler;
                g_BattleEffects[slot].header.mode  = 2;
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
                slot                               = Battle_AllocEffect(1, 57) & BYTE_MASK;
                work                               = g_BattleEffectBattler;
                g_BattleEffects[slot].header.mode  = 2;
                g_BattleEffects[slot].unk_04       = count;
                g_BattleEffects[slot].unk_0B       = i;
                g_BattleEffects[slot].target.party = work;
                g_BattleEffectBattler->param.unk_0B += 1;
                count++;
            }
        }
    }
}
