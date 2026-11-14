#include "magic225_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    Magic225Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F03BC[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F03BC[i];
            g_BattleEffectBattler = D_801F03BC[i].target.party;
            func_801EFE0C();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

/* Clears the effect slots, centers the camera, claims the first effect slot and reloads palette rows 2 and 26 of
 * the work copy. */
MATCH void func_801EED28(void) {
    u16*         dst;
    u16*         src;
    u16*         row_dst;
    u16*         row_src;
    u16          i;
    u32          slot;
    PartyMember* work;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    Battle_CenterCamera();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 24;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 101) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = work;
    g_Task->param.unk_0B += 1;
    i       = 0;
    row_dst = MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW);
    row_src = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    dst     = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src     = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 256; i++) {
        row_dst[i] = row_src[i];
        dst[i]     = src[i];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 1));
}

MATCH void func_801EEE8C(void) {
    u8           count;
    u8           i;
    u8           slot;
    PartyMember* work;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        i = 0;
        do {
            SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                work                                   = g_Task;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = ((i & BYTE_MASK) * 4) + 8;
                BMAGIC_EFFECT_SLOTS[slot].target.party = work;
                g_Task->param.unk_0B += 1;
            }
            i++;
        } while (i < 16);
        g_Task->header.mode += 1;
    }
}

/* Spawn three effects on each unblocked battler of the selected side: kind j + 4 where
 * func_800AED5C accepts the battler for selector j, kind 8 otherwise. */
MATCH void func_801EEF8C(void) {
    s32 i;
    s32 j;
    u8  slot;
    s32 battler;

    if (g_Task->param.unk_0B == 0) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            i = 0;
            do {
                if (!(Battle_SlotIsBlocked((i + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK) & BYTE_MASK)) {
                    j       = 0;
                    battler = i + BATTLE_PARTY_CHARACTERS_COUNT;
                    do {
                        if (func_800AED5C(D_800B6BF0[j & BYTE_MASK], battler & BYTE_MASK) & BYTE_MASK) {
                            slot = Battle_AllocEffect(1, 2);
                            if (slot != 0xFF) {
                                g_BattleEffects[slot].target.party = g_Task;
                                g_BattleEffects[slot].unk_04       = j + 4;
                                g_BattleEffects[slot].arg.unk_09   = (j & BYTE_MASK) * 5 + 1;
                                g_BattleEffects[slot].unk_0B       = battler;
                                g_BattleEffects[slot].unk_0A       = (j & BYTE_MASK) * 12;
                                g_Task->param.unk_0B += 1;
                            }
                        } else {
                            slot = Battle_AllocEffect(1, 2);
                            if (slot != 0xFF) {
                                g_BattleEffects[slot].target.party = g_Task;
                                g_BattleEffects[slot].unk_04       = 8;
                                g_BattleEffects[slot].arg.unk_09   = (j & BYTE_MASK) * 5 + 1;
                                g_BattleEffects[slot].unk_0B       = battler;
                                g_BattleEffects[slot].unk_0A       = (j & BYTE_MASK) * 12;
                                g_Task->param.unk_0B += 1;
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
                        if (func_800AED5C(D_800B6BF0[j & BYTE_MASK], i & BYTE_MASK) & BYTE_MASK) {
                            slot = Battle_AllocEffect(1, 2);
                            if (slot != 0xFF) {
                                g_BattleEffects[slot].target.party = g_Task;
                                g_BattleEffects[slot].unk_04       = j + 4;
                                g_BattleEffects[slot].arg.unk_09   = (j & BYTE_MASK) * 5 + 1;
                                g_BattleEffects[slot].unk_0B       = i;
                                g_BattleEffects[slot].unk_0A       = (j & BYTE_MASK) * 12;
                                g_Task->param.unk_0B += 1;
                            }
                        } else {
                            slot = Battle_AllocEffect(1, 2);
                            if (slot != 0xFF) {
                                g_BattleEffects[slot].target.party = g_Task;
                                g_BattleEffects[slot].unk_04       = 8;
                                g_BattleEffects[slot].arg.unk_09   = (j & BYTE_MASK) * 5 + 1;
                                g_BattleEffects[slot].unk_0B       = i;
                                g_BattleEffects[slot].unk_0A       = (j & BYTE_MASK) * 12;
                                g_Task->param.unk_0B += 1;
                            }
                        }
                        j++;
                    } while ((u32)(j & BYTE_MASK) < 3);
                }
                i++;
            } while ((u32)(i & BYTE_MASK) < BATTLE_PARTY_CHARACTERS_COUNT);
        }
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF2D8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF31C(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0398, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EFCA0();
        func_801EF7D4(0x30, 0x10, 0x52, 0);
        func_801EF7D4(0x12C, 0, 0x80, 1);
        func_801EF7D4(0x40, 0xF0, 0x6C, 2);
        func_801EF7D4(0x140, 0xF0, 0x5C, 3);
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF404(void) {
    s32 i;

    BMAGIC_MARK_SELECTED_SIDE(2);
    if (g_Battle.encounter == 55) {
        g_Task->unk_29 = 7;
    } else {
        g_Task->unk_29 = 3;
    }
    g_Task->param.unk_0B = 1;
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF578(void) {
    u8 timer_next;

    timer_next    = g_Task->timer + 2;
    g_Task->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 0x10) {
        g_Task->param.unk_0B = 0;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

MATCH void func_801EF628(void) {
    if (g_BattleEffectBattler->param.unk_0B < 2U) {
        g_Task->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF67C(void) {
    s32 i;

    if (g_Task->unk_09 != 0) {
        g_Task->unk_09 -= 2;
    }
    if (--g_Task->timer == 0) {
        BMAGIC_MARK_SELECTED_SIDE(4);
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

/* Draw one corner glow of magic225 at the screen point (x, y): a disc of 32 wedges in the
 * colour row, then a ring of 32 quads fading out to half the radius again. */
MATCH void func_801EF7D4(s32 x, s32 y, s32 radius, s32 color) {
    POLY_G3* prim;
    POLY_G4* quad;
    s32      tpage;
    s32      i;

    if (GetGraphType() == 1) {
        tpage = 0x125;
    } else if (GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim((u8)g_Task->unk_29, sizeof(DR_MODE));
    D_1F800000_WORD[0] = (s16)radius;
    D_1F800000_WORD[1] = (s16)radius + (s16)radius / 2;
    D_1F800000_WORD[3] = g_Task->unk_09 * 4;
    D_1F800000_WORD[4] = D_801F038C[color & BYTE_MASK][0] * g_Task->unk_09;
    D_1F800000_WORD[5] = D_801F038C[color & BYTE_MASK][1] * g_Task->unk_09;
    D_1F800000_WORD[6] = D_801F038C[color & BYTE_MASK][2] * g_Task->unk_09;
    for (i = 0; (u32)(i & BYTE_MASK) < 32; i++) {
        prim = GFX_BeginPolyG3(1);
        setXY3(prim, x, y, x + FIXED_MUL(rsin((i & BYTE_MASK) << 7), D_1F800000_WORD[0]), y + FIXED_MUL(rcos((i & BYTE_MASK) << 7), D_1F800000_WORD[0]),
               x + FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 7), D_1F800000_WORD[0]), y + FIXED_MUL(rcos(((i & BYTE_MASK) + 1) << 7), D_1F800000_WORD[0]));
        setRGB0(prim, D_1F800000_WORD[4], D_1F800000_WORD[5], D_1F800000_WORD[6]);
        setRGB1(prim, D_1F800000_WORD[4], D_1F800000_WORD[5], D_1F800000_WORD[6]);
        setRGB2(prim, D_1F800000_WORD[4], D_1F800000_WORD[5], D_1F800000_WORD[6]);
        GFX_AddPrim((u8)g_Task->unk_29, sizeof(POLY_G3));
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
        GFX_AddPrim((u8)g_Task->unk_29, sizeof(POLY_G4));
    }
}

MATCH void func_801EFCA0(void) {
    POLY_F4*      prim;
    s32           tpage;
    volatile s32* shade;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = ((g_Task->param.unk_0B & 3) << 7) | 0x25;
    } else {
        tpage = ((g_Task->param.unk_0B & 3) << 5) | 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim((u8)g_Task->unk_29, sizeof(DR_MODE));
    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    SetSemiTrans(prim, g_Task->param.unk_0B);
    shade  = &D_1F80000C;
    *shade = g_Task->timer * 15 + 15;
    setXYWH(prim, 0, 0, 319, 239);
    setRGB0(prim, *shade, *shade, *shade);
    GFX_AddPrim((u8)g_Task->unk_29, sizeof(POLY_F4));
}

MATCH void func_801EFE0C(void) {
    SYS_DISPATCH_TASK(D_801F03AC, 1, g_Task);
}

MATCH void func_801EFE50(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F03AC + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EFEE8(void) {
    PartyMember* caster;
    PartyMember* work;
    PartyMember* battler;
    PartyMember* task;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        caster         = D_8014637C;
        g_Task->facing = caster->facing;
        g_Task->unk_0C = 0x10000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        work              = g_Task;
        battler           = g_BattleEffectBattler;
        work->pos.x.fixed = caster->pos.x.fixed + work->unk_0C;
        work->pos.y.fixed = caster->pos.y.fixed + work->unk_10;
        work->pos.z.fixed = caster->pos.z.fixed + TO_COORD(256);
        g_Task->unk_14    = ratan2(battler->pos.x.fixed - work->pos.x.fixed, battler->pos.y.fixed - work->pos.y.fixed);
        if (g_Task->param.unk_0B & 1) {
            g_Task->unk_14 += rand() & 0xFF;
        } else {
            g_Task->unk_14 -= rand() & 0xFF;
        }
        g_Task->unk_25      = 0x1D;
        g_Task->unk_26      = 0x80;
        g_Task->scale.x     = 0x10000;
        g_Task->scale.y     = 0x10000;
        g_Task->unk_48      = 2;
        g_Task->unk_27      = 2;
        g_Task->unk_28      = 1;
        g_Task->unk_24      = 0;
        g_Task->unk_5C      = 0;
        g_Task->unk_5D      = 0;
        g_Task->unk_5E      = 0;
        g_Task->unk_5F      = 0;
        g_Task->unk_2A      = g_Task->facing & 1;
        g_Task->unk_29      = 2;
        g_Task->unk_2C.half = 0;
        g_Task->unk_2B      = 1;
        Actor_SelectScript(0);
        task         = g_Task;
        task->unk_09 = 16;
        task->unk_0C = 12;
        g_Task->header.step += 1;
    }
}

/* func_801F0140 */
MATCH void BMagic_GetScaleX(void) {
    s32 value;

    Actor_StepAnimLoop();
    g_Task->scale.x += 0x800;
    g_Task->scale.y += 0x800;
    g_Task->pos.x.fixed += rsin(g_Task->unk_14) * g_Task->unk_0C;
    g_Task->pos.y.fixed += rcos(g_Task->unk_14) * g_Task->unk_0C;
    if (g_FrameCount & 0x1) {
        value = g_Task->unk_0C;
        if (value == 4) {
            g_Task->header.step += 1;
            return;
        }
        g_Task->unk_0C = value - 1;
    }
}

/* func_801F021C */
MATCH void BMagic_SetScaleX(void) {
    Actor_StepAnimLoop();
    g_Task->scale.x += 0x800;
    g_Task->scale.y += 0x800;
    g_Task->pos.x.fixed += rsin(g_Task->unk_14) << 2;
    g_Task->pos.y.fixed += rcos(g_Task->unk_14) << 2;
    if (--g_Task->unk_09 == 0) {
        g_BattleEffectBattler->param.unk_0B--;
        Actor_Clear();
    }
}

/* func_801F02D4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0338 */
#include "overlays/bmagic/Actor_Clear.h"
