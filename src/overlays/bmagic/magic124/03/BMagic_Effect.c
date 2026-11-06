#include "magic124_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC14);

INCLUDE_ASM(func_801EEDD8);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

MATCH void func_801EEFF0(void) {
    u8 temp_v0;

    if (g_Task->unk_0B < 3U) {
        temp_v0       = g_Task->timer - 1;
        g_Task->timer = temp_v0;
        if (!(temp_v0 & 0xFF)) {
            g_Task->header.mode += 1;
        }
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

INCLUDE_ASM(func_801EF0B0);

MATCH void func_801EF268(void) {
}

MATCH void func_801EF270(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, TASK_BYTES[1]);
}

INCLUDE_ASM(func_801EF2B4);

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
    g_Task->timer = 0x10 + (rsin((g_Task->unk_0B & 0x3F) << 6) * 4 >> 12);
    g_Task->unk_0C++;
    if (g_Task->unk_0C == 0x10) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF654(void) {
    u8 timer;

    g_Task->timer  = ((rsin((g_Task->unk_0B & 0x3F) << 6) * 4) >> 0xC) + 0x10;
    timer          = g_Task->unk_09 - 2;
    g_Task->unk_09 = timer;
    if (!(timer & 0xFF)) {
        D_801EB4E0->unk_0B -= 1;
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
    PartyBattler* work;

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
    PartyBattler* work;
    u8            count;

    work = g_Task;
    work->timer++;
    work         = g_Task;
    count        = work->unk_09 - 4;
    work->unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->unk_0B--;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F03E0);

INCLUDE_ASM(func_801F05B4);

/* func_801F0828 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F088C */
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}
