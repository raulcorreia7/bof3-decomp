#include "magic048_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* work;
    u32          slot;
    u8           i;

    g_Task->param.unk_0B = 0;
    g_Task->facing       = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->unk_09 = 10;
    g_Task->header.mode += 1;
    i = 0;
    do {
        slot                               = Battle_AllocEffect(1, 30) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = ((i ^ 0xF) - 3) * 8;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_08       = g_Task->facing;
        g_Task->param.unk_0B += 1;
        i++;
    } while (i < 12);
}

#include "overlays/bmagic/Effect_CountDownTimerQueueEffect.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE70 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEB4(void) {
    SYS_DISPATCH_BYTE(D_801EF81C, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        func_801EF5C8();
        func_801EF234();
        PopMatrix();
    }
}

MATCH s32 func_801EEF3C(void) {
    PartyMember* work;
    FAKE_REG(s32, scroll, "a1"); /* FAKE: pins the scroll offset to retail a1; the best plain form differs in 6 instructions (scroll and battler registers). */
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0) {
        func_801EF6A0();
        g_Task->unk_0C = 0x10000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
        g_Task->unk_0C      = 0x80000;
        g_Task->unk_10      = 0;
        func_801DD350(g_Task);
        work = g_Task;
        work->unk_0C += g_AreaScrollTargetX;
        FAKE_BARRIER(); /* FAKE: keeps the height read below the velocity store. */
        work->unk_14 = COORD_INT(work->pos.z) + 0x100;
        scroll       = g_AreaScrollTargetY;
        work->unk_10 += scroll;
        COORD_INT(work->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 0x100;
        work->unk_09           = 0;
        g_Task->timer          = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF05C(void) {
    VECTOR pos;

    g_Task->unk_09 += 1;
    pos.vx = (g_Task->unk_0C >> 9) - AREA_CELL_ORIGIN;
    pos.vy = (g_Task->unk_10 >> 9) - AREA_CELL_ORIGIN;
    pos.vz = g_Task->unk_14 >> 1;
    func_800AF3A0(pos, 0x10);
    if (g_Task->timer != 16) {
        g_Task->timer += 1;
    }
    if (func_800AF6B8(g_Task->unk_0C, g_Task->unk_10, g_Task->pos.z.fixed, 0x60000) != 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF158(void) {
    VECTOR pos;
    u8     count;

    pos.vx = (g_Task->unk_0C >> 9) - AREA_CELL_ORIGIN;
    pos.vy = (g_Task->unk_10 >> 9) - AREA_CELL_ORIGIN;
    pos.vz = g_Task->unk_14 >> 1;
    func_800AF3A0(pos, 0x10);
    g_Task->unk_09 = g_Task->unk_09 + 1;
    count          = g_Task->timer - 1;
    g_Task->timer  = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

/* Draw the magic048 ring as 32 shaded quads standing between two radii round the effect,
 * tinted at the outer edge by the timer; past a radius of 9 the outer edge flickers. */
MATCH void func_801EF234(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[1] = g_Task->unk_09 * 4;
    D_1F800000.view.effect.params[2] = g_Task->unk_09 * 6;
    if (g_Task->unk_09 >= 9) {
        D_1F800000.view.effect.params[2] += rand() & 0xF;
    }
    D_1F800000.view.effect.params[3]     = g_Task->timer * 8;
    D_1F800000.view.effect.params[4]     = g_Task->timer * 4;
    /* FAKE: the first corner through the scratchpad view keeps the base register on the second corner, as retail does; through D_1F800014 it moves to the first. */
    D_1F800000.view.effect.vectors[0].vx = 0;
    D_1F800014[1].vx                     = 0;
    D_1F800014[1].vy                     = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[2]);
    D_1F800014[1].vz                     = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[2]);
    D_1F800014[2].vx                     = 0;
    D_1F800014[3].vx                     = 0;
    D_1F800014[3].vy                     = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);
    D_1F800014[3].vz                     = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);
    for (i = 1; i <= 32; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[0].vz = D_1F800014[1].vz;
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 7), D_1F800000.view.effect.params[2]);
        D_1F800014[1].vz = FIXED_MUL(rsin(i << 7), D_1F800000.view.effect.params[2]);
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[2].vz = D_1F800014[3].vz;
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 7), D_1F800000.view.effect.params[1]);
        D_1F800014[3].vz = FIXED_MUL(rsin(i << 7), D_1F800000.view.effect.params[1]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[4]);
        setRGB3(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[4]);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801EF5C8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = ratan2(g_Task->unk_10 - g_Task->pos.y.fixed, g_Task->unk_0C - g_Task->pos.x.fixed) & ANGLE_MASK;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

MATCH void func_801EF6A0(void) {
    u8   i;
    s32* sum;
    s32* enemy_sum;
    s32* party_sum;

    /* The effect takes the mean z of the unblocked battlers on the targeted side; the scratchpad keeps the sum and the count. */
    sum                              = &D_1F800000.view.scenario.math_00;
    D_1F800000.view.scenario.math_04 = 0;
    *sum                             = 0;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        i         = 0;
        enemy_sum = sum;
        for (; i < 8; i++) {
            if (!Battle_SlotIsBlocked((u8)(i + BATTLE_PARTY_CHARACTERS_COUNT))) {
                enemy_sum[0] += COORD_INT(g_BattleEnemyBattlers[i].pos.z);
                enemy_sum[1] += 1;
            }
        }
    } else {
        i         = 0;
        party_sum = sum;
        for (; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            if (!Battle_SlotIsBlocked(i)) {
                party_sum[0] += COORD_INT(g_Game.members[i].pos.z);
                party_sum[1] += 1;
            }
        }
    }
    COORD_INT(g_Task->pos.z) = D_1F800000.view.scenario.math_00 / D_1F800000.view.scenario.math_04;
}
