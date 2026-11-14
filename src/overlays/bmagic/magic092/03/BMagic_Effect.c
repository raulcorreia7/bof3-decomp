#include "magic092_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_StartOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F07F8[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F07F8[i];
            g_BattleEffectBattler = D_801F07F8[i].target.party;
            func_801EF7FC();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

/* Clears the effect slot table and spawns one effect 0x28 at each selectable battler, the
 * enemies when the target selector holds 0x40 and the party otherwise, each starting 16
 * frames after the one before; then sets STP on colours 1 to 15 of work palette row 26. */
MATCH void func_801EED04(void) {
    u32 i;
    u32 slot;
    u32 count;
    u8  index;
    u8  battler;

    count = 0;
    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    g_Task->param.unk_0B = 0;
    if (g_Battle.target_selector & 0x40) {
        for (i = 0; i < 8; i++) {
            index   = i;
            battler = i + BATTLE_PARTY_CHARACTERS_COUNT;
            if (!Battle_SlotIsBlocked(battler)) {
                slot                               = Battle_AllocEffect(1, 0x28) & BYTE_MASK;
                g_BattleEffects[slot].target.party = g_Task;
                g_BattleEffects[slot].unk_03       = index;
                g_BattleEffects[slot].pos.x.fixed  = g_BattleEnemyBattlers[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_BattleEnemyBattlers[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_BattleEnemyBattlers[i].pos.z.fixed;
                g_BattleEffects[slot].arg.unk_09   = count * 16 + 1;
                count++;
                g_Task->param.unk_0B += 1;
            }
        }
    } else {
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            if (!Battle_SlotIsBlocked(i & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 0x28) & BYTE_MASK;
                g_BattleEffects[slot].target.party = g_Task;
                g_BattleEffects[slot].unk_03       = i;
                g_BattleEffects[slot].pos.x.fixed  = g_Game.members[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_Game.members[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_Game.members[i].pos.z.fixed;
                g_BattleEffects[slot].arg.unk_09   = count * 16 + 1;
                count++;
                g_Task->param.unk_0B += 1;
            }
        }
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = 0;
    for (i = 1; i < 16; i++) {
        MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[i] = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW)[i] | 0x8000;
    }
    g_GfxPalettePending = 1;
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EF000 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF044(void) {
    SYS_DISPATCH_BYTE(D_801F07C0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF580();
        PopMatrix();
    }
}

MATCH void func_801EF0CC(void) {
    PartyMember* work;
    u8           count;
    u8           i;
    u8           slot;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->param.unk_0B = 0;
        for (i = 0; i < 3; i++) {
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                work                                  = g_Task;
                BMAGIC_EFFECT_SLOTS[slot].header.mode = i != 0;
                BMAGIC_EFFECT_SLOTS[slot].header.step = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B      = i;
                BMAGIC_EFFECT_SLOTS[slot].header.flags |= BMAGIC_EFFECT_IN_USE | ACTOR_FLAG_HIDDEN;
                BMAGIC_EFFECT_SLOTS[slot].target.party = work;
                g_Task->param.unk_0B += 1;
            }
        }
        SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF1F0);

#include "overlays/bmagic/Effect_StepOnOwnTickFlag.h"

MATCH void func_801EF388(void) {
    u8 count;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    if (g_Task->param.unk_0B == 0x80) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            GFX_FreePaletteFadeTarget(&g_BattleEnemyBattlers[g_Task->unk_03]);
            func_800AF814((g_Task->unk_03 + 3) & BYTE_MASK);
            Battle_MarkDamaged((g_Task->unk_03 + 3) & BYTE_MASK);
        } else {
            GFX_FreePaletteFadeTarget((EnemyBattler*)&g_Game.members[g_Task->unk_03]);
            func_800AF814(g_Task->unk_03);
            Battle_MarkDamaged(g_Task->unk_03);
        }
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF580(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1) {
        tpage = 0x125;
    } else if (GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = 0x180;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    if (g_Task->unk_09 < 16) {
        D_1F800000.view.effect.params[7] = g_Task->unk_09 * 8;
    } else {
        D_1F800000.view.effect.params[7] = 0x80;
    }

    for (i = 1; i <= 8; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, LOHU(D_1F800000.view.effect.params[7]), LOHU(D_1F800000.view.effect.params[7]), LOHU(D_1F800000.view.effect.params[7]));
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }

    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801EF7FC(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 1, g_Task);
}

MATCH void func_801EF840(void) {
    SYS_DISPATCH_BYTE(D_801F07D8, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801EFB04();
    }
}

#include "overlays/bmagic/Effect_StartAtTarget.h"

MATCH void func_801EF940(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x11);
}

#include "overlays/bmagic/Effect_CountUpAndMarkBattler.h"

#include "overlays/bmagic/Effect_CountDownByTwoFinishAtOne.h"

INCLUDE_ASM(func_801EFB04);

MATCH void func_801F0260(void) {
    PartyMember* work;
    u16          x;
    u16          y;

    SYS_DISPATCH_BYTE(D_801F07E8, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        work = g_Task;
        if (work->param.unk_0B == 1) {
            x = work->unk_2E.half - MAGIC092_STEP_X;
            y = work->unk_30.half;
        } else {
            x = work->unk_2E.half + MAGIC092_STEP_X;
            y = work->unk_30.half;
        }
        y -= MAGIC092_RISE_Y;
        work->unk_2E.half = x;
        work->unk_30.half = y;
        func_801F04BC();
    }
}

#include "overlays/bmagic/Effect_AppearAtTarget.h"

MATCH void func_801F038C(void) {
    EFFECT_ADVANCE_AT_COUNT(2, 0x10);
}

#include "overlays/bmagic/Effect_StepOnTickFlag.h"

#include "overlays/bmagic/Effect_TickCounter.h"

/* Draws the glow fan at the effect point: eight triangles of a radius 64 to 79 picked
 * once, red at the centre with a fifth of it in green and blue, redrawing the blend
 * mode for each. */
MATCH void func_801F04BC(void) {
    POLY_G3* prim;
    s32      angle;
    s32      i;

    D_1F800000.view.effect.params[0] = RANDOM_MASK(0xF) + 0x40;
    i                                = 0;
    D_1F800000.view.effect.params[7] = g_Task->unk_09 * 10;
    do {
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = GFX_BeginPolyG3(1);
        setXY0(prim, g_Task->unk_2E.half, g_Task->unk_30.half);
        angle    = i << 9;
        prim->x1 = g_Task->unk_2E.half + FIXED_MUL(rsin(angle), D_1F800000.view.effect.params[0]);
        prim->y1 = g_Task->unk_30.half + FIXED_MUL(rcos(angle), D_1F800000.view.effect.params[0]);
        i++;
        angle    = i << 9;
        prim->x2 = g_Task->unk_2E.half + FIXED_MUL(rsin(angle), D_1F800000.view.effect.params[0]);
        prim->y2 = g_Task->unk_30.half + FIXED_MUL(rcos(angle), D_1F800000.view.effect.params[0]);
        setRGB0(prim, D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[7] / 5, D_1F800000.view.effect.params[7] / 5);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    } while (i < 8);
}

/* func_801F0758 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
