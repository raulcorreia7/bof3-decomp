#include "magic093_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_RunSlotsWithSetup.h"

MATCH void func_801EED04(void) {
    PartyMember* owner;
    u16*         dst;
    u16*         src;
    u32          i;
    u32          slot;

    BMAGIC_CLEAR_EFFECTS(i);
    func_801F0670();
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode++;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            if (!Battle_SlotIsBlocked((u8)(i + 3))) {
                slot                               = Battle_AllocEffect(1, 77) & BYTE_MASK;
                owner                              = SELF(PartyMember);
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_03       = i;
                g_BattleEffects[slot].arg.unk_09   = 16;
                g_BattleEffects[slot].target.party = owner;
                SELF(PartyMember)->unk_09++;
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (!Battle_SlotIsBlocked((u8)i)) {
                slot                               = Battle_AllocEffect(1, 77) & BYTE_MASK;
                owner                              = SELF(PartyMember);
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_03       = i;
                g_BattleEffects[slot].arg.unk_09   = 16;
                g_BattleEffects[slot].target.party = owner;
                SELF(PartyMember)->unk_09++;
            }
        }
    }
    for (i = 0; i < 8; i++) {
        slot                                   = BMagic_AllocEffect() & BYTE_MASK;
        owner                                  = SELF(PartyMember);
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[slot].unk_04       = i;
        BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
        SELF(PartyMember)->param.unk_0B++;
    }
    for (i = 0; i < 16; i++) {
        slot                                   = BMagic_AllocEffect() & BYTE_MASK;
        owner                                  = SELF(PartyMember);
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 1;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 8 + 24;
        BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
        SELF(PartyMember)->param.unk_0B++;
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < AREA_PALETTE_COLORS; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
}

/* Starts the effect once bytes 0x09 and 0x0B of the work record are both zero. */
MATCH void func_801EF02C(void) {
    u16* flags;

    if ((PARTY_MEMBER_WORD_08(SELF(PartyMember)) & 0xFF00FF00u) == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        Effect_Reset();
    }
}

/* func_801EF080 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0C4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 2, g_Self);
}

MATCH void func_801EF108(void) {
    void* battler;
    u8    count;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            battler = &g_BattleEnemyBattlers[SELF(PartyMember)->unk_03];
            GFX_PaletteFreeFadeTarget(battler);
            GFX_PaletteAllocFade(battler, -8, -8, -8, 1);
            Battle_ApplyDamageFlags((SELF(PartyMember)->unk_03 + 3) & BYTE_MASK, 0x10);
        } else {
            battler = &g_Game.members[SELF(PartyMember)->unk_03];
            GFX_PaletteFreeFadeTarget(battler);
            GFX_PaletteAllocFade(battler, -8, -8, -8, 1);
            Battle_ApplyDamageFlags(SELF(PartyMember)->unk_03, 0x10);
        }
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF264(void) {
    if (g_BattleEffectBattler->param.unk_0B < 8U) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            Battle_MarkDamaged((SELF(PartyMember)->unk_03 + 3) & BYTE_MASK);
            GFX_PaletteFreeFadeTarget(&g_BattleEnemyBattlers[SELF(PartyMember)->unk_03]);
            Battle_FadePoisonedBattler((SELF(PartyMember)->unk_03 + 3) & BYTE_MASK);
        } else {
            Battle_MarkDamaged(SELF(PartyMember)->unk_03);
            GFX_PaletteFreeFadeTarget((EnemyBattler*)&g_Game.members[SELF(PartyMember)->unk_03]);
            Battle_FadePoisonedBattler(SELF(PartyMember)->unk_03);
        }
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF3A4(void) {
    BATTLE_ACTIVE_WORK->unk_09--;
    Effect_Reset();
}

MATCH void func_801EF3D8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 4), 1, g_Self);
}

MATCH void func_801EF41C(void) {
    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 6), SELF(PartyMember)->header.step);
    SELF(PartyMember)->param.unk_0B += 1;
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF85C();
        func_801EFAE8();
        PopMatrix();
    }
}

MATCH void func_801EF4C8(void) {
    s16 angle;
    s16 phase;
    u8  mask;

    SELF(PartyMember)->timer            = (rand() & 3) << 4;
    angle                               = 0xC0 - SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[0]        = angle;
    mask                                = SELF(PartyMember)->unk_04 & 7;
    D_1F80000A                          = mask << 9;
    LOW(SELF(PartyMember)->pos.x.fixed) = g_BattleEffectBattler->pos.x.fixed + ((rsin(mask << 9) * g_ScratchPad.cells.halves[0]) >> 3);
    phase                               = D_1F80000A;
    SELF(PartyMember)->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed + ((rcos(phase) * g_ScratchPad.cells.halves[0]) >> 3);
    SELF(PartyMember)->pos.z.fixed      = g_BattleEffectBattler->pos.z.fixed;
    SELF(PartyMember)->param.unk_0B     = rand();
    SELF(PartyMember)->unk_09           = 0;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF600(void) {
    s16 angle;
    s16 phase;
    u8  mask;
    u8  count;

    angle                               = SELF(PartyMember)->unk_09 * 8 - (SELF(PartyMember)->timer - 0xC0);
    g_ScratchPad.cells.halves[0]        = angle;
    mask                                = SELF(PartyMember)->unk_04 & 7;
    D_1F80000A                          = mask << 9;
    LOW(SELF(PartyMember)->pos.x.fixed) = g_BattleEffectBattler->pos.x.fixed + ((rsin(mask << 9) * g_ScratchPad.cells.halves[0]) >> 3);
    phase                               = D_1F80000A;
    SELF(PartyMember)->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed + ((rcos(phase) * g_ScratchPad.cells.halves[0]) >> 3);
    count                               = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09           = count;
    if ((count & BYTE_MASK) == 0x10) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF710(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 8) {
        work              = SELF(PartyMember);
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EF750(void) {
    PartyMember* work;

    work         = SELF(PartyMember);
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 0) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

MATCH void func_801EF85C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      red;
    s32      core;
    s32      green;
    s32      blue;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[0] = ((rsin((SELF(PartyMember)->param.unk_0B & 0x1F) << 7) * 16) >> 12) + 0x100;
    red                          = SELF(PartyMember)->unk_09 * 10;
    core                         = SELF(PartyMember)->unk_09 * 9;
    blue                         = SELF(PartyMember)->unk_09 * 2;
    green                        = SELF(PartyMember)->unk_09 * 4;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        GFX_STEP_TRIANGLE_FAN(i << 8, g_ScratchPad.cells.halves[0]);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, red, core, blue);
        setRGB1(prim, red, green, blue);
        setRGB2(prim, red, green, blue);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

MATCH void func_801EFAE8(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32      i;
    u8       red;
    u8       green;
    u8       blue;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[0] = ((rsin((SELF(PartyMember)->param.unk_0B & 0x1F) << 7) * 16) >> 12) + 0x100;
    g_ScratchPad.cells.halves[1] = ((rsin((SELF(PartyMember)->param.unk_0B & 0x1F) << 7) * 16) >> 12) + 0x180;
    red                          = SELF(PartyMember)->unk_09 * 10;
    green                        = SELF(PartyMember)->unk_09 * 4;
    blue                         = SELF(PartyMember)->unk_09 * 2;
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[0]);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, red, green, blue);
        setRGB3(prim, red, green, blue);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801EFE5C(void) {
    SYS_DISPATCH_BYTE(D_801F08C4, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        func_801F01F0();
    }
}

MATCH void func_801EFEDC(void) {
    s16* radius;
    u8   count;
    u8   phase;
    u8   pick;
    u8   flags;
    u32  id;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        radius                         = &g_ScratchPad.cells.halves[0];
        *radius                        = 0x100;
        phase                          = rand() & 7;
        g_ScratchPad.cells.halves[5]   = phase << 9;
        SELF(PartyMember)->pos.x.fixed += (rsin(phase << 9) * *radius) >> 3;
        SELF(PartyMember)->pos.y.fixed += (rcos(g_ScratchPad.cells.halves[5]) * *radius) >> 3;
        flags = SELF(PartyMember)->param.unk_0B;
        if (flags & 1) {
            pick = (flags >> 1) % 3;
            switch (pick) {
                case 0:
                    id = EMI_SE_ID(SND_BANK_COMMON, 0x01);
                    break;
                case 1:
                    id = EMI_SE_ID(SND_BANK_COMMON, 0x02);
                    break;
                case 2:
                default:
                    id = EMI_SE_ID(SND_BANK_COMMON, 0x03);
                    break;
            }
            SND_SEQueueSelection(id);
        }
        SELF(PartyMember)->param.unk_0B = 0x10;
        SELF(PartyMember)->unk_09       = 0;
        SELF(PartyMember)->timer        = 0x40;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F00A0(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(unk_09, 32, 192);
}

MATCH void func_801F00F0(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    work->unk_09 += 2;
    work = SELF(PartyMember);
    work->timer--;
    if (work->timer == 48) {
        work = SELF(PartyMember);
        work->header.step++;
    }
}

MATCH void func_801F015C(void) {
    u8 ticks;

    SELF(PartyMember)->unk_09 += 1;
    SELF(PartyMember)->timer -= 1;
    ticks                           = SELF(PartyMember)->param.unk_0B - 1;
    SELF(PartyMember)->param.unk_0B = ticks;
    if (!(ticks & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

MATCH void func_801F01F0(void) {
    POLY_GT4* prim;
    s32       tpage;
    u8        shade;

    shade                        = SELF(PartyMember)->param.unk_0B * 8;
    g_ScratchPad.cells.halves[6] = SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[7] = SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->screen_y.value;
    tpage                        = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));

    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, g_ScratchPad.cells.halves[3] - g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[3] + g_ScratchPad.cells.halves[7],
           g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[3] - g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[4],
           g_ScratchPad.cells.halves[3] + g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[4]);
    GFX_SET_RGB_ALL(prim, shade, shade, shade);
    prim->tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUVWH(prim, 0x40, 0x40, 128, 191);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 0, sizeof(POLY_GT4));

    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, g_ScratchPad.cells.halves[3] - g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6] - 16,
           g_ScratchPad.cells.halves[3] + g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6] - 16, g_ScratchPad.cells.halves[3] - g_ScratchPad.cells.halves[7],
           g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[3] + g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[4] - g_ScratchPad.cells.halves[6]);
    setRGB0(prim, 1, 1, 1);
    setRGB1(prim, 1, 1, 1);
    setRGB2(prim, shade, shade, shade);
    setRGB3(prim, shade, shade, shade);
    prim->tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUVWH(prim, 0x40, 0x30, 128, 16);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 0, sizeof(POLY_GT4));
}

/* func_801F05BC */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F0620 */
#include "overlays/bmagic/shared/Actor_Clear.h"

MATCH void func_801F0670(void) {
    s32 count;
    s32 x;
    s32 y;
    s32 z;
    u8  i;

    count = 0;
    z     = 0;
    y     = 0;
    x     = 0;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            if (!Battle_SlotIsBlocked((u8)(i + 3))) {
                count++;
                x += (g_BattleEnemyBattlers[i].pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
                y += (g_BattleEnemyBattlers[i].pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
                z += COORD_INT(g_BattleEnemyBattlers[i].pos.z);
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (!Battle_SlotIsBlocked(i)) {
                count++;
                x += (g_Game.members[i].pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
                y += (g_Game.members[i].pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
                z += COORD_INT(g_Game.members[i].pos.z);
            }
        }
    }
    SELF(PartyMember)->pos.x.fixed      = (x / count + AREA_CELL_ORIGIN) << 9;
    SELF(PartyMember)->pos.y.fixed      = (y / count + AREA_CELL_ORIGIN) << 9;
    COORD_INT(SELF(PartyMember)->pos.z) = z / count;
}
