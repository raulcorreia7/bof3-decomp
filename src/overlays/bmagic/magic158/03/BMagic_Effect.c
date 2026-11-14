#include "magic158_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlotsWithSetup.h"

#include "overlays/bmagic/func_801EED04.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEEF0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF34(void) {
    SYS_DISPATCH_BYTE(D_801EF788, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF2F0();
        func_801EF3EC();
        PopMatrix();
    }
}

/* At the ticker's zero, places the effect half a cell from the battler by the
 * angle byte 0x0B and starts its rise from a random tint row. */
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
        /* kept: (s16) types the rsin angle; without it GCC folds the two shifts and the body is 4 bytes short. */
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin((s16)(phase << 8)) * 0x8000) >> 12);
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle_cell) * 0x8000) >> 12);
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(1152);
        entry               = RANDOM_MASK(7) * 3;
        g_Task->unk_5D      = D_801EF76C[entry];
        g_Task->unk_5E      = D_801EF76C[entry + 1];
        g_Task->unk_5F      = D_801EF76C[entry + 2];
        g_Task->unk_14      = 0x80;
        g_Task->unk_20      = -0x10;
        g_Task->unk_09      = 8;
        g_Task->timer       = 2;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF140(void) {
    u8 count;
    u8 timer;

    count                    = g_Task->unk_09;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) - 0x60;
    if ((count & BYTE_MASK) != 0x10) {
        g_Task->unk_09 = count + 1;
    }
    timer = g_Task->timer;
    if (timer != 16) {
        g_Task->timer = timer + 2;
    }
    if (COORD_INT(g_Task->pos.z) == COORD_INT(BATTLE_ACTIVE_WORK->pos.z)) {
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF1C8);

#include "overlays/bmagic/BMagic_SetupEffectMatrix.h"

MATCH void func_801EF2F0(void) {
    BMAGIC_SETUP_EFFECT_MATRIX();
}

MATCH void func_801EF3EC(void) {
    POLY_F4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32      i;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->unk_09 * 2;
    D_1F800000.view.effect.params[1] = g_Task->unk_09 * 4;
    D_1F800000.view.effect.params[3] = (s8)g_Task->unk_5D * g_Task->timer;
    D_1F800000.view.effect.params[4] = (s8)g_Task->unk_5E * g_Task->timer;
    D_1F800000.view.effect.params[5] = (s8)g_Task->unk_5F * g_Task->timer;
    for (i = 0; i < 10; i += 2) {
        prim = (POLY_F4*)g_GfxPrimCursor;
        SetPolyF4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = FIXED_MUL(rsin((i + 1) * 0x199), D_1F800000.view.effect.params[1]);
        D_1F800014[0].vy = FIXED_MUL(rcos((i + 1) * 0x199), D_1F800000.view.effect.params[1]);
        D_1F800014[0].vz = 0;
        D_1F800014[1].vx = FIXED_MUL(rsin(i * 0x199), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy = FIXED_MUL(rcos(i * 0x199), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz = 0;
        if (i == 8) {
            D_1F800000.view.effect.params[2] = 0;
        } else {
            D_1F800000.view.effect.params[2] = (i + 2) * 0x199;
        }
        D_1F800014[2].vx = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz = 0;
        D_1F800014[3].vx = 0;
        D_1F800014[3].vy = 0;
        D_1F800014[3].vz = 0;
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_F4));
    }
}

/* func_801EF708 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
