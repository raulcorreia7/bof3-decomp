#include "magic106_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved;
    PartyMember* swap;
    s32          count;

    BMagic_DispatchTaskPair(func_801EECE4, Effect_PlayOnZeroTick);
    count = 0;
    do {
        if (D_801EF9F8[(u8)count << 5] & 0x1) {
            saved                 = g_BattleEffectBattler;
            swap                  = FIELD(PartyMember*, D_801EFA14, (u8)count << 5);
            g_BMagicOrbit         = D_801EF9F8 + ((u8)count << 5);
            g_BattleEffectBattler = swap;
            func_801EEEE0();
            g_BattleEffectBattler = saved;
        }
        count += 1;
    } while ((u8)count < 96);
}

MATCH void func_801EECE4(void) {
    PartyMember* work;
    u8           i;
    u32          row;
    u8           growth;
    u8           slot;

    for (i = 0; i < 96; i++) {
        D_801EF9F8[i << 5]       = 0;
        D_801EF9F8[(i << 5) + 1] = 0;
        D_801EF9F8[(i << 5) + 2] = 0;
    }
    work              = g_Task;
    work->pos.x.fixed = g_Battle.selected_actor->pos.x.fixed;
    /* FAKE: retail re-reads the selected actor for the next copy. */
    FAKE_BARRIER();
    work->pos.y.fixed = g_Battle.selected_actor->pos.y.fixed;
    /* FAKE: retail re-reads the selected actor for the next copy. */
    FAKE_BARRIER();
    work->pos.z.fixed  = g_Battle.selected_actor->pos.z.fixed + TO_COORD(256);
    work->param.unk_0B = 0;
    g_Task->unk_09     = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 96; i++) {
        slot                  = func_801EF914();
        row                   = slot << 5;
        D_801EFA14[slot << 3] = g_Task;
        D_801EF9F8[row + 1]   = 0;
        D_801EF9F8[row + 4]   = i;
        growth                = ((i >> 1) & 0x70) + (rand() & 0xF) + 1;
        D_801EF9F8[row + 10]  = growth;
        D_801EF9F8[row + 8]   = 0x40 - growth;
        g_Task->param.unk_0B += 1;
    }
    SND_QueueSelectionEffect(0x100);
    SND_QueueSelectionEffect(0x101);
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEE0(void) {
    BMagicOrbit* work;

    work = g_BMagicOrbit;
    D_801EF9C0[work->header.mode]();
}

MATCH void func_801EEF24(void) {
    SYS_DISPATCH_BYTE(D_801EF9C4, g_BMagicOrbit->header.step);
    if (g_BMagicOrbit->header.flags != 0 && g_BMagicOrbit->header.step != 0) {
        func_801EF52C();
        func_801EF5F4();
        PopMatrix();
    }
}

/* func_801EEFAC */
#include "overlays/bmagic/Effect_StartOrbit.h"

MATCH void func_801EF16C(void) {
    s32 threshold;

    g_BMagicOrbit->radius -= 2;
    g_BMagicOrbit->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin((s16)g_BMagicOrbit->angle) * g_BMagicOrbit->radius;
    g_BMagicOrbit->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos((s16)g_BMagicOrbit->angle) * g_BMagicOrbit->radius;
    g_BMagicOrbit->unk_0B++;
    if (g_BMagicOrbit->unk_09 < 16) {
        g_BMagicOrbit->unk_09 += 2;
    }
    threshold = ((g_BMagicOrbit->unk_04 >> 5) * 8) + 0x20;
    if (g_BMagicOrbit->radius <= threshold) {
        g_BMagicOrbit->header.step++;
        if (g_BMagicOrbit->unk_04 == 0) {
            Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        }
    }
}

/* func_801EF29C */
#include "overlays/bmagic/Effect_StepOrbit.h"

MATCH void func_801EF418(void) {
    BMAGIC_ORBIT_BATTLER_AND_CLEAR(func_801EF970);
}

MATCH void func_801EF52C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    s32     off;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    off    = g_BMagicOrbit->angle + 0x800;
    rot.vz = ((g_BMagicOrbit->unk_03 << 7) - off) & ANGLE_MASK;
    pos.vx = (g_BMagicOrbit->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vy = (g_BMagicOrbit->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vz = -COORD_INT(g_BMagicOrbit->pos.z) / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

MATCH void func_801EF5F4(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    u8       i;
    s32      tpage;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_BMagicOrbit->pos.x.fixed, g_BMagicOrbit->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[5]     = g_BMagicOrbit->timer_05 * g_BMagicOrbit->unk_09;
    D_1F800000.view.effect.params[6]     = g_BMagicOrbit->timer_06 * g_BMagicOrbit->unk_09;
    D_1F800000.view.effect.params[7]     = g_BMagicOrbit->timer_07 * g_BMagicOrbit->unk_09;
    /* FAKE: retail stores vz and vy of the first corner through the scratch view, and only vx through D_1F800014. */
    D_1F800000.view.effect.vectors[0].vz = 0;
    D_1F800000.view.effect.vectors[0].vy = 0;
    D_1F800014[0].vx                     = 0;
    for (i = 0; i < 4; i++) {
        D_1F800000.view.effect.params[0] = D_801EF9D4[i];
        D_1F800000.view.effect.params[1] = D_801EF9DC[i];
        D_1F800000.view.effect.params[2] = D_801EF9E4[i];
        D_1F800000.view.effect.params[3] = D_801EF9EC[i];
        D_1F800000.view.effect.params[4] = ((g_BMagicOrbit->unk_0B + D_801EF9F4[i]) & 0xF) << 8;
        prim                             = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[1].vx = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vx = FIXED_MUL(rsin(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[1]);
        D_1F800014[2].vy = FIXED_MUL(rcos(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[1]);
        D_1F800014[2].vz = D_1F800014[1].vz = (u32)rsin(D_1F800000.view.effect.params[4]) >> 7;
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[5]);
        setRGB1(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[7]);
        setRGB2(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[7]);
        Area_AddCellPrim(g_BMagicOrbit->pos.x.fixed, g_BMagicOrbit->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

MATCH u32 func_801EF914(void) {
    u8 index;

    for (index = 0u; index < 96; index++) {
        if ((D_801EF9F8[index << 5] & 0x1) == 0) {
            D_801EF9F8[index << 5] |= 1;
            return index;
        }
    }
    return 0xFFu;
}

MATCH void func_801EF970(void) {
    g_BMagicOrbit->header.flags = 0;
    g_BMagicOrbit->header.mode  = 0;
    g_BMagicOrbit->header.step  = 0;
    g_BMagicOrbit->unk_03       = 0;
    g_BMagicOrbit->unk_04       = 0;
}
