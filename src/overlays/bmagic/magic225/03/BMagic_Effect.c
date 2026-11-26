#include "magic225_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC14 */
MATCH void BMagic_TemptationUpdate(void) {
    BMagicTemptationModes handlers = g_BMagicTemptationModes;
    PartyMember*          saved_task;
    PartyMember*          saved_battler;
    u8                    i;

    SYS_DISPATCH_BYTE(handlers.modes, TASK(PartyMember)->header.mode);

    BMAGIC_RUN_EFFECT_SLOTS(g_BMagicTemptationActors, BMagic_TemptationSlotUpdate);
}

/* func_801EED28 */
MATCH void BMagic_TemptationInit(void) {
    u16*         dst;
    u16*         src;
    u16*         row_dst;
    u16*         row_src;
    u16          i;
    u32          slot;
    PartyMember* work;

    BMAGIC_CLEAR_EFFECTS(i);
    Battle_CenterCamera();
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 24;
    TASK(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 101) & BYTE_MASK;
    work                               = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = work;
    TASK(PartyMember)->param.unk_0B += 1;
    i       = 0;
    row_dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    row_src = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    dst     = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src     = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (; i < AREA_PALETTE_COLORS; i++) {
        row_dst[i] = row_src[i];
        dst[i]     = src[i];
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 1));
}

/* func_801EEE8C */
MATCH void BMagic_TemptationSpawnActors(void) {
    u8           count;
    u8           i;
    u8           slot;
    PartyMember* work;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count == 0) {
        i = 0;
        do {
            SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                work                                   = TASK(PartyMember);
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = ((i & BYTE_MASK) * 4) + 8;
                BMAGIC_EFFECT_SLOTS[slot].target.party = work;
                TASK(PartyMember)->param.unk_0B += 1;
            }
            i++;
        } while (i < 16);
        TASK(PartyMember)->header.mode += 1;
    }
}

/* func_801EEF8C */
MATCH void BMagic_TemptationSpawnTargetEffects(void) {
    s32 i;
    s32 j;
    u8  slot;
    s32 battler;

    if (TASK(PartyMember)->param.unk_0B == 0) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            i = 0;
            do {
                if (!(Battle_SlotIsBlocked((i + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK) & BYTE_MASK)) {
                    j       = 0;
                    battler = i + BATTLE_PARTY_CHARACTERS_COUNT;
                    do {
                        if (Battle_CanTarget(D_800B6BF0[j & BYTE_MASK], battler & BYTE_MASK) & BYTE_MASK) {
                            slot = Battle_AllocEffect(1, 2);
                            if (slot != 0xFF) {
                                g_BattleEffects[slot].target.party = TASK(PartyMember);
                                g_BattleEffects[slot].unk_04       = j + 4;
                                g_BattleEffects[slot].arg.unk_09   = (j & BYTE_MASK) * 5 + 1;
                                g_BattleEffects[slot].unk_0B       = battler;
                                g_BattleEffects[slot].unk_0A       = (j & BYTE_MASK) * 12;
                                TASK(PartyMember)->param.unk_0B += 1;
                            }
                        } else {
                            slot = Battle_AllocEffect(1, 2);
                            if (slot != 0xFF) {
                                g_BattleEffects[slot].target.party = TASK(PartyMember);
                                g_BattleEffects[slot].unk_04       = 8;
                                g_BattleEffects[slot].arg.unk_09   = (j & BYTE_MASK) * 5 + 1;
                                g_BattleEffects[slot].unk_0B       = battler;
                                g_BattleEffects[slot].unk_0A       = (j & BYTE_MASK) * 12;
                                TASK(PartyMember)->param.unk_0B += 1;
                            }
                        }
                        j++;
                    } while ((u32)(j & BYTE_MASK) < 3);
                }
                i++;
            } while ((u32)(i & BYTE_MASK) < 8);
        } else {
            i = 0;
            do {
                if (!(Battle_SlotIsBlocked(i & BYTE_MASK) & BYTE_MASK)) {
                    j = 0;
                    do {
                        if (Battle_CanTarget(D_800B6BF0[j & BYTE_MASK], i & BYTE_MASK) & BYTE_MASK) {
                            slot = Battle_AllocEffect(1, 2);
                            if (slot != 0xFF) {
                                g_BattleEffects[slot].target.party = TASK(PartyMember);
                                g_BattleEffects[slot].unk_04       = j + 4;
                                g_BattleEffects[slot].arg.unk_09   = (j & BYTE_MASK) * 5 + 1;
                                g_BattleEffects[slot].unk_0B       = i;
                                g_BattleEffects[slot].unk_0A       = (j & BYTE_MASK) * 12;
                                TASK(PartyMember)->param.unk_0B += 1;
                            }
                        } else {
                            slot = Battle_AllocEffect(1, 2);
                            if (slot != 0xFF) {
                                g_BattleEffects[slot].target.party = TASK(PartyMember);
                                g_BattleEffects[slot].unk_04       = 8;
                                g_BattleEffects[slot].arg.unk_09   = (j & BYTE_MASK) * 5 + 1;
                                g_BattleEffects[slot].unk_0B       = i;
                                g_BattleEffects[slot].unk_0A       = (j & BYTE_MASK) * 12;
                                TASK(PartyMember)->param.unk_0B += 1;
                            }
                        }
                        j++;
                    } while ((u32)(j & BYTE_MASK) < 3);
                }
                i++;
            } while ((u32)(i & BYTE_MASK) < BATTLE_PARTY_CHARACTERS_COUNT);
        }
        TASK(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF2D8 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EF31C */
MATCH void BMagic_TemptationFlashUpdate(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(g_BMagicTemptationFlashSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        BMagic_TemptationDrawFlash();
        BMagic_TemptationDrawGlow(0x30, 0x10, 0x52, 0);
        BMagic_TemptationDrawGlow(0x12C, 0, 0x80, 1);
        BMagic_TemptationDrawGlow(0x40, 0xF0, 0x6C, 2);
        BMagic_TemptationDrawGlow(0x140, 0xF0, 0x5C, 3);
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

/* func_801EF404 */
MATCH void BMagic_TemptationFlashStart(void) {
    s32 i;

    BMAGIC_MARK_SELECTED_SIDE(2);
    if (g_Battle.encounter == 55) {
        TASK(PartyMember)->unk_29 = 7;
    } else {
        TASK(PartyMember)->unk_29 = 3;
    }
    TASK(PartyMember)->param.unk_0B = 1;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->timer        = 0;
    TASK(PartyMember)->header.step += 1;
}

/* func_801EF578 */
MATCH void BMagic_TemptationFlashRise(void) {
    u8 timer_next;

    timer_next               = TASK(PartyMember)->timer + 2;
    TASK(PartyMember)->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 0x10) {
        TASK(PartyMember)->param.unk_0B = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

/* func_801EF628 */
MATCH void BMagic_TemptationFlashWait(void) {
    if (g_BattleEffectBattler->param.unk_0B < 2U) {
        TASK(PartyMember)->param.unk_0B = 1;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EF67C */
MATCH void BMagic_TemptationFlashEnd(void) {
    s32 i;

    if (TASK(PartyMember)->unk_09 != 0) {
        TASK(PartyMember)->unk_09 -= 2;
    }
    if (--TASK(PartyMember)->timer == 0) {
        BMAGIC_MARK_SELECTED_SIDE(4);
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

/* func_801EF7D4 */
MATCH void BMagic_TemptationDrawGlow(s32 x, s32 y, s32 radius, s32 color) {
    POLY_G3* prim;
    POLY_G4* quad;
    s32      tpage;
    s32      i;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE((u8)TASK(PartyMember)->unk_29, tpage);
    D_1F800000_WORD[0] = (s16)radius;
    D_1F800000_WORD[1] = (s16)radius + (s16)radius / 2;
    D_1F800000_WORD[3] = TASK(PartyMember)->unk_09 * 4;
    D_1F800000_WORD[4] = g_BMagicTemptationGlowColors[color & BYTE_MASK][0] * TASK(PartyMember)->unk_09;
    D_1F800000_WORD[5] = g_BMagicTemptationGlowColors[color & BYTE_MASK][1] * TASK(PartyMember)->unk_09;
    D_1F800000_WORD[6] = g_BMagicTemptationGlowColors[color & BYTE_MASK][2] * TASK(PartyMember)->unk_09;
    for (i = 0; (u32)(i & BYTE_MASK) < 32; i++) {
        prim = GFX_BeginPolyG3(1);
        setXY3(prim, x, y, x + FIXED_MUL(rsin((i & BYTE_MASK) << 7), D_1F800000_WORD[0]), y + FIXED_MUL(rcos((i & BYTE_MASK) << 7), D_1F800000_WORD[0]),
               x + FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 7), D_1F800000_WORD[0]), y + FIXED_MUL(rcos(((i & BYTE_MASK) + 1) << 7), D_1F800000_WORD[0]));
        setRGB0(prim, D_1F800000_WORD[4], D_1F800000_WORD[5], D_1F800000_WORD[6]);
        setRGB1(prim, D_1F800000_WORD[4], D_1F800000_WORD[5], D_1F800000_WORD[6]);
        setRGB2(prim, D_1F800000_WORD[4], D_1F800000_WORD[5], D_1F800000_WORD[6]);
        GFX_AddPrim((u8)TASK(PartyMember)->unk_29, sizeof(POLY_G3));
    }
    for (i = 0; (u32)(i & BYTE_MASK) < 32; i++) {
        quad = GFX_BeginPolyG4(1);
        setXY4(quad, x + FIXED_MUL(rsin((i & BYTE_MASK) << 7), D_1F800000_WORD[1]), y + FIXED_MUL(rcos((i & BYTE_MASK) << 7), D_1F800000_WORD[1]),
               x + FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 7), D_1F800000_WORD[1]), y + FIXED_MUL(rcos(((i & BYTE_MASK) + 1) << 7), D_1F800000_WORD[1]),
               x + FIXED_MUL(rsin((i & BYTE_MASK) << 7), D_1F800000_WORD[0]), y + FIXED_MUL(rcos((i & BYTE_MASK) << 7), D_1F800000_WORD[0]),
               x + FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 7), D_1F800000_WORD[0]), y + FIXED_MUL(rcos(((i & BYTE_MASK) + 1) << 7), D_1F800000_WORD[0]));
        setRGB0(quad, 1, 1, 1);
        setRGB1(quad, 1, 1, 1);
        setRGB2(quad, D_1F800000_WORD[4], D_1F800000_WORD[5], D_1F800000_WORD[6]);
        setRGB3(quad, D_1F800000_WORD[4], D_1F800000_WORD[5], D_1F800000_WORD[6]);
        GFX_AddPrim((u8)TASK(PartyMember)->unk_29, sizeof(POLY_G4));
    }
}

/* func_801EFCA0 */
MATCH void BMagic_TemptationDrawFlash(void) {
    POLY_F4*      prim;
    s32           tpage;
    volatile s32* shade;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TASK(PartyMember)->param.unk_0B, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE((u8)TASK(PartyMember)->unk_29, tpage);
    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    SetSemiTrans(prim, TASK(PartyMember)->param.unk_0B);
    shade  = &D_1F80000C;
    *shade = TASK(PartyMember)->timer * 15 + 15;
    setXYWH(prim, 0, 0, 319, 239);
    setRGB0(prim, *shade, *shade, *shade);
    GFX_AddPrim((u8)TASK(PartyMember)->unk_29, sizeof(POLY_F4));
}

/* func_801EFE0C */
MATCH void BMagic_TemptationSlotUpdate(void) {
    SYS_DISPATCH_TASK(g_BMagicTemptationActorSteps, 1, g_Task);
}

/* func_801EFE50 */
MATCH void BMagic_TemptationActorUpdate(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(g_BMagicTemptationActorSteps + 1, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

/* func_801EFEE8 */
MATCH void BMagic_TemptationActorPlace(void) {
    PartyMember* caster;
    PartyMember* work;
    PartyMember* battler;
    PartyMember* task;
    u8           timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        caster                    = g_BattleActiveActor;
        TASK(PartyMember)->facing = caster->facing;
        TASK(PartyMember)->unk_0C = 0x10000;
        TASK(PartyMember)->unk_10 = 0;
        Effect_RotatePosition(g_Task);
        work                      = TASK(PartyMember);
        battler                   = g_BattleEffectBattler;
        work->pos.x.fixed         = caster->pos.x.fixed + work->unk_0C;
        work->pos.y.fixed         = caster->pos.y.fixed + work->unk_10;
        work->pos.z.fixed         = caster->pos.z.fixed + TO_COORD(256);
        TASK(PartyMember)->unk_14 = ratan2(battler->pos.x.fixed - work->pos.x.fixed, battler->pos.y.fixed - work->pos.y.fixed);
        if (TASK(PartyMember)->param.unk_0B & 1) {
            TASK(PartyMember)->unk_14 += rand() & 0xFF;
        } else {
            TASK(PartyMember)->unk_14 -= rand() & 0xFF;
        }
        TASK(PartyMember)->unk_25       = 0x1D;
        TASK(PartyMember)->unk_26       = 0x80;
        TASK(PartyMember)->scale.x      = 0x10000;
        TASK(PartyMember)->scale.y      = 0x10000;
        TASK(PartyMember)->unk_48       = 2;
        TASK(PartyMember)->unk_27       = 2;
        TASK(PartyMember)->unk_28       = 1;
        TASK(PartyMember)->unk_24       = 0;
        TASK(PartyMember)->unk_5C       = 0;
        TASK(PartyMember)->unk_5D       = 0;
        TASK(PartyMember)->unk_5E       = 0;
        TASK(PartyMember)->unk_5F       = 0;
        TASK(PartyMember)->unk_2A       = TASK(PartyMember)->facing & 1;
        TASK(PartyMember)->unk_29       = 2;
        TASK(PartyMember)->unk_2C.value = 0;
        TASK(PartyMember)->unk_2B       = 1;
        Script_Select(0);
        task         = TASK(PartyMember);
        task->unk_09 = 16;
        task->unk_0C = 12;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F0140 */
MATCH void BMagic_TemptationActorFly(void) {
    s32 value;

    Script_AnimStepLoop();
    TASK(PartyMember)->scale.x += 0x800;
    TASK(PartyMember)->scale.y += 0x800;
    TASK(PartyMember)->pos.x.fixed += rsin(TASK(PartyMember)->unk_14) * TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed += rcos(TASK(PartyMember)->unk_14) * TASK(PartyMember)->unk_0C;
    if (g_FrameCount & 0x1) {
        value = TASK(PartyMember)->unk_0C;
        if (value == 4) {
            TASK(PartyMember)->header.step += 1;
            return;
        }
        TASK(PartyMember)->unk_0C = value - 1;
    }
}

/* func_801F021C */
MATCH void BMagic_TemptationActorEnd(void) {
    Script_AnimStepLoop();
    TASK(PartyMember)->scale.x += 0x800;
    TASK(PartyMember)->scale.y += 0x800;
    TASK(PartyMember)->pos.x.fixed += rsin(TASK(PartyMember)->unk_14) << 2;
    TASK(PartyMember)->pos.y.fixed += rcos(TASK(PartyMember)->unk_14) << 2;
    if (--TASK(PartyMember)->unk_09 == 0) {
        g_BattleEffectBattler->param.unk_0B--;
        Actor_Clear();
    }
}

/* func_801F02D4 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F0338 */
#include "overlays/bmagic/shared/Actor_Clear.h"
