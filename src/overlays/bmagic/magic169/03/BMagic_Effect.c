#include "magic169_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC38(void) {
    Magic010SharedSteps handlers;
    PartyMember*        saved_task;
    PartyMember*        saved_battler;
    u8                  i;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);
    if (g_Task->header.flags != 0 && g_Task->header.mode != 0) {
        func_800AF764();
        func_801EF070();
    }
    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].target.party;
            func_801EF860();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

MATCH void func_801EED8C(void) {
    u16* src;
    u16* dst;
    u16  i;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    func_800AFD9C();
    g_Task->pos.z.fixed += TO_COORD(192);
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    MEM(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = MEM(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    g_GfxPalettePending                                 = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
    g_Task->unk_09       = 0;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
}

MATCH void func_801EEEB0(void) {
    u8           i;
    u8           row = 0;
    u32          slot;
    PartyMember* work;

    if (++g_Task->unk_09 == 16) {
        if (g_Battle.target_selector & BATTLE_TARGET_PARTY_SIDE) {
            i = 0;
            if (g_Battle.party_count != 0) {
                do {
                    slot                               = Battle_AllocEffect(1, 8) & BYTE_MASK;
                    work                               = g_Task;
                    g_BattleEffects[slot].header.mode  = 0;
                    g_BattleEffects[slot].unk_04       = i;
                    g_BattleEffects[slot].arg.unk_09   = row * 0x28 + 1;
                    g_BattleEffects[slot].target.party = work;
                    g_Task->param.unk_0B += 1;
                    row++, i++;
                } while (i < g_Battle.party_count);
            }
        }
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEFE0(void) {
    u8 timer;

    if (g_Task->param.unk_0B == 0) {
        timer          = g_Task->unk_09 - 1;
        g_Task->unk_09 = timer;
        if (!(timer & BYTE_MASK)) {
            g_Task->header.mode += 1;
        }
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EF070(void) {
    POLY_FT4* prim;
    s16*      shade;
    s32       tpage;
    s16       x;
    s16       y;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x2A5;
    } else {
        tpage = 0xB5;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(DR_MODE));
    shade  = &D_1F800006;
    prim   = (POLY_FT4*)g_GfxPrimCursor;
    *shade = g_Task->unk_09 * 8;
    x      = g_Task->unk_2E.half;
    y      = g_Task->unk_30.half;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, x - 0x38, y - 0x60, x + 0x38, y - 0x60, x - 0x38, y, x + 0x38, y);
    prim->tpage = GetTPage(1, 1, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUVWH(prim, 8, 8, 112, 96);
    setRGB0(prim, *shade, *shade, *shade);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_FT4));
}

/* func_801EF210 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF254(void) {
    BMagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC14, header.step);
}

MATCH void func_801EF2CC(void) {
    u8           count;
    u8           i;
    u8           slot;
    PartyMember* actor;
    PartyMember* work;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        actor          = &g_Game.members[g_Task->unk_04];
        g_Task->facing = actor->facing;
        WorldPos_Copy(&g_Task->pos, &actor->pos);
        g_Task->param.unk_0B = 0;
        g_Task->unk_09       = 8;
        g_Task->timer        = 0;
        g_Task->header.step += 1;
        i = 0;
        do {
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                work                                   = g_Task;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = ((i & BYTE_MASK) >> 2) + 0x10;
                BMAGIC_EFFECT_SLOTS[slot].target.party = work;
                g_Task->param.unk_0B += 1;
            }
            i++;
        } while (i < 24);
    }
}

MATCH void func_801EF444(void) {
    PartyMember* battler;
    u8           timer;
    PartyMember* work;

    work         = g_Task;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    battler      = &g_Game.members[work->unk_04];
    if (!(timer & BYTE_MASK)) {
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF4FC(void) {
    s32 cue;

    g_PaletteFades[g_Task->timer].offset.red++;
    g_PaletteFades[g_Task->timer].offset.green++;
    g_PaletteFades[g_Task->timer].offset.blue++;
    if (--g_Task->unk_09 == 0) {
        cue = EMI_CUE_ID(SND_BANK_COMMON, 0x02);
        if (g_Task->unk_04 & 0x1) {
            cue = EMI_CUE_ID(SND_BANK_COMMON, 0x01);
        }
        SND_QueueSelectionEffect(cue);
        g_Task->header.step++;
    }
}

#include "overlays/bmagic/Effect_NextStepUnderTickLimit.h"

/* Darkens the palette fade row the effect timer indexes and, when its wait runs out, frees the battler byte 0x04
 * names and tells the battle UI. */
MATCH void func_801EF688(void) {
    u8           count;
    u8           unk04;
    PartyMember* battler;

    /* FAKE: retail frame reserves 0x10 bytes no statement uses. */
    FAKE_STACK_PADS(u8, 0x10);

    unk04 = g_Task->unk_04;
    g_PaletteFades[g_Task->timer].offset.red -= 1;
    g_PaletteFades[g_Task->timer].offset.green -= 1;
    g_PaletteFades[g_Task->timer].offset.blue -= 1;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    battler        = &g_Game.members[unk04];
    if (!(count & BYTE_MASK)) {
        GFX_FreePaletteFadeTarget(battler);
        func_800AF814(g_Task->unk_04);
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF7D0(void) {
    if (g_Task->param.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        if (Battle_SlotIsBlocked(g_Task->unk_04) & BYTE_MASK) {
            Battle_MarkDamaged(g_Task->unk_04);
        }
        func_801E5988();
    }
}

MATCH void func_801EF860(void) {
    SYS_DISPATCH_TASK(D_801F0420, 1, g_Task);
}

#include "overlays/bmagic/Effect_DrawRings.h"

MATCH void func_801EFA18(void) {
    s32  phase;
    s32  speed;
    s16* angle_cell;
    u8   count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->unk_0C      = 8;
        angle_cell          = &D_1F800004;
        phase               = g_Task->param.unk_0B & 0xF;
        *angle_cell         = phase << 8;
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x800000;
        speed               = ((RANDOM_MASK(3)) << 20) + 0x200000;
        g_Task->unk_14      = speed;
        g_Task->unk_20      = speed / 16;
        g_Task->unk_5D      = (RANDOM_MASK(7)) + 6;
        g_Task->unk_5E      = (RANDOM_MASK(7)) + 6;
        g_Task->unk_5F      = (RANDOM_MASK(7)) + 6;
        g_Task->unk_09      = 0;
        g_Task->timer       = 16;
        g_Task->header.step++;
    }
}

MATCH void func_801EFBC4(void) {
    s32  phase;
    s32  b;
    s16* angle_cell;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B & 0xF;
    g_Task->unk_0C += 2;
    *angle_cell         = phase << 8;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    if (g_Task->unk_20 < g_Task->unk_14) {
        b              = g_Task->unk_14 - g_Task->unk_20;
        g_Task->unk_14 = b;
        g_Task->pos.z.fixed += b;
    }
    count          = g_Task->unk_09 + 2;
    g_Task->unk_09 = count;
    if (count == 16) {
        g_Task->header.step++;
    }
}

MATCH void func_801EFCF4(void) {
    s32  phase;
    s32  b;
    s16* angle_cell;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B & 0xF;
    g_Task->unk_0C += 1;
    *angle_cell         = phase << 8;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    if (g_Task->unk_20 < g_Task->unk_14) {
        b              = g_Task->unk_14 - g_Task->unk_20;
        g_Task->unk_14 = b;
        g_Task->pos.z.fixed += b;
    }
    if (g_FrameCount & 0x1) {
        count          = g_Task->unk_09 - 1;
        g_Task->unk_09 = count;
        if (count == 0) {
            g_BattleEffectBattler->param.unk_0B -= 1;
            Actor_Clear();
        }
    }
}

MATCH void BMagic_DrawRingTriangles(void) {
    POLY_G3* prim;
    s16      i;
    s16      x;
    s16      y;

    x                                = g_Task->unk_2E.half;
    y                                = g_Task->unk_30.half;
    D_1F800000.view.effect.params[0] = 8;
    D_1F800000.view.effect.params[3] = g_Task->unk_09 * 12;
    D_1F800000.view.effect.params[4] = (s8)g_Task->unk_5D * g_Task->unk_09;
    D_1F800000.view.effect.params[5] = (s8)g_Task->unk_5E * g_Task->unk_09;
    D_1F800000.view.effect.params[6] = (s8)g_Task->unk_5F * g_Task->unk_09;
    for (i = 0; i < 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, x, y, x + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]), y + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]),
               x + FIXED_MUL(rsin((i + 1) << 9), D_1F800000.view.effect.params[0]), y + FIXED_MUL(rcos((i + 1) << 9), D_1F800000.view.effect.params[0]));
        setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        setRGB1(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB2(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

MATCH void BMagic_DrawRingQuads(void) {
    POLY_G4* prim;
    s16      i;
    s16      x;
    s16      y;

    x                                = g_Task->unk_2E.half;
    y                                = g_Task->unk_30.half;
    D_1F800000.view.effect.params[0] = 8;
    D_1F800000.view.effect.params[1] = 20;
    D_1F800000.view.effect.params[4] = (s8)g_Task->unk_5D * g_Task->unk_09;
    D_1F800000.view.effect.params[5] = (s8)g_Task->unk_5E * g_Task->unk_09;
    D_1F800000.view.effect.params[6] = (s8)g_Task->unk_5F * g_Task->unk_09;
    for (i = 0; i < 8; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[1]), y + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[1]));
        prim->x2 = x + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]);
        prim->y2 = y + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]);
        prim->x1 = x + FIXED_MUL(rsin((i + 1) << 9), D_1F800000.view.effect.params[1]);
        prim->y1 = y + FIXED_MUL(rcos((i + 1) << 9), D_1F800000.view.effect.params[1]);
        prim->x3 = x + FIXED_MUL(rsin((i + 1) << 9), D_1F800000.view.effect.params[0]);
        prim->y3 = y + FIXED_MUL(rcos((i + 1) << 9), D_1F800000.view.effect.params[0]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB3(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

/* func_801F0368 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F03CC */
#include "overlays/bmagic/Actor_Clear.h"
