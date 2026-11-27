#include "magic158_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_RunSlotsWithSetup.h"

#include "overlays/bmagic/shared/func_801EED04.h"

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEEF0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF34(void) {
    BMAGIC_DISPATCH_AND_DRAW_IN_OWN_MATRIX(D_801EF788, func_801EF2F0, func_801EF3EC);
}

/* At the ticker's zero, places the effect half a cell from the battler by the
 * angle byte 0x0B and starts its rise from a random tint row. */
MATCH void func_801EEFBC(void) {
    u8   count;
    s32  phase;
    s32  entry;
    s16* angle_cell;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        angle_cell                     = &D_1F800004;
        phase                          = SELF(PartyMember)->param.unk_0B & 0xF;
        *angle_cell                    = phase << 8;
        /* kept: (s16) types the rsin angle; without it GCC folds the two shifts and the body is 4 bytes short. */
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin((s16)(phase << 8)) * 0x8000) >> 12);
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle_cell) * 0x8000) >> 12);
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(1152);
        entry                          = RANDOM_MASK(7) * 3;
        SELF(PartyMember)->unk_5D      = D_801EF76C[entry];
        SELF(PartyMember)->unk_5E      = D_801EF76C[entry + 1];
        SELF(PartyMember)->unk_5F      = D_801EF76C[entry + 2];
        SELF(PartyMember)->unk_14      = 0x80;
        SELF(PartyMember)->unk_20      = -0x10;
        SELF(PartyMember)->unk_09      = 8;
        SELF(PartyMember)->timer       = 2;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF140(void) {
    u8 count;
    u8 timer;

    count                               = SELF(PartyMember)->unk_09;
    COORD_INT(SELF(PartyMember)->pos.z) = COORD_INT(SELF(PartyMember)->pos.z) - 0x60;
    if ((count & BYTE_MASK) != 0x10) {
        SELF(PartyMember)->unk_09 = count + 1;
    }
    timer = SELF(PartyMember)->timer;
    if (timer != 16) {
        SELF(PartyMember)->timer = timer + 2;
    }
    if (COORD_INT(SELF(PartyMember)->pos.z) == COORD_INT(BATTLE_ACTIVE_WORK->pos.z)) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF1C8(void) {
    s16* angle_cell;
    u8   phase;

    angle_cell  = &D_1F800004;
    phase       = SELF(PartyMember)->param.unk_0B & 0xF;
    *angle_cell = phase << 8;
    SELF(PartyMember)->pos.x.fixed += (rsin(phase << 8) * 0x1000) >> 12;
    SELF(PartyMember)->pos.y.fixed += (rcos(*angle_cell) * 0x1000) >> 12;
    SELF(PartyMember)->unk_14 += SELF(PartyMember)->unk_20;
    COORD_INT(SELF(PartyMember)->pos.z) += SELF(PartyMember)->unk_14;
    if (--SELF(PartyMember)->timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        SELF(PartyMember)->header.flags = 0;
        SELF(PartyMember)->header.mode  = 0;
        SELF(PartyMember)->header.step  = 0;
        SELF(PartyMember)->unk_03       = 0;
        SELF(PartyMember)->unk_04       = 0;
    }
}

#include "overlays/bmagic/shared/BMagic_SetupEffectMatrix.h"

MATCH void func_801EF2F0(void) {
    BMAGIC_SETUP_EFFECT_MATRIX();
}

MATCH void func_801EF3EC(void) {
    POLY_F4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32      i;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09 * 2;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_09 * 4;
    g_ScratchPad.cells.halves[3] = (s8)SELF(PartyMember)->unk_5D * SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[4] = (s8)SELF(PartyMember)->unk_5E * SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[5] = (s8)SELF(PartyMember)->unk_5F * SELF(PartyMember)->timer;
    for (i = 0; i < 10; i += 2) {
        prim = (POLY_F4*)g_GfxPrimCursor;
        SetPolyF4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPadVectors[0].vx = FIXED_MUL(rsin((i + 1) * 0x199), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[0].vy = FIXED_MUL(rcos((i + 1) * 0x199), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[0].vz = 0;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i * 0x199), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i * 0x199), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz = 0;
        if (i == 8) {
            g_ScratchPad.cells.halves[2] = 0;
        } else {
            g_ScratchPad.cells.halves[2] = (i + 2) * 0x199;
        }
        g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vz = 0;
        setVector(&g_ScratchPadVectors[3], 0, 0, 0);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_F4));
    }
}

/* func_801EF708 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"
