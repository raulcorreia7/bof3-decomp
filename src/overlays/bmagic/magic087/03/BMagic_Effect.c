#include "magic087_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_RunSlotsWithSetup.h"

/* Clears the effect slot table and spawns one effect 0x27 at each selectable battler, the enemies
 * (raised by the enemy type's height) when the target selector holds 0x40 and the party otherwise,
 * each starting 8 frames after the one before by slot; then sets STP on colours 1 to 15 of work
 * palette row 26 from arena row 0. */
MATCH void func_801EED04(void) {
    u8 i;
    u8 slot;
    u8 battler;

    TASK(PartyMember)->param.unk_0B = 0;
    BMAGIC_CLEAR_EFFECTS(i);
    if (g_Battle.target_selector & 0x40) {
        for (i = 0; i < 8; i++) {
            battler = i + BATTLE_PARTY_CHARACTERS_COUNT;
            if (!Battle_SlotIsBlocked(battler)) {
                slot                               = Battle_AllocEffect(1, 39);
                g_BattleEffects[slot].target.party = TASK(PartyMember);
                g_BattleEffects[slot].unk_04       = TASK(PartyMember)->param.unk_0B;
                g_BattleEffects[slot].arg.unk_09   = i * 8 + 1;
                g_BattleEffects[slot].pos.x.fixed  = g_BattleEnemyBattlers[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_BattleEnemyBattlers[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_BattleEnemyBattlers[i].pos.z.fixed + 0x800000;
                g_BattleEffects[slot].pos.z.part.integer += ENCOUNTER_ENEMIES[g_BattleEnemyBattlers[i].type].height;
                TASK(PartyMember)->param.unk_0B += 1;
            }
        }
    } else {
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            if (!Battle_SlotIsBlocked(i)) {
                slot                               = Battle_AllocEffect(1, 39);
                g_BattleEffects[slot].target.party = TASK(PartyMember);
                g_BattleEffects[slot].unk_04       = TASK(PartyMember)->param.unk_0B;
                g_BattleEffects[slot].arg.unk_09   = i * 8 + 1;
                g_BattleEffects[slot].pos.x.fixed  = g_Game.members[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_Game.members[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_Game.members[i].pos.z.fixed + 0x800000;
                TASK(PartyMember)->param.unk_0B += 1;
            }
        }
    }
    for (i = 1; i < 16; i++) {
        MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] = MEM_PTR(u16, AREA_PALETTE_ARENA)[i] | PSX_COLOR_STP_BIT;
    }
    g_GfxPalettePending                                          = 1;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = *MEM_PTR(u16, AREA_PALETTE_ARENA);
    TASK(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF0A8 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0EC(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 2, g_Task);
}

MATCH void func_801EF130(void) {
    PartyMember* work;
    u8           slot;
    u8           i;

    TASK(PartyMember)->param.unk_0B = 0;
    for (i = 0; i < 4; i++) {
        slot                                   = BMagic_AllocEffect();
        work                                   = TASK(PartyMember);
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[slot].unk_04       = i;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 2 + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = work;
        TASK(PartyMember)->param.unk_0B++;
    }
    for (i = 0; i < 4; i++) {
        slot                                   = BMagic_AllocEffect();
        work                                   = TASK(PartyMember);
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 1;
        BMAGIC_EFFECT_SLOTS[slot].unk_04       = i;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 2 + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = work;
        TASK(PartyMember)->param.unk_0B++;
    }
    TASK(PartyMember)->header.step++;
    if (TASK(PartyMember)->unk_04 == 0) {
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
}

MATCH void func_801EF2C0(void) {
    if (TASK(PartyMember)->param.unk_0B == 2) {
        TASK(PartyMember)->unk_04 = 0;
        TASK(PartyMember)->unk_09 = 8;
        TASK(PartyMember)->timer  = 16;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF324(void) {
    PartyMember* work;
    u8           count;
    u8           slot;
    u8           timer;

    if (TASK(PartyMember)->unk_04 == 0) {
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x01));
    }
    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count == 0) {
        slot                                   = BMagic_AllocEffect();
        work                                   = TASK(PartyMember);
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 2;
        BMAGIC_EFFECT_SLOTS[slot].target.party = work;
        slot                                   = BMagic_AllocEffect();
        work                                   = TASK(PartyMember);
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 3;
        BMAGIC_EFFECT_SLOTS[slot].target.party = work;
        TASK(PartyMember)->unk_09              = 8;
        timer                                  = TASK(PartyMember)->timer - 1;
        TASK(PartyMember)->timer               = timer;
        if (timer == 0) {
            TASK(PartyMember)->param.unk_0B = 0x82;
            TASK(PartyMember)->unk_09       = 0;
            TASK(PartyMember)->header.step += 1;
        }
    }
    TASK(PartyMember)->unk_04 += 1;
    Battle_ProjectRange();
    func_801EF580(0);
    func_801EF580(0xF);
}

MATCH void func_801EF4A0(void) {
    u8 counter;

    counter                   = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x10) {
        TASK(PartyMember)->header.step += 1;
        return;
    }
    TASK(PartyMember)->unk_04 += 1;
    Battle_ProjectRange();
    func_801EF580(0);
    func_801EF580(0xF);
}

MATCH void func_801EF530(void) {
    PartyMember* work;

    if (TASK(PartyMember)->param.unk_0B == 0x80) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Effect_Reset();
    }
}

/* Draws a column of up to eight semi-transparent 8 by 8 textured quads rising from the effect's
 * screen point, each edge swayed by a sine of the frame counter plus the row and phase, brightening
 * up the column to row 6 and fading after it; step 3 starts the column higher as unk_09 grows. */
MATCH void func_801EF580(s32 phase) {
    POLY_GT4* prim;
    s32       count;
    s32       i;
    s32       start;
    s32       offset;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.words[2] = 1;
    start                       = 0;
    count                       = 8;
    if (TASK(PartyMember)->unk_04 < 16) {
        count = (TASK(PartyMember)->unk_04 >> 1) + 1;
    }
    if (TASK(PartyMember)->header.step == 3) {
        start = TASK(PartyMember)->unk_09 >> 1;
    }
    for (i = start; i < count; i++) {
        prim = GFX_CURSOR(POLY_GT4);
        SetPolyGT4(prim);
        PSX_SET_SEMI_TRANSPARENT(prim);
        g_ScratchPad.cells.words[1] = ((TASK(PartyMember)->unk_04 + i + phase + 1) & 0x1F) << 7;
        offset                      = ((rsin(g_ScratchPad.cells.words[1]) * 8) >> 12) + 4;
        setXY2(prim, TASK(PartyMember)->screen_x.value - offset, TASK(PartyMember)->screen_y.value - (i + 1) * 8, prim->x0 + 8, TASK(PartyMember)->screen_y.value - (i + 1) * 8);
        g_ScratchPad.cells.words[1] = ((TASK(PartyMember)->unk_04 + phase + i) & 0x1F) << 7;
        offset                      = ((rsin(g_ScratchPad.cells.words[1]) * 8) >> 12) + 4;
        prim->x2                    = TASK(PartyMember)->screen_x.value - offset;
        prim->y2                    = TASK(PartyMember)->screen_y.value - i * 8;
        prim->x3                    = prim->x2 + 8;
        prim->y3                    = TASK(PartyMember)->screen_y.value - i * 8;
        setRGB2(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2]);
        setRGB3(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2]);
        if (i < 6) {
            g_ScratchPad.cells.words[2] = (i + 1) * 16;
        } else {
            g_ScratchPad.cells.words[2] = 0x61 - (i - 5) * 48;
        }
        setRGB0(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2]);
        setRGB1(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2]);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x3C0, 0x100);
        prim->clut  = GetClut(0, 0x1FA);
        setUV4(prim, 0, (i * 8 + TASK(PartyMember)->unk_04 * 2) & 0x1F, 8, (i * 8 + TASK(PartyMember)->unk_04 * 2) & 0x1F, 0, ((i * 8 + TASK(PartyMember)->unk_04 * 2) & 0x1F) + 8, 8,
               ((i * 8 + TASK(PartyMember)->unk_04 * 2) & 0x1F) + 8);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_GT4));
    }
}

MATCH void func_801EF958(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Task);
}

MATCH void func_801EF99C(void) {
    SYS_DISPATCH_BYTE(D_801F0530, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        if (TASK(PartyMember)->header.step != 0 && TASK(PartyMember)->header.step != 3) {
            func_801EFF50();
            func_801F0014();
            PopMatrix();
        }
    }
}

MATCH void func_801EFA2C(void) {
    u8 value;

    value                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        TASK(PartyMember)->unk_0C = 0x100;
        TASK(PartyMember)->unk_18 = 4;
        if (TASK(PartyMember)->header.mode != 0) {
            TASK(PartyMember)->param.unk_0B = 0;
            TASK(PartyMember)->unk_09       = 0;
        } else {
            TASK(PartyMember)->param.unk_0B = 8;
            TASK(PartyMember)->unk_09       = 0x1F;
        }
        TASK(PartyMember)->timer = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFAD4(void) {
    PartyMember* work;
    PartyMember* battler;
    s32          offset;

    TASK(PartyMember)->param.unk_0B += 1;
    g_ScratchPad.cells.words[1]    = (++TASK(PartyMember)->unk_09 & 0x3F) << 6;
    g_ScratchPad.cells.words[0]    = TASK(PartyMember)->unk_0C -= TASK(PartyMember)->unk_18;
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin(g_ScratchPad.cells.words[1]) * g_ScratchPad.cells.words[0]) >> 3);
    offset                         = rcos(g_ScratchPad.cells.words[1]) * g_ScratchPad.cells.words[0];
    battler                        = g_BattleEffectBattler;
    work                           = TASK(PartyMember);
    work->pos.y.fixed              = battler->pos.y.fixed + (offset >> 3);
    work->pos.z.fixed              = battler->pos.z.fixed;
    if (work->timer < 33) {
        work->timer += 1;
    }
    if (TASK(PartyMember)->unk_0C == 0) {
        if (TASK(PartyMember)->unk_04 != 0) {
            BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
            TASK(PartyMember)->header.flags = 0;
            TASK(PartyMember)->header.mode  = 0;
            TASK(PartyMember)->header.step  = 0;
            TASK(PartyMember)->unk_03       = 0;
            TASK(PartyMember)->unk_04       = 0;
        } else {
            TASK(PartyMember)->header.step += 1;
        }
    }
}

MATCH void func_801EFCA0(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 130) {
        work              = SP_REF(PartyMember*, 0x44u);
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EFCE0(void) {
    u8 timer;

    timer                    = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = timer;
    if (!(timer & BYTE_MASK)) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        TASK(PartyMember)->header.flags = 0;
        TASK(PartyMember)->header.mode  = 0;
        TASK(PartyMember)->header.step  = 0;
        TASK(PartyMember)->unk_03       = 0;
        TASK(PartyMember)->unk_04       = 0;
    }
}

MATCH void func_801EFD7C(void) {
    BMAGIC_DISPATCH_AND_DRAW_IN_OWN_MATRIX(D_801F0540, func_801EFF50, func_801F0014);
}

MATCH void func_801EFE04(void) {
    TASK(PartyMember)->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed = BATTLE_ACTIVE_WORK->pos.z.fixed;
    if (TASK(PartyMember)->header.mode == 2) {
        TASK(PartyMember)->param.unk_0B = 0;
    } else {
        TASK(PartyMember)->param.unk_0B = 8;
    }
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->timer  = 32;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EFE90(void) {
    PartyMember* work;
    u8           timer;

    work         = TASK(PartyMember);
    work->unk_09 = work->unk_09 + 1;
    work->pos.z.fixed -= 0x80000;
    timer                    = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = timer;
    if (!(timer & BYTE_MASK)) {
        TASK(PartyMember)->header.step += 1;
        TASK(PartyMember)->header.flags = 0;
        TASK(PartyMember)->header.mode  = 0;
        TASK(PartyMember)->header.step  = 0;
        TASK(PartyMember)->unk_03       = 0;
        TASK(PartyMember)->unk_04       = 0;
    }
}

MATCH void func_801EFF50(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    ;
    PushMatrix();
    setVector(&rot, 0, 0, (TASK(PartyMember)->param.unk_0B & 0x3f) << 6);
    setVector(&pos, (TASK(PartyMember)->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (TASK(PartyMember)->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, -(COORD_INT(TASK(PartyMember)->pos.z) + 0x200) / 2);
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

/* Outlines a square around the effect with two semi-transparent gouraud line triangles (corners at
 * 45, 135, 225 and 315 degrees), its radius 0x80 and growing by 4 per unk_09 from mode 2 on, the
 * shade timer times the frame counter's table step. */
MATCH void func_801F0014(void) {
    LINE_G3* prim;
    s32      tpage;
    long     depth;
    long     flag;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));

    prim = GFX_CURSOR(LINE_G3);
    SetLineG3(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    if (TASK(PartyMember)->header.mode < 2) {
        g_ScratchPad.cells.words[0] = 0x80;
    } else {
        g_ScratchPad.cells.words[0] = TASK(PartyMember)->unk_09 * 4 + 0x80;
    }
    setVector(&g_ScratchPadVectors[0], FIXED_MUL(rsin(0x200), g_ScratchPad.cells.words[0]), FIXED_MUL(rcos(0x200), g_ScratchPad.cells.words[0]), 0);
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(0x600), g_ScratchPad.cells.words[0]), FIXED_MUL(rcos(0x600), g_ScratchPad.cells.words[0]), 0);
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0xA00), g_ScratchPad.cells.words[0]), FIXED_MUL(rcos(0xA00), g_ScratchPad.cells.words[0]), 0);
    RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    g_ScratchPad.cells.words[2] = TASK(PartyMember)->timer * D_801F0548[TASK(PartyMember)->unk_04];
    setRGB0(prim, g_ScratchPad.cells.words[2], 1, g_ScratchPad.cells.words[2]);
    setRGB1(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], 1);
    setRGB2(prim, g_ScratchPad.cells.words[2], 1, g_ScratchPad.cells.words[2]);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(LINE_G3));

    prim = GFX_CURSOR(LINE_G3);
    SetLineG3(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    setVector(&g_ScratchPadVectors[0], FIXED_MUL(rsin(0xA00), g_ScratchPad.cells.words[0]), FIXED_MUL(rcos(0xA00), g_ScratchPad.cells.words[0]), 0);
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(0xE00), g_ScratchPad.cells.words[0]), FIXED_MUL(rcos(0xE00), g_ScratchPad.cells.words[0]), 0);
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0x200), g_ScratchPad.cells.words[0]), FIXED_MUL(rcos(0x200), g_ScratchPad.cells.words[0]), 0);
    RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    setRGB0(prim, g_ScratchPad.cells.words[2], 1, g_ScratchPad.cells.words[2]);
    setRGB1(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], 1);
    setRGB2(prim, g_ScratchPad.cells.words[2], 1, g_ScratchPad.cells.words[2]);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(LINE_G3));
}

/* func_801F04A4 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"
