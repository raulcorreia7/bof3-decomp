#include "magic063_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    PartyMember* saved;
    PartyMember* swap;
    s32          count;

    BMagic_DispatchTaskPair(func_801EECF8, Effect_StartOnZeroTick);
    count = 0;
    do {
        if (D_801F0454[(u8)count << 5] & 0x1) {
            saved                 = g_BattleEffectBattler;
            swap                  = FIELD(PartyMember*, D_801F0470, (u8)count << 5);
            g_BMagicOrbitWork     = D_801F0454 + ((u8)count << 5);
            g_BattleEffectBattler = swap;
            func_801EF340();
            g_BattleEffectBattler = saved;
        }
        count += 1;
    } while ((u8)count < 96);
}

MATCH void func_801EECF8(void) {
    u8 slot;
    u8 i;
    u8 battler;

    for (i = 0; i < 0x60; i++) {
        D_801F0454[i << 5]       = 0;
        D_801F0454[(i << 5) + 1] = 0;
        D_801F0454[(i << 5) + 2] = 0;
    }
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 8; i++) {
        battler = i + BATTLE_PARTY_CHARACTERS_COUNT;
        if (!Battle_SlotIsBlocked(battler) && g_Battle.active_battler != i + BATTLE_PARTY_CHARACTERS_COUNT) {
            slot                               = Battle_AllocEffect(1, 0x68);
            g_BattleEffects[slot].target.party = g_Task;
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_04       = battler;
            g_Task->param.unk_0B += 1;
        }
    }
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        battler = i;
        if (!Battle_SlotIsBlocked(battler) && g_Battle.active_battler != battler) {
            slot                               = Battle_AllocEffect(1, 0x68);
            g_BattleEffects[slot].target.party = g_Task;
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_04       = i;
            g_Task->param.unk_0B += 1;
        }
    }
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEF30 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF74(void) {
    Magic063Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

INCLUDE_ASM(func_801EEFE4);

MATCH void func_801EF110(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        if (g_BattleEffectBattler->param.unk_0B == 1) {
            g_Task->header.step = 3;
        } else {
            g_BattleEffectBattler->param.unk_0B -= 1;
            g_Task->header.step += 1;
        }
    }
}

MATCH void func_801EF190(void) {
    if (g_Task->param.unk_0B == 0) {
        func_801E5988();
    }
}

MATCH void func_801EF1C8(void) {
    u8           i;
    u8           slot;
    u8           val;
    s32          off;
    PartyMember* task;

    if (g_Task->param.unk_0B != 0) {
        return;
    }
    i = 0;
    do {
        slot = func_801F0354();
        if (slot != GAME_NONE) {
            off                                  = slot << 5;
            task                                 = g_Task;
            D_801F0454[off + 1]                  = 0;
            D_801F0454[off + 4]                  = i;
            FIELD(PartyMember*, D_801F0470, off) = task;
            val                                  = ((i >> 1) & 0x70) + (RANDOM_MASK(0xF)) + 1;
            D_801F0454[off + 10]                 = val;
            D_801F0454[off + 8]                  = 0x40 - val;
            g_Task->param.unk_0B++;
        }
        i++;
    } while (i < 0x5C);
    SND_QueueSelectionFx(0x101);
    SND_QueueSelectionFx(0x102);
    g_Task->header.step++;
}

#include "overlays/bmagic/Effect_FinishOnZeroTick.h"

MATCH void func_801EF340(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 1, 1, g_BMagicOrbitWork);
}

MATCH void func_801EF384(void) {
    SYS_DISPATCH_BYTE(D_801F040C, g_BMagicOrbitWork->header.step);
    if (g_BMagicOrbitWork->header.flags != 0 && g_BMagicOrbitWork->header.step != 0) {
        func_801EF994();
        func_801EFA5C();
        PopMatrix();
    }
}

/* func_801EF40C */
#include "overlays/bmagic/Effect_StartOrbit.h"

MATCH void func_801EF5CC(void) {
    s32 threshold;

    g_BMagicOrbitWork->radius -= 2;
    g_BMagicOrbitWork->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbitWork->angle) * g_BMagicOrbitWork->radius);
    g_BMagicOrbitWork->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbitWork->angle) * g_BMagicOrbitWork->radius);
    g_BMagicOrbitWork->unk_0B++;
    if (g_BMagicOrbitWork->unk_09 < 0x10) {
        g_BMagicOrbitWork->unk_09 += 2;
    }
    threshold = ((g_BMagicOrbitWork->unk_04 >> 5) * 8) + 0x20;
    if (g_BMagicOrbitWork->radius <= threshold) {
        g_BMagicOrbitWork->header.step++;
        if (g_BMagicOrbitWork->unk_04 == 0) {
            Battle_ApplyDamageFlags(g_BattleEffectBattler->unk_04, 0x10);
        }
    }
}

/* func_801EF704 */
#include "overlays/bmagic/Effect_StepOrbit.h"

MATCH void func_801EF880(void) {
    BMAGIC_ORBIT_BATTLER_AND_CLEAR(func_801F03B0);
}

MATCH void func_801EF994(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    s32     off;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    off    = g_BMagicOrbitWork->angle + 0x800;
    rot.vz = ((g_BMagicOrbitWork->unk_03 << 7) - off) & 0xFFF;
    pos.vx = (g_BMagicOrbitWork->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_BMagicOrbitWork->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -COORD_INT(g_BMagicOrbitWork->pos.z) / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

/* Draws the four sparkle wedges round the orbiting effect: each a shaded triangle from
 * the centre to two corners from the wedge tables, lifted by a sine of the effect tick. */
MATCH void func_801EFA5C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    SVECTOR* vec;
    u8       i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
    Area_AddCellPrim(g_BMagicOrbitWork->pos.x.fixed, g_BMagicOrbitWork->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[5] = g_BMagicOrbitWork->timer_05 * g_BMagicOrbitWork->unk_09;
    D_1F800000.view.effect.params[6] = g_BMagicOrbitWork->timer_06 * g_BMagicOrbitWork->unk_09;
    D_1F800000.view.effect.params[7] = g_BMagicOrbitWork->timer_07 * g_BMagicOrbitWork->unk_09;
    /* FAKE: the vector base in a local makes the centre vector the register base of the corner writes. */
    vec                              = D_1F800014;
    D_1F800014[0].vz                 = 0;
    D_1F800014[0].vy                 = 0;
    vec[0].vx                        = 0;
    for (i = 0; i < 4; i++) {
        D_1F800000.view.effect.params[0] = D_801F041C[i];
        D_1F800000.view.effect.params[1] = D_801F0424[i];
        D_1F800000.view.effect.params[2] = D_801F042C[i];
        D_1F800000.view.effect.params[3] = D_801F0434[i];
        D_1F800000.view.effect.params[4] = ((g_BMagicOrbitWork->unk_0B + D_801F043C[i]) & 0xF) << 8;
        prim                             = GFX_BeginPolyG3(1);
        D_1F800014[1].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[1]);
        D_1F800014[2].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[1]);
        D_1F800014[2].vz = D_1F800014[1].vz = (u32)rsin(D_1F800000.view.effect.params[4]) >> 7;
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[5]);
        setRGB1(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[7]);
        setRGB2(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[7]);
        Area_AddCellPrim(g_BMagicOrbitWork->pos.x.fixed, g_BMagicOrbitWork->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

MATCH void func_801EFD7C(void) {
    SYS_DISPATCH_BYTE(D_801F0440, g_BMagicOrbitWork->header.step);
    if (g_BMagicOrbitWork->header.flags != 0 && g_BMagicOrbitWork->header.step != 0) {
        func_801EF994();
        func_801EFA5C();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EFE04);

MATCH void func_801EFF18(void) {
    g_BMagicOrbitWork->angle       = (g_BMagicOrbitWork->angle + 0x20) & 0xFFF;
    g_BMagicOrbitWork->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbitWork->angle) << 5);
    g_BMagicOrbitWork->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbitWork->angle) << 5);
    g_BMagicOrbitWork->unk_09 += 2;
    g_BMagicOrbitWork->unk_0B++;
    if (g_BMagicOrbitWork->unk_09 == 0x10) {
        g_BMagicOrbitWork->header.step++;
    }
}

MATCH void func_801EFFE8(void) {
    g_BMagicOrbitWork->angle       = (g_BMagicOrbitWork->angle + 0x20) & 0xFFF;
    g_BMagicOrbitWork->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(g_BMagicOrbitWork->angle) << 5);
    g_BMagicOrbitWork->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbitWork->angle) << 5);
    g_BMagicOrbitWork->unk_0B++;
    if (--g_BMagicOrbitWork->unk_0A == 0) {
        if (g_BattleEffectBattler->header.step == 3) {
            g_BMagicOrbitWork->unk_0A = 0x40;
        } else {
            g_BMagicOrbitWork->unk_0A = 1;
        }
        g_BMagicOrbitWork->header.step++;
    }
}

MATCH void func_801F00F0(void) {
    if (g_BattleEffectBattler->header.step == 3) {
        g_BMagicOrbitWork->unk_0B += 4;
        g_BMagicOrbitWork->angle = (g_BMagicOrbitWork->angle + 0x40) & 0xFFF;
    } else {
        g_BMagicOrbitWork->unk_0B += 1;
        g_BMagicOrbitWork->angle = (g_BMagicOrbitWork->angle + 0x20) & 0xFFF;
    }
    g_BMagicOrbitWork->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbitWork->angle) << 5);
    g_BMagicOrbitWork->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbitWork->angle) << 5);
    if (--g_BMagicOrbitWork->unk_0A == 0) {
        g_BMagicOrbitWork->header.step++;
    }
}

MATCH void func_801F0220(void) {
    if (g_BattleEffectBattler->header.step == 3) {
        g_BMagicOrbitWork->unk_0B += 2;
        g_BMagicOrbitWork->angle = (g_BMagicOrbitWork->angle + 0x40) & 0xFFF;
    } else {
        g_BMagicOrbitWork->unk_0B += 1;
        g_BMagicOrbitWork->angle = (g_BMagicOrbitWork->angle + 0x20) & 0xFFF;
    }
    g_BMagicOrbitWork->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbitWork->angle) << 5);
    g_BMagicOrbitWork->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbitWork->angle) << 5);
    if (--g_BMagicOrbitWork->unk_09 == 0) {
        g_BattleEffectBattler->param.unk_0B--;
        func_801F03B0();
    }
}

MATCH u32 func_801F0354(void) {
    u8 index;

    for (index = 0u; index < 96; index++) {
        if ((D_801F0454[index << 5] & 0x1) == 0) {
            D_801F0454[index << 5] |= 1;
            return index;
        }
    }
    return 0xFFu;
}

MATCH void func_801F03B0(void) {
    g_BMagicOrbitWork->header.flags = 0;
    g_BMagicOrbitWork->header.mode  = 0;
    g_BMagicOrbitWork->header.step  = 0;
    g_BMagicOrbitWork->unk_03       = 0;
    g_BMagicOrbitWork->unk_04       = 0;
}
