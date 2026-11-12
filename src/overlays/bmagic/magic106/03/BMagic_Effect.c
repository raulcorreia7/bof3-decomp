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
            g_BMagicOrbitWork     = D_801EF9F8 + ((u8)count << 5);
            g_BattleEffectBattler = swap;
            func_801EEEE0();
            g_BattleEffectBattler = saved;
        }
        count += 1;
    } while ((u8)count < 96);
}

INCLUDE_ASM(func_801EECE4);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEE0(void) {
    BMagicOrbitWork* work;

    work = g_BMagicOrbitWork;
    D_801EF9C0[work->header.mode]();
}

MATCH void func_801EEF24(void) {
    SYS_DISPATCH_BYTE(D_801EF9C4, g_BMagicOrbitWork->header.step);
    if (g_BMagicOrbitWork->header.flags != 0 && g_BMagicOrbitWork->header.step != 0) {
        func_801EF52C();
        func_801EF5F4();
        PopMatrix();
    }
}

/* func_801EEFAC */
#include "overlays/bmagic/Effect_StartOrbit.h"

MATCH void func_801EF16C(void) {
    s32 threshold;

    g_BMagicOrbitWork->radius -= 2;
    g_BMagicOrbitWork->unk_10 = g_BattleEffectBattler->pos.x.fixed + rsin((s16)g_BMagicOrbitWork->angle) * g_BMagicOrbitWork->radius;
    g_BMagicOrbitWork->unk_14 = g_BattleEffectBattler->pos.y.fixed + rcos((s16)g_BMagicOrbitWork->angle) * g_BMagicOrbitWork->radius;
    g_BMagicOrbitWork->unk_0B++;
    if (g_BMagicOrbitWork->unk_09 < 16) {
        g_BMagicOrbitWork->unk_09 += 2;
    }
    threshold = ((g_BMagicOrbitWork->unk_04 >> 5) * 8) + 0x20;
    if (g_BMagicOrbitWork->radius <= threshold) {
        g_BMagicOrbitWork->header.step++;
        if (g_BMagicOrbitWork->unk_04 == 0) {
            Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        }
    }
}

/* func_801EF29C */
#include "overlays/bmagic/Effect_StepOrbit.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EF418(void) {
    u8  timer;
    u8  spin;
    u8  counter;
    s32 cosTerm;
    s32 angle;

    angle                               = (FIELD(u16, g_BMagicOrbitWork, 0xE) + 0x40) & 0xFFF;
    FIELD(u16, g_BMagicOrbitWork, 0xE)  = angle;
    FIELD(s32, g_BMagicOrbitWork, 0x10) = g_BattleEffectBattler->pos.x.fixed + rsin(angle) * FIELD(s16, g_BMagicOrbitWork, 0xC);
    cosTerm                             = rcos((s16)FIELD(u16, g_BMagicOrbitWork, 0xE)) * FIELD(s16, g_BMagicOrbitWork, 0xC);
    counter                             = FIELD(u8, g_BMagicOrbitWork, 0xB) + 1;
    spin                                = FIELD(u8, g_BMagicOrbitWork, 0xA);
    FIELD(u16, g_BMagicOrbitWork, 0x1A) = (u16)(FIELD(u16, g_BMagicOrbitWork, 0x1A) + spin);
    FIELD(u8, g_BMagicOrbitWork, 0xB)   = counter;
    FIELD(s32, g_BMagicOrbitWork, 0x14) = g_BattleEffectBattler->pos.y.fixed + cosTerm;
    if (g_FrameCount & 1) {
        timer                           = FIELD(u8, g_BMagicOrbitWork, 9) - 1;
        FIELD(u8, g_BMagicOrbitWork, 9) = timer;
        if (!(timer & 0xFF)) {
            g_BattleEffectBattler->param.unk_0B -= 1;
            func_801EF970();
        }
    }
}
#else
INCLUDE_ASM(func_801EF418);
#endif

MATCH void func_801EF52C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    s32     off;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    off    = FIELD(u16, g_BMagicOrbitWork, 0xE) + 0x800;
    rot.vz = ((g_BMagicOrbitWork->unk_03 << 7) - off) & 0xFFF;
    pos.vx = (FIELD(s32, g_BMagicOrbitWork, 0x10) >> 9) - 0x4000;
    pos.vy = (FIELD(s32, g_BMagicOrbitWork, 0x14) >> 9) - 0x4000;
    pos.vz = -FIELD(s16, g_BMagicOrbitWork, 0x1A) / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

INCLUDE_ASM(func_801EF5F4);

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
    g_BMagicOrbitWork->header.flags = 0;
    g_BMagicOrbitWork->header.mode  = 0;
    g_BMagicOrbitWork->header.step  = 0;
    g_BMagicOrbitWork->unk_03       = 0;
    g_BMagicOrbitWork->unk_04       = 0;
}
