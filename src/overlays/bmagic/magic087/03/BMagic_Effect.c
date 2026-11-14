#include "magic087_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlotsWithSetup.h"

/* Clears the effect slot table and spawns one effect 0x27 at each selectable battler, the enemies
 * (raised by the enemy kind's height) when the target selector holds 0x40 and the party otherwise,
 * each starting 8 frames after the one before by slot; then sets STP on colours 1 to 15 of work
 * palette row 26 from arena row 0. */
MATCH void func_801EED04(void) {
    u8 i;
    u8 slot;
    u8 battler;

    g_Task->param.unk_0B = 0;
    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    if (g_Battle.target_selector & 0x40) {
        for (i = 0; i < 8; i++) {
            battler = i + BATTLE_PARTY_CHARACTERS_COUNT;
            if (!Battle_SlotIsBlocked(battler)) {
                slot                               = Battle_AllocEffect(1, 0x27);
                g_BattleEffects[slot].target.party = g_Task;
                g_BattleEffects[slot].unk_04       = g_Task->param.unk_0B;
                g_BattleEffects[slot].arg.unk_09   = i * 8 + 1;
                g_BattleEffects[slot].pos.x.fixed  = g_BattleEnemyBattlers[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_BattleEnemyBattlers[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_BattleEnemyBattlers[i].pos.z.fixed + 0x800000;
                g_BattleEffects[slot].pos.z.part.integer += ENCOUNTER_ENEMIES[g_BattleEnemyBattlers[i].kind].height;
                g_Task->param.unk_0B += 1;
            }
        }
    } else {
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            if (!Battle_SlotIsBlocked(i)) {
                slot                               = Battle_AllocEffect(1, 0x27);
                g_BattleEffects[slot].target.party = g_Task;
                g_BattleEffects[slot].unk_04       = g_Task->param.unk_0B;
                g_BattleEffects[slot].arg.unk_09   = i * 8 + 1;
                g_BattleEffects[slot].pos.x.fixed  = g_Game.members[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_Game.members[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_Game.members[i].pos.z.fixed + 0x800000;
                g_Task->param.unk_0B += 1;
            }
        }
    }
    for (i = 1; i < 16; i++) {
        MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[i] = MEM_PTR(u16, AREA_PALETTE_ARENA)[i] | 0x8000;
    }
    g_GfxPalettePending                                      = 1;
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA);
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF0A8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0EC(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 2, g_Task);
}

MATCH void func_801EF130(void) {
    PartyMember* work;
    u8           slot;
    u8           i;

    g_Task->param.unk_0B = 0;
    for (i = 0; i < 4; i++) {
        slot                                   = BMagic_AllocEffect();
        work                                   = g_Task;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[slot].unk_04       = i;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 2 + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = work;
        g_Task->param.unk_0B++;
    }
    for (i = 0; i < 4; i++) {
        slot                                   = BMagic_AllocEffect();
        work                                   = g_Task;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 1;
        BMAGIC_EFFECT_SLOTS[slot].unk_04       = i;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 2 + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = work;
        g_Task->param.unk_0B++;
    }
    g_Task->header.step++;
    if (g_Task->unk_04 == 0) {
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
}

MATCH void func_801EF2C0(void) {
    if (g_Task->param.unk_0B == 2) {
        g_Task->unk_04 = 0;
        g_Task->unk_09 = 8;
        g_Task->timer  = 16;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF324(void) {
    PartyMember* work;
    u8           count;
    u8           slot;
    u8           timer;

    if (g_Task->unk_04 == 0) {
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x01));
    }
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        slot                                   = BMagic_AllocEffect();
        work                                   = g_Task;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 2;
        BMAGIC_EFFECT_SLOTS[slot].target.party = work;
        slot                                   = BMagic_AllocEffect();
        work                                   = g_Task;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 3;
        BMAGIC_EFFECT_SLOTS[slot].target.party = work;
        g_Task->unk_09                         = 8;
        timer                                  = g_Task->timer - 1;
        g_Task->timer                          = timer;
        if (timer == 0) {
            g_Task->param.unk_0B = 0x82;
            g_Task->unk_09       = 0;
            g_Task->header.step += 1;
        }
    }
    g_Task->unk_04 += 1;
    Battle_ProjectRange();
    func_801EF580(0);
    func_801EF580(0xF);
}

MATCH void func_801EF4A0(void) {
    u8 counter;

    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x10) {
        g_Task->header.step += 1;
        return;
    }
    g_Task->unk_04 += 1;
    Battle_ProjectRange();
    func_801EF580(0);
    func_801EF580(0xF);
}

MATCH void func_801EF530(void) {
    PartyMember* work;

    if (g_Task->param.unk_0B == 0x80) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        func_801E5988();
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

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.scenario.math_08 = 1;
    start                            = 0;
    count                            = 8;
    if (g_Task->unk_04 < 16) {
        count = (g_Task->unk_04 >> 1) + 1;
    }
    if (g_Task->header.step == 3) {
        start = g_Task->unk_09 >> 1;
    }
    for (i = start; i < count; i++) {
        prim = GFX_CURSOR(POLY_GT4);
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.view.scenario.math_04 = ((g_Task->unk_04 + i + phase + 1) & 0x1F) << 7;
        offset                           = ((rsin(D_1F800000.view.scenario.math_04) * 8) >> 12) + 4;
        prim->x0                         = g_Task->unk_2E.half - offset;
        prim->y0                         = g_Task->unk_30.half - (i + 1) * 8;
        prim->x1                         = prim->x0 + 8;
        prim->y1                         = g_Task->unk_30.half - (i + 1) * 8;
        D_1F800000.view.scenario.math_04 = ((g_Task->unk_04 + phase + i) & 0x1F) << 7;
        offset                           = ((rsin(D_1F800000.view.scenario.math_04) * 8) >> 12) + 4;
        prim->x2                         = g_Task->unk_2E.half - offset;
        prim->y2                         = g_Task->unk_30.half - i * 8;
        prim->x3                         = prim->x2 + 8;
        prim->y3                         = g_Task->unk_30.half - i * 8;
        prim->r2                         = D_1F800000.view.scenario.math_08;
        prim->g2                         = D_1F800000.view.scenario.math_08;
        prim->b2                         = D_1F800000.view.scenario.math_08;
        prim->r3                         = D_1F800000.view.scenario.math_08;
        prim->g3                         = D_1F800000.view.scenario.math_08;
        prim->b3                         = D_1F800000.view.scenario.math_08;
        if (i < 6) {
            D_1F800000.view.scenario.math_08 = (i + 1) * 16;
        } else {
            D_1F800000.view.scenario.math_08 = 0x61 - (i - 5) * 48;
        }
        prim->r0    = D_1F800000.view.scenario.math_08;
        prim->g0    = D_1F800000.view.scenario.math_08;
        prim->b0    = D_1F800000.view.scenario.math_08;
        prim->r1    = D_1F800000.view.scenario.math_08;
        prim->g1    = D_1F800000.view.scenario.math_08;
        prim->b1    = D_1F800000.view.scenario.math_08;
        prim->tpage = GetTPage(0, 1, 0x3C0, 0x100);
        prim->clut  = GetClut(0, 0x1FA);
        prim->u0    = 0;
        prim->v0    = (i * 8 + g_Task->unk_04 * 2) & 0x1F;
        prim->u1    = 8;
        prim->v1    = (i * 8 + g_Task->unk_04 * 2) & 0x1F;
        prim->u2    = 0;
        prim->v2    = ((i * 8 + g_Task->unk_04 * 2) & 0x1F) + 8;
        prim->u3    = 8;
        prim->v3    = ((i * 8 + g_Task->unk_04 * 2) & 0x1F) + 8;
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_GT4));
    }
}

MATCH void func_801EF958(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Task);
}

MATCH void func_801EF99C(void) {
    SYS_DISPATCH_BYTE(D_801F0530, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        if (g_Task->header.step != 0 && g_Task->header.step != 3) {
            func_801EFF50();
            func_801F0014();
            PopMatrix();
        }
    }
}

MATCH void func_801EFA2C(void) {
    u8 value;

    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        g_Task->unk_0C = 0x100;
        g_Task->unk_18 = 4;
        if (g_Task->header.mode != 0) {
            g_Task->param.unk_0B = 0;
            g_Task->unk_09       = 0;
        } else {
            g_Task->param.unk_0B = 8;
            g_Task->unk_09       = 0x1F;
        }
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFAD4(void) {
    PartyMember* work;
    PartyMember* battler;
    s32          offset;

    g_Task->param.unk_0B += 1;
    D_1F800000.view.scenario.math_04 = (++g_Task->unk_09 & 0x3F) << 6;
    D_1F800000.view.scenario.math_00 = g_Task->unk_0C -= g_Task->unk_18;
    g_Task->pos.x.fixed              = g_BattleEffectBattler->pos.x.fixed + ((rsin(D_1F800000.view.scenario.math_04) * D_1F800000.view.scenario.math_00) >> 3);
    offset                           = rcos(D_1F800000.view.scenario.math_04) * D_1F800000.view.scenario.math_00;
    battler                          = g_BattleEffectBattler;
    work                             = g_Task;
    work->pos.y.fixed                = battler->pos.y.fixed + (offset >> 3);
    work->pos.z.fixed                = battler->pos.z.fixed;
    if (work->timer < 33) {
        work->timer += 1;
    }
    if (g_Task->unk_0C == 0) {
        if (g_Task->unk_04 != 0) {
            BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
            g_Task->header.flags = 0;
            g_Task->header.mode  = 0;
            g_Task->header.step  = 0;
            g_Task->unk_03       = 0;
            g_Task->unk_04       = 0;
        } else {
            g_Task->header.step += 1;
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

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (!(timer & BYTE_MASK)) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        g_Task->header.flags = 0;
        g_Task->header.mode  = 0;
        g_Task->header.step  = 0;
        g_Task->unk_03       = 0;
        g_Task->unk_04       = 0;
    }
}

MATCH void func_801EFD7C(void) {
    SYS_DISPATCH_BYTE(D_801F0540, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EFF50();
        func_801F0014();
        PopMatrix();
    }
}

MATCH void func_801EFE04(void) {
    g_Task->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed;
    g_Task->pos.z.fixed = BATTLE_ACTIVE_WORK->pos.z.fixed;
    if (g_Task->header.mode == 2) {
        g_Task->param.unk_0B = 0;
    } else {
        g_Task->param.unk_0B = 8;
    }
    g_Task->unk_09 = 0;
    g_Task->timer  = 32;
    g_Task->header.step += 1;
}

MATCH void func_801EFE90(void) {
    PartyMember* work;
    u8           timer;

    work         = g_Task;
    work->unk_09 = work->unk_09 + 1;
    work->pos.z.fixed -= 0x80000;
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->header.step += 1;
        g_Task->header.flags = 0;
        g_Task->header.mode  = 0;
        g_Task->header.step  = 0;
        g_Task->unk_03       = 0;
        g_Task->unk_04       = 0;
    }
}

MATCH void func_801EFF50(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    ;
    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = (g_Task->param.unk_0B & 0x3f) << 6;
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -(COORD_INT(g_Task->pos.z) + 0x200) / 2;
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

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));

    prim = GFX_CURSOR(LINE_G3);
    SetLineG3(prim);
    SetSemiTrans(prim, 1);
    if (g_Task->header.mode < 2) {
        D_1F800000.view.scenario.math_00 = 0x80;
    } else {
        D_1F800000.view.scenario.math_00 = g_Task->unk_09 * 4 + 0x80;
    }
    D_1F800014[0].vx = FIXED_MUL(rsin(0x200), D_1F800000.view.scenario.math_00);
    D_1F800014[0].vy = FIXED_MUL(rcos(0x200), D_1F800000.view.scenario.math_00);
    D_1F800014[0].vz = 0;
    D_1F800014[1].vx = FIXED_MUL(rsin(0x600), D_1F800000.view.scenario.math_00);
    D_1F800014[1].vy = FIXED_MUL(rcos(0x600), D_1F800000.view.scenario.math_00);
    D_1F800014[1].vz = 0;
    D_1F800014[2].vx = FIXED_MUL(rsin(0xA00), D_1F800000.view.scenario.math_00);
    D_1F800014[2].vy = FIXED_MUL(rcos(0xA00), D_1F800000.view.scenario.math_00);
    D_1F800014[2].vz = 0;
    RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    D_1F800000.view.scenario.math_08 = g_Task->timer * D_801F0548[g_Task->unk_04];
    setRGB0(prim, D_1F800000.view.scenario.math_08, 1, D_1F800000.view.scenario.math_08);
    setRGB1(prim, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08, 1);
    setRGB2(prim, D_1F800000.view.scenario.math_08, 1, D_1F800000.view.scenario.math_08);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(LINE_G3));

    prim = GFX_CURSOR(LINE_G3);
    SetLineG3(prim);
    SetSemiTrans(prim, 1);
    D_1F800014[0].vx = FIXED_MUL(rsin(0xA00), D_1F800000.view.scenario.math_00);
    D_1F800014[0].vy = FIXED_MUL(rcos(0xA00), D_1F800000.view.scenario.math_00);
    D_1F800014[0].vz = 0;
    D_1F800014[1].vx = FIXED_MUL(rsin(0xE00), D_1F800000.view.scenario.math_00);
    D_1F800014[1].vy = FIXED_MUL(rcos(0xE00), D_1F800000.view.scenario.math_00);
    D_1F800014[1].vz = 0;
    D_1F800014[2].vx = FIXED_MUL(rsin(0x200), D_1F800000.view.scenario.math_00);
    D_1F800014[2].vy = FIXED_MUL(rcos(0x200), D_1F800000.view.scenario.math_00);
    D_1F800014[2].vz = 0;
    RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    setRGB0(prim, D_1F800000.view.scenario.math_08, 1, D_1F800000.view.scenario.math_08);
    setRGB1(prim, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08, 1);
    setRGB2(prim, D_1F800000.view.scenario.math_08, 1, D_1F800000.view.scenario.math_08);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(LINE_G3));
}

/* func_801F04A4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
