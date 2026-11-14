#include "magic166_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_PlayOnZeroTick);

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

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

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

INCLUDE_ASM(func_801EEFBC);

INCLUDE_ASM(func_801EF138);

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

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
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
        D_1F800014[0].vx = FIXED_MUL(rsin((i + 1) * 409), D_1F800000.view.effect.params[1]);
        D_1F800014[0].vy = FIXED_MUL(rcos((i + 1) * 409), D_1F800000.view.effect.params[1]);
        D_1F800014[0].vz = 0;
        D_1F800014[1].vx = FIXED_MUL(rsin(i * 409), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy = FIXED_MUL(rcos(i * 409), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz = 0;
        if (i == 8) {
            D_1F800000.view.effect.params[2] = 0;
        } else {
            D_1F800000.view.effect.params[2] = (i + 2) * 409;
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

/* func_801EF69C */
#include "overlays/bmagic/BMagic_AllocEffect.h"
