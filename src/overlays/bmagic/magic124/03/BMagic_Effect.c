#include "magic124_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC14);

INCLUDE_ASM(func_801EEDD8);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

MATCH void func_801EEFF0(void) {
    u8 timer_next;

    if (g_Task->param.unk_0B < 3U) {
        timer_next    = g_Task->timer - 1;
        g_Task->timer = timer_next;
        if (!(timer_next & BYTE_MASK)) {
            g_Task->header.mode += 1;
        }
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

INCLUDE_ASM(func_801EF0B0);

MATCH void func_801EF268(void) {
}

/* func_801EF270 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF2B4(void) {
    u8           slot;
    PartyMember* battler;

    SYS_DISPATCH_TASK(g_BMagicEffectModes + 2, 2, g_Task);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        g_Task->param.unk_0B++;
        func_801EF6E8();
        if ((g_Task->param.unk_0B & 3) == 0) {
            if (g_Task->header.step == 1) {
                if (g_Task->timer != 0) {
                    slot = BMagic_AllocEffect();
                    if (slot != 0xFF) {
                        battler                                = g_BattleEffectBattler;
                        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 1;
                        BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
                        BMAGIC_EFFECT_SLOTS[slot].unk_2E       = D_1F800000.view.effect.params[4];
                        BMAGIC_EFFECT_SLOTS[slot].unk_30       = D_1F800000.view.effect.params[5];
                        g_BattleEffectBattler->param.unk_0B++;
                    }
                }
            }
        }
    }
}

INCLUDE_ASM(func_801EF3FC);

MATCH void func_801EF588(void) {
    u8 timer;

    timer         = g_Task->timer + 4;
    g_Task->timer = timer;
    if (timer == 16) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF5D8(void) {
    g_Task->timer = 16 + (rsin((g_Task->param.unk_0B & 0x3F) << 6) * 4 >> 12);
    g_Task->unk_0C++;
    if (g_Task->unk_0C == 0x10) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF654(void) {
    u8 timer;

    g_Task->timer  = ((rsin((g_Task->param.unk_0B & 0x3F) << 6) * 4) >> 0xC) + 16;
    timer          = g_Task->unk_09 - 2;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801EF6E8);

MATCH void func_801F020C(void) {
    SYS_DISPATCH_BYTE(D_801F08F4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F03E0();
        func_801F05B4();
    }
}

MATCH void func_801F028C(void) {
    g_Task->unk_5D = 8;
    g_Task->unk_5E = 6;
    g_Task->unk_5F = 15;
    g_Task->unk_09 = 0;
    g_Task->timer  = 2;
    g_Task->header.step++;
}

MATCH void func_801F02FC(void) {
    PartyMember* work;

    work = g_Task;
    work->timer += 2;
    work = g_Task;
    work->unk_09 += 4;
    if (work->unk_09 == 16) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801F0368(void) {
    PartyMember* work;
    u8           count;

    work = g_Task;
    work->timer++;
    work         = g_Task;
    count        = work->unk_09 - 4;
    work->unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F03E0);

INCLUDE_ASM(func_801F05B4);

/* func_801F0828 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F088C */
#include "overlays/bmagic/Actor_Clear.h"
