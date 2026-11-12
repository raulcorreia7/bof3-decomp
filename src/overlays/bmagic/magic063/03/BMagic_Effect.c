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

INCLUDE_ASM(func_801EECF8);

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
            val                                  = ((i >> 1) & 0x70) + (rand() & 0xF) + 1;
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
    g_BMagicOrbitWork->unk_10 = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbitWork->angle) * g_BMagicOrbitWork->radius);
    g_BMagicOrbitWork->unk_14 = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbitWork->angle) * g_BMagicOrbitWork->radius);
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
    off    = FIELD(u16, g_BMagicOrbitWork, 0xE) + 0x800;
    rot.vz = (((g_BMagicOrbitWork)->unk_03 << 7) - off) & 0xFFF;
    pos.vx = ((g_BMagicOrbitWork)->unk_10 >> 9) - 0x4000;
    pos.vy = ((g_BMagicOrbitWork)->unk_14 >> 9) - 0x4000;
    pos.vz = -FIELD(s16, g_BMagicOrbitWork, 0x1A) / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

INCLUDE_ASM(func_801EFA5C);

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
    g_BMagicOrbitWork->angle  = (g_BMagicOrbitWork->angle + 0x20) & 0xFFF;
    g_BMagicOrbitWork->unk_10 = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbitWork->angle) << 5);
    g_BMagicOrbitWork->unk_14 = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbitWork->angle) << 5);
    g_BMagicOrbitWork->unk_09 += 2;
    g_BMagicOrbitWork->unk_0B++;
    if (g_BMagicOrbitWork->unk_09 == 0x10) {
        g_BMagicOrbitWork->header.step++;
    }
}

MATCH void func_801EFFE8(void) {
    g_BMagicOrbitWork->angle  = (g_BMagicOrbitWork->angle + 0x20) & 0xFFF;
    g_BMagicOrbitWork->unk_10 = g_BattleEffectBattler->pos.x.fixed + (rsin(g_BMagicOrbitWork->angle) << 5);
    g_BMagicOrbitWork->unk_14 = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbitWork->angle) << 5);
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
    g_BMagicOrbitWork->unk_10 = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbitWork->angle) << 5);
    g_BMagicOrbitWork->unk_14 = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbitWork->angle) << 5);
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
    g_BMagicOrbitWork->unk_10 = g_BattleEffectBattler->pos.x.fixed + (rsin((s16)g_BMagicOrbitWork->angle) << 5);
    g_BMagicOrbitWork->unk_14 = g_BattleEffectBattler->pos.y.fixed + (rcos((s16)g_BMagicOrbitWork->angle) << 5);
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
