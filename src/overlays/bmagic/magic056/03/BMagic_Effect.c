#include "magic056_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

/* Starts the effect: centres the camera, queues a copy of the acting battler as effect
 * 0x55 in mode 3, sets STP on colours 1 to 15 of the first two palettes of work row 26
 * and clears their colour 0, then fills bytes 0x24, 0x27 and 0x28 of the effect from the
 * effect battler and marks the battler busy. */
/* func_801EEC94 */
MATCH void BMagic_SacrificeInit(void) {
    PartyMember*     work;
    u16*             dst;
    u16*             src;
    u32              i;
    u32              index;
    u8               active;
    BattleWorkImage* slot;
    BattleWorkImage* image;
    u32              enemy;
    PartyMember*     member;

    Battle_CenterCamera();
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(8, 0);
    index  = Battle_AllocEffect(1, BMAGIC_EFFECT_SACRIFICE) & BYTE_MASK;
    active = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        slot   = (BattleWorkImage*)&g_BattleEffects[index];
        member = &g_Game.members[active];
        *slot  = *(BattleWorkImage*)member;
    } else {
        slot  = (BattleWorkImage*)&g_BattleEffects[index];
        enemy = active - BATTLE_PARTY_CHARACTERS_COUNT;
        image = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
        *slot = *image;
    }
    work                                = SELF(PartyMember);
    g_BattleEffects[index].header.mode  = BMAGIC_SACRIFICE_EFFECT_CLONE;
    g_BattleEffects[index].unk_06       = 1;
    g_BattleEffects[index].header.step  = 0;
    g_BattleEffects[index].effect_type  = BMAGIC_EFFECT_SACRIFICE;
    g_BattleEffects[index].target.party = work;
    SELF(PartyMember)->param.unk_0B += 1;
    dst = MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW));
    src = MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW));
    for (i = 1; i < 16; i++) {
        dst[i]      = src[i] | PSX_COLOR_STP_BIT;
        dst[i + 16] = src[i + 16] | PSX_COLOR_STP_BIT;
    }
    *MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW))        = 0;
    *MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW) + 0x20) = 0;
    g_GfxPalettePending                                                      = 1;
    SELF(PartyMember)->unk_27                                                = Battle_CopyCellPalette(g_BattleEffectBattler);
    SELF(PartyMember)->unk_28                                                = g_BattleEffectBattler->unk_28;
    SELF(PartyMember)->unk_24                                                = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(SELF(PartyMember));
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

/* func_801EEF3C */
MATCH s32 BMagic_SacrificeEnd(void) {
    if (SELF(PartyMember)->param.unk_0B == 0) {
        g_BattleEffectBattler->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        func_800AFC54();
        Battle_SelectActiveBattlerScript(0x1C, 0);
        Battle_MarkDamaged(g_Battle.target_selector);
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            g_Game.members[g_Battle.active_battler].header.mode = 6;
            g_Game.members[g_Battle.active_battler].header.step = 4;
            g_Game.members[g_Battle.active_battler].chr.hp      = 0;
            g_Game.members[g_Battle.active_battler].chr.status  = STATUS_KO;
            GFX_PaletteFreeFadeTarget(&g_Game.members[g_Battle.active_battler]);
        } else {
            ENEMY_COMBATANT(g_Battle.active_battler).header.mode = 6;
            ENEMY_COMBATANT(g_Battle.active_battler).header.step = 4;
            ENEMY_COMBATANT(g_Battle.active_battler).hp          = 0;
            ENEMY_COMBATANT(g_Battle.active_battler).status      = STATUS_KO;
            GFX_PaletteFreeFadeTarget(g_BattleEnemies + g_Battle.active_battler * BATTLE_ENEMY_STRIDE);
        }
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

/* func_801EF1B0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EF1F4 */
MATCH void BMagic_SacrificeDomeUpdate(void) {
    BMAGIC_DISPATCH_AND_DRAW(g_BMagicSacrificeDomeSteps, BMagic_SacrificeDrawDome);
}

#include "overlays/bmagic/shared/Effect_CopyBattlerCoords.h"

/* func_801EF2DC */
MATCH void BMagic_SacrificeDomeExpand(void) {
    u8 counter;

    if (SELF(PartyMember)->unk_09 == 4) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
    }
    SP_REF(s16, 0)            = SELF(PartyMember)->unk_09 * 0x1C;
    counter                   = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0xC) {
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EF37C */
MATCH void BMagic_SacrificeDomeEnd(void) {
    u8 count;

    SP_REF(s16, 0u) = (SELF(PartyMember)->unk_09 * 4) + 0x120;
    SELF(PartyMember)->timer += 1;
    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x28) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF4C0 */
MATCH void BMagic_SacrificeDrawDome(void) {
    POLY_GT4* prim;
    long      depth;
    long      flag;
    s32       tpage;
    s32       band;
    s32       row;
    s32       i;
    s32       x;
    s32       y;

    for (band = 24, row = 1; band >= 17; band--, row++) {
        g_ScratchPad.cells.halves[3] = 0x81;
        g_ScratchPad.cells.halves[4] = 0x81;
        if (row - 1 < SELF(PartyMember)->unk_09 - 16) {
            g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_09 - 15 - row;
            if (g_ScratchPad.cells.halves[3] < 17) {
                g_ScratchPad.cells.halves[3] = 0x81 - g_ScratchPad.cells.halves[3] * 8;
            } else {
                g_ScratchPad.cells.halves[3] = 1;
            }
        }
        if (row < SELF(PartyMember)->unk_09 - 16) {
            g_ScratchPad.cells.halves[4] = SELF(PartyMember)->unk_09 - 16 - row;
            if (g_ScratchPad.cells.halves[4] < 17) {
                g_ScratchPad.cells.halves[4] = 0x81 - g_ScratchPad.cells.halves[4] * 8;
            } else {
                g_ScratchPad.cells.halves[4] = 1;
            }
        }
        g_ScratchPad.cells.halves[1] = FIXED_MUL(rcos((band - 1) << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPad.cells.halves[2] = FIXED_MUL(rcos(band << 7), g_ScratchPad.cells.halves[0]);
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]),
                  g_ScratchPadVectors[0].vz = FIXED_MUL(rsin((band - 1) << 7), g_ScratchPad.cells.halves[0]));
        setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[2]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[2]),
                  g_ScratchPadVectors[2].vz = FIXED_MUL(rsin(band << 7), g_ScratchPad.cells.halves[0]));
        for (i = 1; i <= 32; i++) {
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[1]);
            g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[1]);
            g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[2]);
            g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[2]);
            x                         = (g_ScratchPadVectors[3].vx << 9) + SELF(PartyMember)->pos.x.fixed;
            y                         = (g_ScratchPadVectors[3].vy << 9) + SELF(PartyMember)->pos.y.fixed;
            tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, 2, sizeof(DR_MODE));
            prim = (POLY_GT4*)g_GfxPrimCursor;
            SetPolyGT4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x340, 0x100);
            prim->clut  = GetClut(0, 0x1FA);
            setUV4(prim, i * 8, (band - 16) * 8 + 0x20, i * 8 + 8, (band - 16) * 8 + 0x20, i * 8, (band - 16) * 8 + 0x28, i * 8 + 8, (band - 16) * 8 + 0x28);
            setRGB0(prim, LOHU(g_ScratchPad.cells.halves[4]), LOHU(g_ScratchPad.cells.halves[4]), LOHU(g_ScratchPad.cells.halves[4]));
            setRGB1(prim, LOHU(g_ScratchPad.cells.halves[4]), LOHU(g_ScratchPad.cells.halves[4]), LOHU(g_ScratchPad.cells.halves[4]));
            setRGB2(prim, LOHU(g_ScratchPad.cells.halves[3]), LOHU(g_ScratchPad.cells.halves[3]), LOHU(g_ScratchPad.cells.halves[3]));
            setRGB3(prim, LOHU(g_ScratchPad.cells.halves[3]), LOHU(g_ScratchPad.cells.halves[3]), LOHU(g_ScratchPad.cells.halves[3]));
            Area_CellAddPrim(x, y, 2, sizeof(POLY_GT4));
        }
    }
}

/* func_801EFA50 */
MATCH void BMagic_SacrificeShadowUpdate(void) {
    BMAGIC_DISPATCH_AND_DRAW(g_BMagicSacrificeShadowSteps, BMagic_SacrificeDrawShadow);
}

MATCH void Effect_CopyBattlerCoords2(void) {
    BMAGIC_COPY_BATTLER_COORDS();
}

/* func_801EFB38 */
MATCH void BMagic_SacrificeShadowGrow(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    work->timer += 2;
    work = SELF(PartyMember);
    work->unk_09++;
    if (work->unk_09 == 12) {
        work = SELF(PartyMember);
        work->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpAndStepAt30.h"

#include "overlays/bmagic/shared/Effect_CountDownTimerCapped.h"

/* Draws the shadow disc of sixteen subtractive triangles behind the battlers round the effect point; the radius
 * follows the counter (a wider rule from step 2 on) and the centre colour the timer. */
/* func_801EFC74 */
MATCH void BMagic_SacrificeDrawShadow(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      scale;

    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256));
    if (SELF(PartyMember)->header.step >= 2) {
        g_ScratchPad.cells.halves[0] = ((SELF(PartyMember)->unk_09 * 4 + 0x210) * rcos(0x800)) >> 12;
    } else {
        scale                        = rcos(0x800) * 48;
        g_ScratchPad.cells.halves[0] = (scale * SELF(PartyMember)->unk_09) >> 12;
    }
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->timer * 8;
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->timer * 6;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim = GFX_BeginPolyG3(1);
        GFX_STEP_TRIANGLE_FAN(i << 8, g_ScratchPad.cells.halves[0]);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
}

/* func_801EFF28 */
MATCH void BMagic_SacrificeCloneUpdate(void) {
    BMagicSacrificeCloneSteps handlers;

    handlers = g_BMagicSacrificeCloneSteps;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
}

/* func_801EFFE8 */
MATCH void BMagic_SacrificeCloneStart(void) {
    SELF(PartyMember)->unk_27 = BATTLE_ACTIVE_WORK->unk_27;
    SELF(PartyMember)->header.step++;
}

#include "overlays/bmagic/shared/Effect_PrimeTintOnScriptReady.h"

/* func_801F00C8 */
MATCH void BMagic_SacrificeCloneHide(void) {
    PartyMember* work;
    PartyMember* source;

    SELF(PartyMember)->unk_5D -= 16;
    SELF(PartyMember)->unk_5E -= 16;
    SELF(PartyMember)->unk_5F -= 16;
    if ((s8)SELF(PartyMember)->unk_5D == -128) {
        work   = SELF(PartyMember);
        source = BATTLE_ACTIVE_WORK;
        WorldPos_Copy(&work->pos, &source->pos);
        work->header.step += 1;
    }
}

/* func_801F0178 */
MATCH void BMagic_SacrificeCloneShow(void) {
    SELF(PartyMember)->unk_5D += 0x10;
    SELF(PartyMember)->unk_5E += 0x10;
    SELF(PartyMember)->unk_5F += 0x10;
    if ((s8)SELF(PartyMember)->unk_5D == 0) {
        SELF(PartyMember)->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(PartyMember)->unk_5C = 0;
        SELF(PartyMember)->unk_09 = 8;
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801F023C */
MATCH void BMagic_SacrificeCloneCast(void) {
    PartyMember* saved;
    PartyMember* task;
    u8           slot;
    u8           count;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_SACRIFICE);
        g_BattleEffects[slot].target.party = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = BMAGIC_SACRIFICE_EFFECT_DOME;
        g_BattleEffectBattler->param.unk_0B += 1;
        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_SACRIFICE);
        g_BattleEffects[slot].target.party = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = BMAGIC_SACRIFICE_EFFECT_SHADOW;
        g_BattleEffectBattler->param.unk_0B += 1;
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            saved       = g_GameState;
            g_GameState = &g_Game.members[g_Battle.active_battler];
            Battle_PlayEffectSE(0);
            g_GameState = saved;
        }
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            task = SELF(PartyMember);
            SELF_SET(&g_Game.members[g_Battle.active_battler]);
            Script_Select(SELF(PartyMember)->facing + 16);
            SELF_SET(task);
            Script_Select(task->facing + 16);
        } else {
            func_801E257C(g_Battle.active_battler, 4);
        }
        SELF(PartyMember)->unk_09 = 30;
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801F042C */
MATCH void BMagic_SacrificeCloneHold(void) {
    u8 count;

    Script_AnimStepLoop();
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(PartyMember)->unk_5C = 1;
        SELF(PartyMember)->unk_5D = 0;
        SELF(PartyMember)->unk_5E = 0;
        SELF(PartyMember)->unk_5F = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801F04EC */
MATCH void BMagic_SacrificeCloneVanish(void) {
    PartyMember* member;
    PartyMember* work;

    Script_AnimStepLoop();
    SELF(PartyMember)->unk_5D -= 0x10;
    SELF(PartyMember)->unk_5E -= 0x10;
    SELF(PartyMember)->unk_5F -= 0x10;
    if ((s8)SELF(PartyMember)->unk_5D == -0x80) {
        work              = SELF(PartyMember);
        work->pos.x.fixed = g_BattleActiveActor->pos.x.fixed;
        /* FAKE: retail re-reads the party cell for the next copy. */
        FAKE_BARRIER();
        work->pos.y.fixed = g_BattleActiveActor->pos.y.fixed;
        /* FAKE: retail re-reads the party cell for the next copy. */
        FAKE_BARRIER();
        work->pos.z.fixed = g_BattleActiveActor->pos.z.fixed;
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            member = &g_Game.members[g_Battle.active_battler];
            g_Self = member;
            Script_Select(member->facing + 0x1C);
            g_Self = work;
            Script_Select(work->facing + 0x1C);
        } else {
            func_801E257C(g_Battle.active_battler, 4);
        }
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801F0658 */
MATCH void BMagic_SacrificeCloneReturn(void) {
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        SELF(PartyMember)->unk_5D += 0x10;
        SELF(PartyMember)->unk_5E += 0x10;
        SELF(PartyMember)->unk_5F += 0x10;
        if ((s8)SELF(PartyMember)->unk_5D == 0) {
            g_BattleEffectBattler->param.unk_0B -= 1;
            SELF(PartyMember)->header.step += 1;
        }
    }
}

/* func_801F0724 */
MATCH void BMagic_SacrificeCloneEnd(void) {
    Effect_Reset();
}
