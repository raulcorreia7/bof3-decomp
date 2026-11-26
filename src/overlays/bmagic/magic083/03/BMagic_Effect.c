#include "magic083_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_RunSlotsWithSetup.h"

/* Clears the effect slot table, then spawns one effect on each selectable battler of the targeted side at its position, and copies the first 32 colours of palette row 26 back from the arena. */
/* func_801EED04 */
MATCH void func_801EED04(void) {
    PartyMember* owner;
    u16*         dst;
    u16*         src;
    u8           slot;
    u8           count;
    u8           index;
    u8           i;

    count = 0;
    BMAGIC_CLEAR_EFFECTS(i);
    TASK(PartyMember)->unk_04       = BMagic_ShieldVariant();
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode++;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            index = i + 3;
            if (!(Battle_SlotIsBlocked(index) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 34) & BYTE_MASK;
                owner                              = TASK(PartyMember);
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_03       = i;
                g_BattleEffects[slot].target.party = owner;
                g_BattleEffects[slot].unk_04       = TASK(PartyMember)->unk_04;
                g_BattleEffects[slot].unk_0B       = count;
                g_BattleEffects[slot].arg.unk_09   = (count * 16) + 1;
                g_BattleEffects[slot].pos.x.fixed  = g_BattleEnemyBattlers[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_BattleEnemyBattlers[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_BattleEnemyBattlers[i].pos.z.fixed;
                TASK(PartyMember)->param.unk_0B++;
                count++;
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (!(Battle_SlotIsBlocked(i) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 34) & BYTE_MASK;
                owner                              = TASK(PartyMember);
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_03       = i;
                g_BattleEffects[slot].target.party = owner;
                g_BattleEffects[slot].unk_04       = TASK(PartyMember)->unk_04;
                g_BattleEffects[slot].unk_0B       = count;
                g_BattleEffects[slot].arg.unk_09   = (count * 16) + 1;
                g_BattleEffects[slot].pos.x.fixed  = g_Game.members[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_Game.members[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_Game.members[i].pos.z.fixed;
                TASK(PartyMember)->param.unk_0B++;
                count++;
            }
        }
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EF0CC */
MATCH s32 BMagic_ShieldVariant(void) {
    if (g_Battle.action_type != BATTLE_ACTION_ABILITY && g_Battle.action_id == 0x136) {
        g_Battle.action_id = ABILITY_SHIELD;
    }
    return 0;
}

/* func_801EF108 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EF14C */
MATCH void BMagic_ShieldBattlerUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicShieldBattlerSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Effect_SetActorMatrix();
        BMagic_ShieldDrawRing();
        BMagic_ShieldDrawDisc();
        PopMatrix();
    }
}

/* func_801EF1DC */
MATCH void BMagic_ShieldBattlerStart(void) {
    void* battler;
    u8    count;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count == 0) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            battler = &g_BattleEnemyBattlers[TASK(PartyMember)->unk_03];
        } else {
            battler = &g_Game.members[TASK(PartyMember)->unk_03];
        }
        GFX_PaletteFreeFadeTarget(battler);
        TASK(PartyMember)->timer  = GFX_PaletteAllocFade(battler, 0, 0, 0, 1);
        TASK(PartyMember)->unk_09 = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EF2F8 */
MATCH void BMagic_ShieldBattlerGlow(void) {
    PartyMember* owner;
    u8           slot;
    u8           base;
    u8           i;

    if (g_PaletteFades[TASK(PartyMember)->timer].offset.r != 8) {
        g_PaletteFades[TASK(PartyMember)->timer].offset.r++;
        g_PaletteFades[TASK(PartyMember)->timer].offset.g++;
        g_PaletteFades[TASK(PartyMember)->timer].offset.b++;
    }
    if (++TASK(PartyMember)->unk_09 == 16) {
        base                            = TASK(PartyMember)->param.unk_0B;
        TASK(PartyMember)->param.unk_0B = 0;
        for (i = 0; i < 3; i++) {
            slot = BMagic_AllocEffect();
            if (slot != 0xFF) {
                owner                                  = TASK(PartyMember);
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].header.step  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_03       = base + (i << 4);
                BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
                BMAGIC_EFFECT_SLOTS[slot].unk_04       = TASK(PartyMember)->unk_04;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i * 10;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 8 + 1;
                BMAGIC_EFFECT_SLOTS[slot].unk_0A       = 1;
                TASK(PartyMember)->param.unk_0B++;
            }
        }
        TASK(PartyMember)->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_StepOnZeroTick.h"

/* func_801EF55C */
MATCH void BMagic_ShieldBattlerRestore(void) {
    PartyMember* battler;
    u8           slot;

    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        slot    = TASK(PartyMember)->unk_03 + 3;
        battler = (PartyMember*)&g_BattleEnemyBattlers[TASK(PartyMember)->unk_03];
    } else {
        slot    = TASK(PartyMember)->unk_03;
        battler = &g_Game.members[slot];
    }
    if (g_PaletteFades[TASK(PartyMember)->timer].offset.r != 0) {
        g_PaletteFades[TASK(PartyMember)->timer].offset.r--;
        g_PaletteFades[TASK(PartyMember)->timer].offset.g--;
        g_PaletteFades[TASK(PartyMember)->timer].offset.b--;
    }
    if (--TASK(PartyMember)->unk_09 == 0) {
        GFX_PaletteFreeFadeTarget(battler);
        Battle_FadePoisonedBattler(slot);
        func_800AEEC8(TASK(PartyMember)->unk_04, TASK(PartyMember)->unk_03);
        TASK(PartyMember)->param.unk_0B++;
        TASK(PartyMember)->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_TickOnZeroTick.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF844 */
MATCH void BMagic_ShieldDrawDisc(void) {
    POLY_G3* poly;
    s32      tpage;
    s32      i;
    long     depth;
    long     flag;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[3] = TASK(PartyMember)->unk_09 * 5;
    g_ScratchPad.cells.halves[4] = g_BMagicShieldDiscTints[TASK(PartyMember)->unk_04][0] * TASK(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[5] = g_BMagicShieldDiscTints[TASK(PartyMember)->unk_04][1] * TASK(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[6] = g_BMagicShieldDiscTints[TASK(PartyMember)->unk_04][2] * TASK(PartyMember)->unk_09;
    g_ScratchPadVectors[2].vx    = (u32)rsin(0) >> 5;
    g_ScratchPadVectors[2].vy    = (u32)rcos(0) >> 5;
    for (i = 1; i < 17; i++) {
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], (u32)rsin(i << 8) >> 5, (u32)rcos(i << 8) >> 5, 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        poly                      = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, &depth, &flag);
        setRGB0(poly, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB1(poly, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(poly, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

/* func_801EFB24 */
MATCH void BMagic_ShieldDrawRing(void) {
    POLY_G4* poly;
    s32      tpage;
    s32      i;
    long     depth;
    long     flag;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[4] = g_BMagicShieldRingTints[TASK(PartyMember)->unk_04][0] * TASK(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[5] = g_BMagicShieldRingTints[TASK(PartyMember)->unk_04][1] * TASK(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[6] = g_BMagicShieldRingTints[TASK(PartyMember)->unk_04][2] * TASK(PartyMember)->unk_09;
    g_ScratchPadVectors[1].vx    = (u32)rsin(0) >> 5;
    g_ScratchPadVectors[1].vy    = (u32)rcos(0) >> 5;
    g_ScratchPadVectors[3].vx    = (u32)rsin(0) >> 4;
    g_ScratchPadVectors[3].vy    = (u32)rcos(0) >> 4;
    for (i = 1; i < 17; i++) {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[1].vx = (u32)rsin(i << 8) >> 5;
        g_ScratchPadVectors[1].vy = (u32)rcos(i << 8) >> 5;
        setVector(&g_ScratchPadVectors[3], (u32)rsin(i << 8) >> 4, (u32)rcos(i << 8) >> 4, 0);
        g_ScratchPadVectors[2].vz = 0;
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        poly                      = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3,
                      &depth, &flag);
        setRGB0(poly, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(poly, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(poly, 1, 1, 1);
        setRGB3(poly, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

/* func_801EFE54 */
MATCH void BMagic_ShieldGemDispatch(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Task);
}

/* func_801EFE98 */
MATCH void BMagic_ShieldGemUpdate(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 2, g_Task);
}

#include "overlays/bmagic/shared/Effect_LaunchFromRing.h"

/* func_801F0010 */
MATCH void BMagic_ShieldGemRise(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;
    PartyMember* reset;

    Battle_ProjectRange();
    BMagic_SetXFixed((RANDOM_MASK(3)) | 0x18);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(BMagic_ShieldDrawGem);
    if (g_FrameCount & 0x1) {
        TASK(PartyMember)->unk_09 += 1;
    }
    task         = TASK(PartyMember);
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        reset         = TASK(PartyMember);
        reset->unk_14 = -0x10;
        reset->timer  = 8;
        reset->unk_20 = 4;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F0104 */
MATCH void BMagic_ShieldGemFall(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;

    Battle_ProjectRange();
    BMagic_SetXFixed((RANDOM_MASK(3)) | 0x18);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(BMagic_ShieldDrawGem);
    if (g_FrameCount & 0x1) {
        TASK(PartyMember)->unk_09 += 1;
    }
    task         = TASK(PartyMember);
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        TASK(PartyMember)->timer = 28 - TASK(PartyMember)->param.unk_0B;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F01F8 */
MATCH void BMagic_ShieldGemSpinUp(void) {
    s32 spin_ticks;
    s32 radius;
    s32 sound;
    u8  remaining;
    u8  battler_index;

    Battle_ProjectRange();
    if ((TASK(PartyMember)->unk_0C == 4) && (TASK(PartyMember)->timer < 5U)) {
        radius = (RANDOM_MASK(3)) | 0x40;
    } else {
        radius = (RANDOM_MASK(3)) | 0x18;
    }
    BMagic_SetXFixed(radius);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(BMagic_ShieldDrawGem);
    if (TASK(PartyMember)->unk_0C < 4) {
        spin_ticks                = TASK(PartyMember)->unk_10 + 1;
        TASK(PartyMember)->unk_10 = spin_ticks;
        if (!(spin_ticks & 0x7)) {
            TASK(PartyMember)->unk_0C += 1;
        }
    }
    TASK(PartyMember)->unk_09 += TASK(PartyMember)->unk_0C;
    if (TASK(PartyMember)->unk_0C == 4) {
        remaining                = TASK(PartyMember)->timer - 1;
        TASK(PartyMember)->timer = remaining;
        if (!(remaining & BYTE_MASK)) {
            battler_index = TASK(PartyMember)->unk_03;
            if (!(battler_index & 0xF0)) {
                sound = EMI_SE_ID(SND_BANK_COMMON, 0x02);
                if (battler_index & 0x1) {
                    sound = EMI_SE_ID(SND_BANK_COMMON, 0x01);
                }
                SND_SEQueueSelection(sound);
            }
            TASK(PartyMember)->unk_10 = 8;
            TASK(PartyMember)->unk_14 = 8;
            TASK(PartyMember)->unk_20 = 8;
            TASK(PartyMember)->header.step += 1;
        }
    }
}

/* func_801F038C */
MATCH void BMagic_ShieldGemOrbit(void) {
    s16* angle;
    u16  phase;
    u8   count;

    Battle_ProjectRange();
    BMagic_SetXFixed(RANDOM_MASK(3) | 0x20);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(BMagic_ShieldDrawGem);
    TASK(PartyMember)->unk_10 += 4;
    TASK(PartyMember)->unk_09 += TASK(PartyMember)->unk_0C;
    phase                           = TASK(PartyMember)->param.unk_0B + 2;
    TASK(PartyMember)->param.unk_0B = phase;
    phase &= 0x1F;
    angle                          = &D_1F800004;
    *angle                         = phase << 7;
    g_ScratchPadHalves             = TASK(PartyMember)->timer * TASK(PartyMember)->unk_10 + 0xB0;
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin(phase << 7) * g_ScratchPadHalves) >> 3);
    TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle) * g_ScratchPadHalves) >> 3);
    count                          = TASK(PartyMember)->timer + 1;
    TASK(PartyMember)->timer       = count;
    if (count == 0x10) {
        g_BattleEffectBattler->param.unk_0B--;
        Actor_Clear();
    }
}

/* func_801F050C */
MATCH void BMagic_ShieldDrawGem(void) {
    POLY_G3* prim;
    u8*      start;
    s32      depths[16];
    long     depth;
    long     flag;
    s32      tpage;
    s32      i;
    s32      x;
    s32      y;
    s16      angle;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));
    start = g_GfxPrimCursor;
    for (i = TASK(PartyMember)->unk_09; i < TASK(PartyMember)->unk_09 + 32; i += 8) {
        g_ScratchPad.cells.halves[1] = 0x50;
        g_ScratchPad.cells.halves[0] = 0x30;
        g_ScratchPad.cells.halves[7] = (i - TASK(PartyMember)->unk_09) / 8;
        g_ScratchPad.cells.halves[4] = g_BMagicShieldGemUpperShades[TASK(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][0];
        g_ScratchPad.cells.halves[5] = g_BMagicShieldGemUpperShades[TASK(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][1];
        g_ScratchPad.cells.halves[6] = g_BMagicShieldGemUpperShades[TASK(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][2];
        g_ScratchPadVectors[0].vx    = 0;
        g_ScratchPadVectors[0].vy    = 0;
        g_ScratchPadVectors[0].vz    = g_ScratchPad.cells.halves[1];
        angle                        = i & 0x1F;
        g_ScratchPad.cells.halves[2] = angle << 7;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(angle << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz    = 0;
        angle                        = (i + 8) & 0x1F;
        g_ScratchPad.cells.halves[2] = angle << 7;
        g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(angle << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vz    = 0;
        prim                         = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        depths[(i - TASK(PartyMember)->unk_09) / 8] =
            RotAverage3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = TASK(PartyMember)->pos.x.fixed;
    y = TASK(PartyMember)->pos.y.fixed;
    func_800AF0F8(x, y, depths, start, 4, sizeof(POLY_G3), 0);
    start = g_GfxPrimCursor;
    for (i = TASK(PartyMember)->unk_09; i < TASK(PartyMember)->unk_09 + 32; i += 8) {
        g_ScratchPad.cells.halves[7] = (i - TASK(PartyMember)->unk_09) / 8;
        g_ScratchPad.cells.halves[4] = g_BMagicShieldGemLowerShades[TASK(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][0];
        g_ScratchPad.cells.halves[5] = g_BMagicShieldGemLowerShades[TASK(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][1];
        g_ScratchPad.cells.halves[6] = g_BMagicShieldGemLowerShades[TASK(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][2];
        g_ScratchPadVectors[0].vx    = 0;
        g_ScratchPadVectors[0].vy    = 0;
        g_ScratchPadVectors[0].vz    = -g_ScratchPad.cells.halves[1];
        angle                        = i & 0x1F;
        g_ScratchPad.cells.halves[2] = angle << 7;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(angle << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz    = 0;
        angle                        = (i + 8) & 0x1F;
        g_ScratchPad.cells.halves[2] = angle << 7;
        g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(angle << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vz    = 0;
        prim                         = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        depths[(i - TASK(PartyMember)->unk_09) / 8] =
            RotAverage3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = TASK(PartyMember)->pos.x.fixed;
    y = TASK(PartyMember)->pos.y.fixed;
    func_800AF0F8(x, y, depths, start, 4, sizeof(POLY_G3), 0);
}

MATCH void BMagic_SetXFixed(s32 radius) {
    POLY_G3* poly;
    s32      tpage;
    s32      i;

    g_ScratchPad.cells.halves[0] = radius;
    i                            = 0;
    do {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        poly = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        setXY3(poly, TASK(PartyMember)->screen_x.value, TASK(PartyMember)->screen_y.value, TASK(PartyMember)->screen_x.value + ((rsin(i << 9) * g_ScratchPad.cells.halves[0]) >> 12),
               TASK(PartyMember)->screen_y.value + ((rcos(i << 9) * g_ScratchPad.cells.halves[0]) >> 12),
               TASK(PartyMember)->screen_x.value + ((rsin((i + 1) << 9) * g_ScratchPad.cells.halves[0]) >> 12),
               TASK(PartyMember)->screen_y.value + ((rcos((i + 1) << 9) * g_ScratchPad.cells.halves[0]) >> 12));
        setRGB0(poly, 0x80, 0x80, 0x80);
        setRGB1(poly, 1, 1, 1);
        setRGB2(poly, 1, 1, 1);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
        i++;
    } while (i < 8);
}

/* func_801F0DC0 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F0E24 */
#include "overlays/bmagic/shared/Actor_Clear.h"
