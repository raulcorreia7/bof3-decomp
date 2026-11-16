#include "magic166_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_MarkDamagedOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801EF724[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801EF724[i];
            g_BattleEffectBattler = D_801EF724[i].target.party;
            BMagic_DispatchEffectMode();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

#include "overlays/bmagic/func_801EED04.h"

#include "overlays/bmagic/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEEF0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF34(void) {
    SYS_DISPATCH_BYTE(D_801EF71C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF284();
        func_801EF380();
        PopMatrix();
    }
}

/* At the ticker's zero, places the effect on the battler offset by the angle byte 0x0B and starts its fall from a random tint row. */
MATCH void func_801EEFBC(void) {
    u8   count;
    s32  phase;
    s32  entry;
    s16* angle_cell;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        angle_cell          = &D_1F800004;
        phase               = g_Task->param.unk_0B & 0xF;
        *angle_cell         = phase << 8;
        /* kept: (s16) types the rsin angle; without it GCC folds the two shifts. */
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin((s16)(phase << 8)) * 0x8000) >> 12);
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle_cell) * 0x8000) >> 12);
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        entry               = RANDOM_MASK(7) * 3;
        g_Task->unk_5D      = D_801EF700[entry];
        g_Task->unk_5E      = D_801EF700[entry + 1];
        g_Task->unk_5F      = D_801EF700[entry + 2];
        g_Task->unk_14      = 0x80;
        g_Task->unk_20      = -8;
        g_Task->unk_09      = 1;
        g_Task->timer       = 16;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF138(void) {
    s16* angle_cell;
    u8   phase;
    u8   count;

    angle_cell  = &D_1F800004;
    phase       = g_Task->param.unk_0B & 0x1F;
    *angle_cell = phase << 7;
    g_Task->pos.x.fixed += (rsin(phase << 7) * 0x1000) >> 12;
    g_Task->pos.y.fixed += (rcos(*angle_cell) * 0x1000) >> 12;
    g_Task->unk_14 += g_Task->unk_20;
    COORD_INT(g_Task->pos.z) += g_Task->unk_14;
    count = g_Task->unk_09;
    if ((count & BYTE_MASK) != 0x10) {
        g_Task->unk_09 = count + 1;
    } else if (--g_Task->timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.flags = 0;
        g_Task->header.mode  = 0;
        g_Task->header.step  = 0;
        g_Task->unk_03       = 0;
        g_Task->unk_04       = 0;
    }
}

#include "overlays/bmagic/BMagic_SetupEffectMatrix.h"

MATCH void func_801EF284(void) {
    BMAGIC_SETUP_EFFECT_MATRIX();
}

/* Draw the magic166 star as five flat quads round the effect, each from the centre out to a
 * point on the outer radius between two on the inner one, tinted by the work tint and the timer. */
MATCH void func_801EF380(void) {
    POLY_F4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.cells.halves[0] = g_Task->unk_09 * 2;
    D_1F800000.cells.halves[1] = g_Task->unk_09 * 4;
    D_1F800000.cells.halves[3] = (s8)g_Task->unk_5D * g_Task->timer;
    D_1F800000.cells.halves[4] = (s8)g_Task->unk_5E * g_Task->timer;
    D_1F800000.cells.halves[5] = (s8)g_Task->unk_5F * g_Task->timer;
    for (i = 0; i < 10; i += 2) {
        prim = (POLY_F4*)g_GfxPrimCursor;
        SetPolyF4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = FIXED_MUL(rsin((i + 1) * 409), D_1F800000.cells.halves[1]);
        D_1F800014[0].vy = FIXED_MUL(rcos((i + 1) * 409), D_1F800000.cells.halves[1]);
        D_1F800014[0].vz = 0;
        D_1F800014[1].vx = FIXED_MUL(rsin(i * 409), D_1F800000.cells.halves[0]);
        D_1F800014[1].vy = FIXED_MUL(rcos(i * 409), D_1F800000.cells.halves[0]);
        D_1F800014[1].vz = 0;
        if (i == 8) {
            D_1F800000.cells.halves[2] = 0;
        } else {
            D_1F800000.cells.halves[2] = (i + 2) * 409;
        }
        D_1F800014[2].vx = FIXED_MUL(rsin(D_1F800000.cells.halves[2]), D_1F800000.cells.halves[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(D_1F800000.cells.halves[2]), D_1F800000.cells.halves[0]);
        D_1F800014[2].vz = 0;
        setVector(&D_1F800014[3], 0, 0, 0);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, D_1F800000.cells.halves[3], D_1F800000.cells.halves[4], D_1F800000.cells.halves[5]);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_F4));
    }
}

/* func_801EF69C */
#include "overlays/bmagic/BMagic_AllocEffect.h"
