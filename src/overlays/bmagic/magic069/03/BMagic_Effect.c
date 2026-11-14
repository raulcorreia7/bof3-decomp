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

    actor                = g_Battle.selected_actor;
    g_Task->unk_2E.half  = actor->unk_2E.half;
    g_Task->unk_30.half  = actor->unk_30.half;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 3; i++) {
        PartyMember* work;

        slot                               = Battle_AllocEffect(1, 57);
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    for (i = 0; i < 3; i++) {
        PartyMember* work;

        slot                               = Battle_AllocEffect(1, 57);
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    /* Copies the first three CLUTs of arena palette row 26 into the work copy. */
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
        dst[i + 32] = src[i + 32];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE90 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEED4(void) {
    s32 tpage;

    SYS_DISPATCH_BYTE(D_801F0504, g_Task->header.step);
    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, 0xC);
    if (g_Task->header.flags & 0x1) {
        if (g_Task->header.step != 0) {
            func_801EFF14();
            func_801EFC00();
        }
    }
    if (g_Task->header.flags & 0x1) {
        if (g_Task->header.step >= 3) {
            func_801F0104();
        }
    }
    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, 0xC);
}

MATCH void func_801EF034(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--g_Task->unk_09 == 0) {
        dst              = g_Task;
        src              = g_BattleEffectBattler;
        dst->unk_0C      = 0xB;
        dst->unk_2E.half = src->unk_2E.half + 0x37;
        dst->unk_30.half = src->unk_30.half - 0x10;
        dst->unk_09      = 0;
        g_Task->timer    = 32;
        g_Task->header.step++;
    }
}

MATCH void func_801EF0C4(void) {
    s32 step_next;

    step_next      = g_Task->unk_0C - 1;
    g_Task->unk_0C = step_next;
    g_Task->unk_2E.half -= step_next;
    if (g_Task->unk_0C == 0) {
        if (g_Task->param.unk_0B == 0) {
            SND_QueueSelectionEffect(0x103);
            g_Task->header.step += 1;
            return;
        }
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF15C(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        func_801F0274();
        g_Task->param.unk_0B = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF1D0(void) {
    u8 value;
    u8 value2;

    if (g_Task->param.unk_0B != 0) {
        value          = g_Task->unk_09 + 4;
        g_Task->unk_09 = value;
        if ((value & BYTE_MASK) == 0x10) {
            g_Task->param.unk_0B = 0;
        }
    } else {
        value2         = g_Task->unk_09 - 2;
        g_Task->unk_09 = value2;
        if (!(value2 & BYTE_MASK)) {
            g_Task->param.unk_0B = 1;
        }
    }
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        SND_QueueSelectionEffect(0x101);
        g_Task->unk_09 = 0x10;
        g_Task->header.step += 1;
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
        func_801E5988();
    }
}

MATCH void func_801EF30C(void) {
    SYS_DISPATCH_BYTE(D_801F0518, g_Task->header.step);
    GFX_AddDitheredDrawMode(3, getTPage(0, 1, 320, 256));
    if (g_Task->header.flags & 0x1 && g_Task->header.step != 0) {
        func_801EFF14();
        func_801EFC00();
    }
    GFX_AddDitheredDrawMode(3, GetGraphType() != 1 ? (GetGraphType() == 2 ? 0x25 : 0x15) : 0x25);
}

MATCH void func_801EF430(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--g_Task->unk_09 == 0) {
        dst              = g_Task;
        src              = g_BattleEffectBattler;
        dst->unk_0C      = 0xB;
        dst->unk_2E.half = src->unk_2E.half - 0x37;
        dst->unk_30.half = src->unk_30.half - 0x10;
        dst->unk_09      = 0;
        g_Task->timer    = 32;
        g_Task->header.step++;
    }
}

MATCH void func_801EF4C0(void) {
    s32 count;

    count          = g_Task->unk_0C - 1;
    g_Task->unk_0C = count;
    g_Task->unk_2E.half += count;
    if (g_Task->unk_0C == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF520(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 10, 2, g_Task);
}

MATCH void func_801EF564(void) {
    PartyMember* battler;
    u8           slot;
    u16          y;

    if (g_Task->param.unk_0B < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[g_Task->param.unk_0B];
    } else {
        battler = (PartyMember*)(g_BattleEnemies + g_Task->param.unk_0B * BATTLE_ENEMY_STRIDE);
    }
    GFX_FreePaletteFadeTarget(battler);
    g_Task->timer       = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
    g_Task->unk_2E.half = battler->unk_2E.half - 32;
    y                   = battler->unk_30.half - 12;
    g_Task->unk_30.half = y;
    slot                = g_Task->param.unk_0B;
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        if (g_Game.members[slot].facing < 2) {
            g_Task->unk_30.half = y - s_BattlePanelYOffsets[g_Game.members[slot].chr.character_id * 2];
        } else {
            g_Task->unk_30.half = y - D_801EB109[g_Game.members[slot].chr.character_id * 2];
        }
    } else {
        g_Task->unk_30.half = y - ENCOUNTER_ENEMIES[g_BattleEnemyBattlers[slot - BATTLE_PARTY_CHARACTERS_COUNT].kind].height;
    }
    g_Task->unk_09 = 0;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801EF724);

MATCH void func_801EF834(void) {
    g_PaletteFades[g_Task->timer].offset.red -= 1;
    g_PaletteFades[g_Task->timer].offset.green -= 1;
    g_PaletteFades[g_Task->timer].offset.blue -= 1;
    if (g_PaletteFades[g_Task->timer].offset.red == 0) {
        if (g_Task->unk_04 == 0) {
            SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 2));
        }
        GFX_FreePaletteFade(g_Task->timer);
        func_800AF814(g_Task->param.unk_0B);
        g_Task->unk_09 = 0;
        g_Task->timer  = 4;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF9C4(void) {
    u8 timer;
    u8 counter;

    func_801EFA84();
    timer = g_Task->timer;
    if ((timer & BYTE_MASK) != 24) {
        g_Task->timer = timer + 4;
    }
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x14) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"

/* The effect's screen-cell quad: 48 wide, the timer tall, its texture page chosen by graph type. */
MATCH void func_801EFA84(void) {
    POLY_FT4* prim;
    s32       tpage;

    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    setXY4(prim, g_Task->unk_2E.half, g_Task->unk_30.half, g_Task->unk_2E.half + 48, g_Task->unk_30.half, g_Task->unk_2E.half, g_Task->unk_30.half + g_Task->timer, g_Task->unk_2E.half + 48,
           g_Task->unk_30.half + g_Task->timer);
    setTPage(prim, 0, 0, 896, 256);
    setClut(prim, 32, 506);
    prim->u0 = 0;
    prim->v0 = 32;
    prim->u1 = 64;
    prim->v1 = 32;
    prim->u2 = 0;
    prim->v2 = g_Task->timer + 32;
    prim->u3 = 64;
    prim->v3 = g_Task->timer + 32;
    setRGB0(prim, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(2, sizeof(POLY_FT4));
}

/* Draw four fans of three shaded triangles round the effect screen point, one per quarter turn
 * at the timer radius; their red and green shades fade in by step. */
MATCH void func_801EFC00(void) {
    POLY_G3* prim;
    s32      i;
    s32      j;

    D_1F800000.view.effect.params[0] = g_Task->timer;
    D_1F800000.view.effect.params[1] = (g_Task->timer >> 2) + 1;
    if (g_Task->header.step < 2) {
        D_1F800000.view.effect.params[3] = 0x80 - g_Task->param.unk_0B * 48;
        D_1F800000.view.effect.params[4] = 0x80 - g_Task->param.unk_0B * 48;
    } else {
        D_1F800000.view.effect.params[3] = g_Task->unk_09 * 6 + 0x80;
        D_1F800000.view.effect.params[4] = 0x80 - g_Task->unk_09 * 6;
    }
    for (i = 0; i < 4; i++) {
        D_1F800000.view.effect.params[6] = g_Task->unk_2E.half + FIXED_MUL(rsin(i << 10), D_1F800000.view.effect.params[0]);
        D_1F800000.view.effect.params[7] = g_Task->unk_30.half + FIXED_MUL(rcos(i << 10), D_1F800000.view.effect.params[0]);
        for (j = 0; j < 3; j++) {
            prim = (POLY_G3*)g_GfxPrimCursor;
            SetPolyG3(prim);
            SetSemiTrans(prim, 1);
            setXY0(prim, D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[7]);
            D_1F800000.view.effect.params[2] = ((D_801F0534[j] + i * 16) & 0x3F) << 6;
            prim->x1                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[1]);
            prim->y1                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[1]);
            D_1F800000.view.effect.params[2] = ((D_801F0534[j + 1] + i * 16) & 0x3F) << 6;
            prim->x2                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[1]);
            prim->y2                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[1]);
            setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], 1);
            setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], 1);
            setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], 1);
            GFX_AddPrim(3, sizeof(POLY_G3));
        }
    }
}

/* Draws a ring of the timer radius round the effect's screen point as 64 line segments, keeping
 * the middle half of every sixteen; the scratchpad holds the radius, angle, shade and centre. */
MATCH void func_801EFF14(void) {
    LINE_F2* prim;
    s32      i;
    s32      segment;

    D_1F800000.view.effect.params[0] = g_Task->timer;
    D_1F800000.view.effect.params[6] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[7] = g_Task->unk_30.half;
    if (g_Task->header.step < 2) {
        D_1F800000.view.effect.params[3] = 0x80 - g_Task->param.unk_0B * 48;
    } else {
        D_1F800000.view.effect.params[3] = 0x80;
    }
    for (segment = 0, i = 0; i < 64; i++, segment++) {
        if ((segment & 0xC) == 4 || (segment & 0xC) == 8) {
            prim = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(prim);
            SetSemiTrans(prim, 1);
            D_1F800000.view.effect.params[2] = i << 6;
            setXY0(prim, D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]),
                   D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]));
            D_1F800000.view.effect.params[2] = (i + 1) << 6;
            prim->x1                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
            prim->y1                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
            setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
            GFX_AddPrim(3, sizeof(LINE_F2));
        }
    }
}

MATCH void func_801F0104(void) {
    LINE_F2*      line;
    volatile u16* shade;

    shade      = (volatile u16*)&D_1F800006;
    line       = (LINE_F2*)g_GfxPrimCursor;
    *shade     = 0x80;
    D_1F80000C = g_Task->unk_2E.half;
    /* FAKE: retail stores each staged coordinate before loading the next. */
    FAKE_ORDER_FENCE();
    D_1F80000E = g_Task->unk_30.half;
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
    GFX_AddPrim(3, sizeof(LINE_F2));
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
    GFX_AddPrim(3, sizeof(LINE_F2));
}

/* Spawn a piece on every selectable battler other than the actor and the target that is
 * confused, charging or under 2 intellect, counting the pieces in the effect battler ticker. */
MATCH void func_801F0274(void) {
    s32          i;
    s32          count;
    s32          slot;
    PartyMember* work;

    count = 0;
    for (i = 0; i < 8; i++) {
        if (Battle_SlotIsBlocked((u8)(i + BATTLE_PARTY_CHARACTERS_COUNT)) == 0 && g_Battle.active_battler != i + BATTLE_PARTY_CHARACTERS_COUNT &&
            g_Battle.target_selector != i + BATTLE_PARTY_CHARACTERS_COUNT) {
            if (g_BattleEnemyBattlers[i].stats.intellect < 2 || (g_BattleEnemyBattlers[i].status & STATUS_CONFUSED) || (g_BattleEnemyBattlers[i].turn.action_flags.value & COMBATANT_FLAG_CHARGING)) {
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
            if (g_Game.members[i].chr.stats.intellect < 2 || (g_Game.members[i].chr.status & STATUS_CONFUSED) || (g_Game.members[i].u.turn.action_flags.value & COMBATANT_FLAG_CHARGING) ||
                (g_Game.members[i].u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM_QUEUED)) {
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
