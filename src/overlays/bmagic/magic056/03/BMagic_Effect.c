#include "magic056_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

/* Starts the effect: centres the camera, queues a copy of the acting battler as effect
 * 0x55 in mode 3, sets STP on colours 1 to 15 of the first two palettes of work row 26
 * and clears their colour 0, then fills bytes 0x24, 0x27 and 0x28 of the effect from the
 * effect battler and marks the battler busy. */
MATCH void func_801EEC94(void) {
    PartyMember*     work;
    u16*             dst;
    u16*             src;
    u32              i;
    u32              index;
    u8               active;
    BattleWorkImage* slot;
    BattleWorkImage* row;
    u32              enemy;
    PartyMember*     member;

    Battle_CenterCamera();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
    func_800AEF98(8, 0);
    index  = Battle_AllocEffect(1, 0x55) & BYTE_MASK;
    active = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        slot   = (BattleWorkImage*)&g_BattleEffects[index];
        member = &g_Game.members[active];
        *slot  = *(BattleWorkImage*)member;
    } else {
        slot  = (BattleWorkImage*)&g_BattleEffects[index];
        enemy = active - BATTLE_PARTY_CHARACTERS_COUNT;
        row   = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
        *slot = *row;
    }
    work                                 = g_Task;
    g_BattleEffects[index].header.mode   = 3;
    g_BattleEffects[index].unk_06        = 1;
    g_BattleEffects[index].header.step   = 0;
    g_BattleEffects[index].handler_index = 0x55;
    g_BattleEffects[index].target.party  = work;
    g_Task->param.unk_0B += 1;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (i = 1; i < 16; i++) {
        dst[i]      = src[i] | 0x8000;
        dst[i + 16] = src[i + 16] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)        = 0;
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW + 0x20) = 0;
    g_GfxPalettePending                                             = 1;
    g_Task->unk_27                                                  = func_800AFB48(g_BattleEffectBattler);
    g_Task->unk_28                                                  = g_BattleEffectBattler->unk_28;
    g_Task->unk_24                                                  = g_BattleEffectBattler->unk_24;
    func_800AF8F0(g_Task);
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH s32 func_801EEF3C(void) {
    if (g_Task->param.unk_0B == 0) {
        g_BattleEffectBattler->header.flags &= ~0x40;
        func_800AFC54();
        func_800AEF98(0x1C, 0);
        Battle_MarkDamaged(g_Battle.target_selector);
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            g_Game.members[g_Battle.active_battler].header.mode = 6;
            g_Game.members[g_Battle.active_battler].header.step = 4;
            g_Game.members[g_Battle.active_battler].chr.hp      = 0;
            g_Game.members[g_Battle.active_battler].chr.status  = STATUS_KO;
            GFX_FreePaletteFadeTarget(&g_Game.members[g_Battle.active_battler]);
        } else {
            ENEMY_COMBATANT(g_Battle.active_battler).header.mode = 6;
            ENEMY_COMBATANT(g_Battle.active_battler).header.step = 4;
            ENEMY_COMBATANT(g_Battle.active_battler).hp          = 0;
            ENEMY_COMBATANT(g_Battle.active_battler).status      = STATUS_KO;
            GFX_FreePaletteFadeTarget(g_BattleEnemies + g_Battle.active_battler * BATTLE_ENEMY_STRIDE);
        }
        g_Task->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

/* func_801EF1B0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF1F4(void) {
    SYS_DISPATCH_BYTE(D_801F0754, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF4C0();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CopyBattlerCoords.h"

MATCH void func_801EF2DC(void) {
    u8 counter;

    if (g_Task->unk_09 == 4) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
    }
    SP_REF(s16, 0) = g_Task->unk_09 * 0x1C;
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0xC) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF37C(void) {
    u8 count;

    SP_REF(s16, 0u) = (g_Task->unk_09 * 4) + 0x120;
    g_Task->timer += 1;
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x28) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF4C0);

MATCH void func_801EFA50(void) {
    SYS_DISPATCH_BYTE(D_801F0760, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFC74();
        PopMatrix();
    }
}

MATCH void Effect_CopyBattlerCoords2(void) {
    BMAGIC_COPY_BATTLER_COORDS();
}

MATCH void func_801EFB38(void) {
    PartyMember* work;

    work = g_Task;
    work->timer += 2;
    work = g_Task;
    work->unk_09++;
    if (work->unk_09 == 12) {
        work = g_Task;
        work->header.step++;
    }
}

#include "overlays/bmagic/Effect_CountUpAndStepAt30.h"

#include "overlays/bmagic/Effect_CountDownTimerCapped.h"

/* Draws the glow disc of sixteen shaded triangles round the effect point; the radius
 * follows byte 0x09 (a wider rule from step 2 on) and the centre colour the effect timer. */
MATCH void func_801EFC74(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      scale;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 2, 320, 256), 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    if (g_Task->header.step >= 2) {
        D_1F800000.view.effect.params[0] = ((g_Task->unk_09 * 4 + 0x210) * rcos(0x800)) >> 12;
    } else {
        scale                            = rcos(0x800) * 48;
        D_1F800000.view.effect.params[0] = (scale * g_Task->unk_09) >> 12;
    }
    D_1F800000.view.effect.params[3] = g_Task->timer * 8;
    D_1F800000.view.effect.params[4] = g_Task->timer * 6;
    setVector(&D_1F800014[2], FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]), FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]), 0);
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
}

MATCH void func_801EFF28(void) {
    Magic056Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
}

MATCH void func_801EFFE8(void) {
    g_Task->unk_27 = BATTLE_ACTIVE_WORK->unk_27;
    g_Task->header.step++;
}

#include "overlays/bmagic/Effect_PrimeTintOnScriptReady.h"

MATCH void func_801F00C8(void) {
    PartyMember* work;
    PartyMember* source;

    g_Task->unk_5D -= 16;
    g_Task->unk_5E -= 16;
    g_Task->unk_5F -= 16;
    if ((s8)g_Task->unk_5D == -128) {
        work   = g_Task;
        source = BATTLE_ACTIVE_WORK;
        WorldPos_Copy(&work->pos, &source->pos);
        work->header.step += 1;
    }
}

MATCH void func_801F0178(void) {
    g_Task->unk_5D += 0x10;
    g_Task->unk_5E += 0x10;
    g_Task->unk_5F += 0x10;
    if ((s8)g_Task->unk_5D == 0) {
        g_Task->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 0;
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F023C(void) {
    PartyMember* saved;
    PartyMember* task;
    u8           slot;
    u8           count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        slot                               = Battle_AllocEffect(1, 0x55);
        g_BattleEffects[slot].target.party = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffectBattler->param.unk_0B += 1;
        slot                               = Battle_AllocEffect(1, 0x55);
        g_BattleEffects[slot].target.party = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 2;
        g_BattleEffectBattler->param.unk_0B += 1;
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            saved       = g_GameState;
            g_GameState = &g_Game.members[g_Battle.active_battler];
            func_801DD858(0);
            g_GameState = saved;
        }
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            task = g_Task;
            TASK_SET(&g_Game.members[g_Battle.active_battler]);
            Actor_SelectScript(g_Task->facing + 16);
            TASK_SET(task);
            Actor_SelectScript(task->facing + 16);
        } else {
            func_801E257C(g_Battle.active_battler, 4);
        }
        g_Task->unk_09 = 30;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F042C(void) {
    u8 count;

    Actor_StepAnimLoop();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 1;
        g_Task->unk_5D = 0;
        g_Task->unk_5E = 0;
        g_Task->unk_5F = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F04EC(void) {
    PartyMember* member;
    PartyMember* work;

    Actor_StepAnimLoop();
    g_Task->unk_5D -= 0x10;
    g_Task->unk_5E -= 0x10;
    g_Task->unk_5F -= 0x10;
    if ((s8)g_Task->unk_5D == -0x80) {
        work              = g_Task;
        work->pos.x.fixed = D_8014637C->pos.x.fixed;
        /* FAKE: retail re-reads the party cell for the next copy. */
        FAKE_BARRIER();
        work->pos.y.fixed = D_8014637C->pos.y.fixed;
        /* FAKE: retail re-reads the party cell for the next copy. */
        FAKE_BARRIER();
        work->pos.z.fixed = D_8014637C->pos.z.fixed;
        if (g_Battle.active_battler < 3) {
            member = &g_Game.members[g_Battle.active_battler];
            g_Task = member;
            Actor_SelectScript(member->facing + 0x1C);
            g_Task = work;
            Actor_SelectScript(work->facing + 0x1C);
        } else {
            func_801E257C(g_Battle.active_battler, 4);
        }
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0658(void) {
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        g_Task->unk_5D += 0x10;
        g_Task->unk_5E += 0x10;
        g_Task->unk_5F += 0x10;
        if ((s8)g_Task->unk_5D == 0) {
            g_BattleEffectBattler->param.unk_0B -= 1;
            g_Task->header.step += 1;
        }
    }
}

MATCH void func_801F0724(void) {
    func_801E5988();
}
