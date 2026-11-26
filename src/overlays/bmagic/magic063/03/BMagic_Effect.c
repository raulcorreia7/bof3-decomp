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
            swap                  = Magic063ClaimTask((u8)count << 5);
            g_BMagicOrbit         = D_801F0454 + ((u8)count << 5);
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
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->header.mode += 1;
    for (i = 0; i < 8; i++) {
        battler = i + BATTLE_PARTY_CHARACTERS_COUNT;
        if (!Battle_SlotIsBlocked(battler) && g_Battle.active_battler != i + BATTLE_PARTY_CHARACTERS_COUNT) {
            slot                               = Battle_AllocEffect(1, 104);
            g_BattleEffects[slot].target.party = TASK(PartyMember);
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_04       = battler;
            TASK(PartyMember)->param.unk_0B += 1;
        }
    }
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        battler = i;
        if (!Battle_SlotIsBlocked(battler) && g_Battle.active_battler != battler) {
            slot                               = Battle_AllocEffect(1, 104);
            g_BattleEffects[slot].target.party = TASK(PartyMember);
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_04       = i;
            TASK(PartyMember)->param.unk_0B += 1;
        }
    }
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EEF30 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF74(void) {
    Magic063Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801EEFE4(void) {
    PartyMember* record;
    PartyMember* target;
    PartyMember* claims;
    PartyMember* count;
    u8           index;
    u8           claimed;
    s32          offset;
    u32          random;

    index = TASK(PartyMember)->unk_04;
    if (index < BATTLE_PARTY_CHARACTERS_COUNT) {
        record = &g_Game.members[index];
    } else {
        record = (PartyMember*)&g_BattleEnemies[index * BATTLE_ENEMY_STRIDE];
    }
    target                          = TASK(PartyMember);
    target->pos.x.fixed             = record->pos.x.fixed;
    target->pos.y.fixed             = record->pos.y.fixed;
    target->pos.z.fixed             = record->pos.z.fixed + TO_COORD(512);
    random                          = RANDOM_MASK(0xF);
    TASK(PartyMember)->unk_09       = random + 1;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.step += 1;
    claimed = func_801F0354();
    if (claimed != GAME_NONE) {
        offset                                  = claimed << 5;
        claims                                  = TASK(PartyMember);
        D_801F0454[offset + 1]                  = 1;
        count                                   = TASK(PartyMember);
        FIELD(PartyMember*, D_801F0470, offset) = claims;
        count->param.unk_0B++;
    }
}

MATCH void func_801EF110(void) {
    u8 timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        if (g_BattleEffectBattler->param.unk_0B == 1) {
            TASK(PartyMember)->header.step = 3;
        } else {
            g_BattleEffectBattler->param.unk_0B -= 1;
            TASK(PartyMember)->header.step += 1;
        }
    }
}

MATCH void func_801EF190(void) {
    if (TASK(PartyMember)->param.unk_0B == 0) {
        Effect_Reset();
    }
}

MATCH void func_801EF1C8(void) {
    u8           i;
    u8           slot;
    u8           val;
    s32          off;
    PartyMember* task;

    if (TASK(PartyMember)->param.unk_0B != 0) {
        return;
    }
    i = 0;
    do {
        slot = func_801F0354();
        if (slot != GAME_NONE) {
            off                                  = slot << 5;
            task                                 = TASK(PartyMember);
            D_801F0454[off + 1]                  = 0;
            D_801F0454[off + 4]                  = i;
            FIELD(PartyMember*, D_801F0470, off) = task;
            val                                  = ((i >> 1) & 0x70) + (RANDOM_MASK(0xF)) + 1;
            D_801F0454[off + 10]                 = val;
            D_801F0454[off + 8]                  = 0x40 - val;
            TASK(PartyMember)->param.unk_0B++;
        }
        i++;
    } while (i < 0x5C);
    SND_SEQueueSelection(0x101);
    SND_SEQueueSelection(0x102);
    TASK(PartyMember)->header.step++;
}

#include "overlays/bmagic/shared/Effect_EndOnZeroTick.h"

MATCH void func_801EF340(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 1, 1, g_BMagicOrbit);
}

MATCH void func_801EF384(void) {
    SYS_DISPATCH_BYTE(D_801F040C, g_BMagicOrbit->header.step);
    if (g_BMagicOrbit->header.flags != 0 && g_BMagicOrbit->header.step != 0) {
        Effect_SetOrbitModelMatrix();
        func_801EFA5C();
        PopMatrix();
    }
}

/* func_801EF40C */
#include "overlays/bmagic/shared/Effect_StartOrbit.h"

MATCH void func_801EF5CC(void) {
    s32 threshold;

    g_BMagicOrbit->radius -= 2;
    g_BMagicOrbit->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbit->angle) * g_BMagicOrbit->radius);
    g_BMagicOrbit->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbit->angle) * g_BMagicOrbit->radius);
    g_BMagicOrbit->unk_0B++;
    if (g_BMagicOrbit->unk_09 < 0x10) {
        g_BMagicOrbit->unk_09 += 2;
    }
    threshold = ((g_BMagicOrbit->unk_04 >> 5) * 8) + 0x20;
    if (g_BMagicOrbit->radius <= threshold) {
        g_BMagicOrbit->header.step++;
        if (g_BMagicOrbit->unk_04 == 0) {
            Battle_ApplyDamageFlags(g_BattleEffectBattler->unk_04, 0x10);
        }
    }
}

/* func_801EF704 */
#include "overlays/bmagic/shared/Effect_StepOrbit.h"

MATCH void func_801EF880(void) {
    BMAGIC_ORBIT_BATTLER_AND_CLEAR(func_801F03B0);
}

/* func_801EF994 */
#include "overlays/bmagic/shared/Effect_SetOrbitModelMatrix.h"

/* Draws the four sparkle wedges round the orbiting effect: each a shaded triangle from
 * the centre to two corners from the wedge tables, lifted by a sine of the effect tick. */
MATCH void func_801EFA5C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    SVECTOR* vec;
    u8       i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(g_BMagicOrbit->pos.x.fixed, g_BMagicOrbit->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[5] = g_BMagicOrbit->timer_05 * g_BMagicOrbit->unk_09;
    g_ScratchPad.cells.halves[6] = g_BMagicOrbit->timer_06 * g_BMagicOrbit->unk_09;
    g_ScratchPad.cells.halves[7] = g_BMagicOrbit->timer_07 * g_BMagicOrbit->unk_09;
    /* FAKE: the vector base in a local makes the centre vector the register base of the corner writes. */
    vec                          = g_ScratchPadVectors;
    g_ScratchPadVectors[0].vz    = 0;
    g_ScratchPadVectors[0].vy    = 0;
    vec[0].vx                    = 0;
    for (i = 0; i < 4; i++) {
        g_ScratchPad.cells.halves[0] = D_801F041C[i];
        g_ScratchPad.cells.halves[1] = D_801F0424[i];
        g_ScratchPad.cells.halves[2] = D_801F042C[i];
        g_ScratchPad.cells.halves[3] = D_801F0434[i];
        g_ScratchPad.cells.halves[4] = ((g_BMagicOrbit->unk_0B + D_801F043C[i]) & 0xF) << 8;
        prim                         = GFX_BeginPolyG3(1);
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[1]),
                  g_ScratchPadVectors[1].vz = (u32)rsin(g_ScratchPad.cells.halves[4]) >> 7);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5]);
        setRGB1(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        setRGB2(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        Area_CellAddPrim(g_BMagicOrbit->pos.x.fixed, g_BMagicOrbit->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

MATCH void func_801EFD7C(void) {
    SYS_DISPATCH_BYTE(D_801F0440, g_BMagicOrbit->header.step);
    if (g_BMagicOrbit->header.flags != 0 && g_BMagicOrbit->header.step != 0) {
        Effect_SetOrbitModelMatrix();
        func_801EFA5C();
        PopMatrix();
    }
}

MATCH void func_801EFE04(void) {
    g_BMagicOrbit->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(0) << 5);
    g_BMagicOrbit->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos(0) << 5);
    g_BMagicOrbit->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    g_BMagicOrbit->timer_05    = (rand() & 7) + 5;
    g_BMagicOrbit->timer_06    = (rand() & 7) + 5;
    g_BMagicOrbit->timer_07    = (rand() & 7) + 5;
    g_BMagicOrbit->angle       = 0;
    g_BMagicOrbit->unk_03      = 7;
    g_BMagicOrbit->unk_09      = 0;
    g_BMagicOrbit->unk_0A      = 0x40;
    g_BMagicOrbit->unk_0B      = rand();
    g_BMagicOrbit->header.step += 1;
}

MATCH void func_801EFF18(void) {
    g_BMagicOrbit->angle       = (g_BMagicOrbit->angle + 0x20) & ANGLE_MASK;
    g_BMagicOrbit->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbit->angle) << 5);
    g_BMagicOrbit->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbit->angle) << 5);
    g_BMagicOrbit->unk_09 += 2;
    g_BMagicOrbit->unk_0B++;
    if (g_BMagicOrbit->unk_09 == 0x10) {
        g_BMagicOrbit->header.step++;
    }
}

MATCH void func_801EFFE8(void) {
    g_BMagicOrbit->angle       = (g_BMagicOrbit->angle + 0x20) & ANGLE_MASK;
    g_BMagicOrbit->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(g_BMagicOrbit->angle) << 5);
    g_BMagicOrbit->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbit->angle) << 5);
    g_BMagicOrbit->unk_0B++;
    if (--g_BMagicOrbit->unk_0A == 0) {
        if (g_BattleEffectBattler->header.step == 3) {
            g_BMagicOrbit->unk_0A = 0x40;
        } else {
            g_BMagicOrbit->unk_0A = 1;
        }
        g_BMagicOrbit->header.step++;
    }
}

MATCH void func_801F00F0(void) {
    if (g_BattleEffectBattler->header.step == 3) {
        g_BMagicOrbit->unk_0B += 4;
        g_BMagicOrbit->angle = (g_BMagicOrbit->angle + 0x40) & ANGLE_MASK;
    } else {
        g_BMagicOrbit->unk_0B += 1;
        g_BMagicOrbit->angle = (g_BMagicOrbit->angle + 0x20) & ANGLE_MASK;
    }
    g_BMagicOrbit->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbit->angle) << 5);
    g_BMagicOrbit->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbit->angle) << 5);
    if (--g_BMagicOrbit->unk_0A == 0) {
        g_BMagicOrbit->header.step++;
    }
}

MATCH void func_801F0220(void) {
    if (g_BattleEffectBattler->header.step == 3) {
        g_BMagicOrbit->unk_0B += 2;
        g_BMagicOrbit->angle = (g_BMagicOrbit->angle + 0x40) & ANGLE_MASK;
    } else {
        g_BMagicOrbit->unk_0B += 1;
        g_BMagicOrbit->angle = (g_BMagicOrbit->angle + 0x20) & ANGLE_MASK;
    }
    g_BMagicOrbit->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbit->angle) << 5);
    g_BMagicOrbit->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbit->angle) << 5);
    if (--g_BMagicOrbit->unk_09 == 0) {
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
    g_BMagicOrbit->header.flags = 0;
    g_BMagicOrbit->header.mode  = 0;
    g_BMagicOrbit->header.step  = 0;
    g_BMagicOrbit->unk_03       = 0;
    g_BMagicOrbit->unk_04       = 0;
}
