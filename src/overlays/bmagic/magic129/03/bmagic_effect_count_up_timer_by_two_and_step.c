#include "magic129_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEFC4(void) {
    SYS_DISPATCH_BYTE(D_801F05B8, SELF(PartyMember)->header.step);
    SELF(PartyMember)->param.unk_0B += 1;
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        func_801EF54C();
    }
}

/* Aim the holocaust shot: project the target and the casting enemy to the screen and step
 * from the caster towards the target over 16 frames. */
MATCH void func_801EF058(void) {
    u8 count;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            SELF(PartyMember)->pos.x.fixed = g_BattleEnemyBattlers[SELF(PartyMember)->unk_04].pos.x.fixed;
            SELF(PartyMember)->pos.y.fixed = g_BattleEnemyBattlers[SELF(PartyMember)->unk_04].pos.y.fixed;
            SELF(PartyMember)->pos.z.fixed = g_BattleEnemyBattlers[SELF(PartyMember)->unk_04].pos.z.fixed;
        } else {
            SELF(PartyMember)->pos.x.fixed = g_Game.members[SELF(PartyMember)->unk_04].pos.x.fixed;
            SELF(PartyMember)->pos.y.fixed = g_Game.members[SELF(PartyMember)->unk_04].pos.y.fixed;
            SELF(PartyMember)->pos.z.fixed = g_Game.members[SELF(PartyMember)->unk_04].pos.z.fixed;
        }
        SELF(PartyMember)->pos.x.fixed += TO_COORD(1);
        Battle_ProjectRange();
        D_1F800008[2]                  = SELF(PartyMember)->screen_x.value;
        D_1F800008[3]                  = SELF(PartyMember)->screen_y.value;
        SELF(PartyMember)->pos.x.fixed = g_BattleEnemyBattlers[g_Battle.active_battler - BATTLE_PARTY_CHARACTERS_COUNT].pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = g_BattleEnemyBattlers[g_Battle.active_battler - BATTLE_PARTY_CHARACTERS_COUNT].pos.y.fixed;
        SELF(PartyMember)->pos.z.fixed = g_BattleEnemyBattlers[g_Battle.active_battler - BATTLE_PARTY_CHARACTERS_COUNT].pos.z.fixed;
        SELF(PartyMember)->pos.x.fixed -= TO_COORD(1);
        SELF(PartyMember)->pos.z.fixed += TO_COORD(0x360);
        Battle_ProjectRange();
        D_1F800008[0]             = SELF(PartyMember)->screen_x.value;
        D_1F800008[1]             = SELF(PartyMember)->screen_y.value;
        SELF(PartyMember)->unk_0C = (D_1F800008[2] - D_1F800008[0]) / 16;
        SELF(PartyMember)->unk_10 = (D_1F800008[3] - D_1F800008[1]) / 16;
        SELF(PartyMember)->unk_14 = ratan2(D_1F800008[2] - D_1F800008[0], D_1F800008[3] - D_1F800008[1]) & ANGLE_MASK;
        SELF(PartyMember)->unk_5D = 0x10;
        SELF(PartyMember)->unk_09 = 0x96;
        SELF(PartyMember)->timer  = 0;
        SELF(PartyMember)->header.step += 1;
        SND_SEQueueSelection(0x100);
    }
}

#include "overlays/bmagic/shared/Effect_CountUpTimerByTwoAndStep.h"

MATCH void func_801EF3DC(void) {
    PartyMember* battler;
    u8           slot;
    u8           timer;

    if (SELF(PartyMember)->unk_09 >= 17 && (g_FrameCount & 0x3) == 0) {
        slot                                   = BMagic_AllocEffect();
        battler                                = g_BattleEffectBattler;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = RANDOM_MASK(0x1F);
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = 1;
        g_BattleEffectBattler->param.unk_0B += 1;
    }
    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF4F0(void) {
    PartyMember* work;
    s8           timer;

    work         = SELF(PartyMember);
    timer        = work->unk_5D - 1;
    work->unk_5D = timer;
    if (timer == 0) {
        work               = g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Effect_Reset();
    }
}

/* Draws the magic129 whip: timer segments from the effect position along (unk_0C, unk_10), each swung sideways by a
 * sine of the segment and of unk_0B, as four semi-transparent Gouraud quads around the segment line (a core band and
 * a widening edge on each side), tinted by unk_5D; the first and last segments fade out. */
MATCH void func_801EF54C(void) {
    POLY_G4* prim;
    s32      tpage;
    u8       grey;
    u8       red;
    u8       green;
    u8       blue;
    s16      sway; /* the sideways swing, then each edge direction */
    s32      angle;
    s32      power;
    u8       i;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    power                        = (s8)SELF(PartyMember)->unk_5D;
    g_ScratchPad.cells.halves[1] = 8;
    grey                         = power * 15;
    g_ScratchPad.cells.halves[3] = (SELF(PartyMember)->unk_14 + 0x800) & ANGLE_MASK;
    red                          = power * 12;
    green                        = power * 6;
    blue                         = grey;
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->screen_y.value;
    for (i = 1; i < SELF(PartyMember)->timer + 1; i++) {
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[1];
        g_ScratchPad.cells.halves[1] = FIXED_MUL(rsin(i << 7), 32) + 8;
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[4] = SELF(PartyMember)->screen_x.value + SELF(PartyMember)->unk_0C * i;
        g_ScratchPad.cells.halves[5] = SELF(PartyMember)->screen_y.value + SELF(PartyMember)->unk_10 * i;
        angle                        = (SELF(PartyMember)->unk_14 + 0x400) & ANGLE_MASK;
        sway                         = FIXED_MUL(rsin(i << 7), 48);
        sway                         = FIXED_MUL(rsin(((i + SELF(PartyMember)->param.unk_0B) & 0x3F) << 6), sway);
        g_ScratchPad.cells.halves[4] += FIXED_MUL(rsin(angle), sway);
        g_ScratchPad.cells.halves[5] += FIXED_MUL(rcos(angle), sway);
        g_ScratchPad.cells.halves[2] = g_ScratchPad.cells.halves[3];
        g_ScratchPad.cells.halves[3] = ratan2(g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[7] - g_ScratchPad.cells.halves[5]) & ANGLE_MASK;
        prim                         = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        sway     = (LOHU(g_ScratchPad.cells.halves[2]) + 0x400) & ANGLE_MASK;
        prim->x1 = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(sway), 8);
        prim->y1 = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(sway), 8);
        sway     = (LOHU(g_ScratchPad.cells.halves[3]) + 0x400) & ANGLE_MASK;
        prim->x3 = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(sway), 8);
        prim->y3 = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(sway), 8);
        setXY0(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        prim->x2 = g_ScratchPad.cells.halves[4];
        prim->y2 = g_ScratchPad.cells.halves[5];
        setRGB0(prim, grey, grey, grey);
        setRGB2(prim, grey, grey, grey);
        setRGB1(prim, red, green, blue);
        setRGB3(prim, red, green, blue);
        if (i == SELF(PartyMember)->timer) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        if (i == 1) {
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
        }
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        sway     = (LOHU(g_ScratchPad.cells.halves[2]) + 0x400) & ANGLE_MASK;
        prim->x1 = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(sway), g_ScratchPad.cells.halves[0]);
        prim->y1 = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(sway), g_ScratchPad.cells.halves[0]);
        setXY0(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(sway), 8), g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(sway), 8));
        sway     = (LOHU(g_ScratchPad.cells.halves[3]) + 0x400) & ANGLE_MASK;
        prim->x3 = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(sway), g_ScratchPad.cells.halves[1]);
        prim->y3 = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(sway), g_ScratchPad.cells.halves[1]);
        prim->x2 = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(sway), 8);
        prim->y2 = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(sway), 8);
        setRGB0(prim, red, green, blue);
        setRGB2(prim, red, green, blue);
        setRGB1(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        if (i == SELF(PartyMember)->timer) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        if (i == 1) {
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
        }
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        sway = (LOHU(g_ScratchPad.cells.halves[2]) - 0x400) & ANGLE_MASK;
        setXY0(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(sway), 8), g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(sway), 8));
        sway     = (LOHU(g_ScratchPad.cells.halves[3]) - 0x400) & ANGLE_MASK;
        prim->x2 = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(sway), 8);
        prim->y2 = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(sway), 8);
        prim->x1 = g_ScratchPad.cells.halves[6];
        prim->y1 = g_ScratchPad.cells.halves[7];
        prim->x3 = g_ScratchPad.cells.halves[4];
        prim->y3 = g_ScratchPad.cells.halves[5];
        setRGB1(prim, grey, grey, grey);
        setRGB3(prim, grey, grey, grey);
        setRGB0(prim, red, green, blue);
        setRGB2(prim, red, green, blue);
        if (i == SELF(PartyMember)->timer) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        if (i == 1) {
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
        }
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        sway = (LOHU(g_ScratchPad.cells.halves[2]) - 0x400) & ANGLE_MASK;
        setXY2(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(sway), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(sway), g_ScratchPad.cells.halves[0]),
               g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(sway), 8), g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(sway), 8));
        sway     = (LOHU(g_ScratchPad.cells.halves[3]) - 0x400) & ANGLE_MASK;
        prim->x2 = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(sway), g_ScratchPad.cells.halves[1]);
        prim->y2 = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(sway), g_ScratchPad.cells.halves[1]);
        prim->x3 = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(sway), 8);
        prim->y3 = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(sway), 8);
        setRGB1(prim, red, green, blue);
        setRGB3(prim, red, green, blue);
        setRGB0(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        if (i == SELF(PartyMember)->timer) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        if (i == 1) {
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
        }
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
}

MATCH void func_801EFF40(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 1, g_Self);
}

MATCH void func_801EFF84(void) {
    s32 tpage;

    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 6), SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        func_800AF764();
        func_801F030C();
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    }
}

MATCH void func_801F00D4(void) {
    s32 value;
    s32 value2;
    u8  value3;

    value3                    = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = value3;
    if (!(value3 & BYTE_MASK)) {
        SELF(PartyMember)->unk_14      = 0x40000;
        SELF(PartyMember)->unk_20      = 0x20000;
        value2                         = RANDOM_MASK(0xF) + 0x1C;
        value                          = (SELF(PartyMember)->param.unk_0B & 0x1F) << 7;
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(value) * value2);
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos(value) * value2);
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        SELF(PartyMember)->unk_5D      = RANDOM_MASK(7) + 5;
        SELF(PartyMember)->unk_5E      = RANDOM_MASK(7) + 5;
        SELF(PartyMember)->unk_5F      = RANDOM_MASK(7) + 5;
        SELF(PartyMember)->unk_09      = 0x10;
        SELF(PartyMember)->timer       = 16;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F023C(void) {
    PartyMember* work  = SELF(PartyMember);
    u8           timer = work->unk_09 - 1;
    s32          value = work->unk_14 + work->unk_20;
    work->unk_09       = timer;
    work->unk_14       = value;
    work->pos.z.fixed += value;
    if (timer == 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F029C(void) {
    PartyMember* work  = SELF(PartyMember);
    u8           timer = work->timer - 1;
    s32          value = work->unk_14 + work->unk_20;
    work->timer        = timer;
    work->unk_14       = value;
    work->pos.z.fixed += value;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

MATCH void func_801F030C(void) {
    POLY_G3* prim;
    SVECTOR* edge;
    s32      radius;
    s32      r;
    s32      g;
    s32      b;
    u8       i;

    g_ScratchPadVectors[0].vx = SELF(PartyMember)->screen_x.value + ((rsin(0) * 32) >> 12);
    g_ScratchPadVectors[0].vy = SELF(PartyMember)->screen_y.value + ((rcos(0) * 32) >> 12);
    r                         = (s8)SELF(PartyMember)->unk_5D * SELF(PartyMember)->timer;
    g                         = (s8)SELF(PartyMember)->unk_5E * SELF(PartyMember)->timer;
    b                         = (s8)SELF(PartyMember)->unk_5F * SELF(PartyMember)->timer;
    i                         = 1;
    edge                      = &g_ScratchPadVectors[0];
    radius                    = 32;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, SELF(PartyMember)->screen_x.value, SELF(PartyMember)->screen_y.value, edge->vx, edge->vy, edge->vx = SELF(PartyMember)->screen_x.value + ((rsin(i << 9) * radius) >> 12),
               edge->vy = SELF(PartyMember)->screen_y.value + ((rcos(i << 9) * radius) >> 12));
        setRGB0(prim, r, g, b);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
        i++;
    } while (i < 9);
}

/* func_801F0500 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F0564 */
#include "overlays/bmagic/shared/Actor_Clear.h"
