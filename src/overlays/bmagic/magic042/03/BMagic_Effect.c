#include "magic042_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    Bmagic_DispatchTaskPair(func_801EEC70, func_801EED44);
}

INCLUDE_ASM(func_801EEC70);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEDA4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

INCLUDE_ASM(func_801EEDE8);

MATCH void func_801EEF08(void) {
    g_Task->facing      = D_801EB4E0->facing;
    g_Task->pos.x.fixed = D_801EB4E0->pos.x.fixed;
    g_Task->pos.y.fixed = D_801EB4E0->pos.y.fixed;
    g_Task->pos.z.fixed = D_801EB4E0->pos.z.fixed;
    func_801EF1B0();
    g_Task->unk_0B = 0;
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EEFB8(void) {
    PartyBattler* work;

    work = g_Task;
    work->unk_0B++;
    work = g_Task;
    work->timer++;
    if (work->timer == 4) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801EF024(void) {
    PartyBattler* work;

    work = g_Task;
    work->unk_0B++;
    work = g_Task;
    work->unk_09 += 8;
    if (work->unk_09 == 80) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801EF090(void) {
    u8 timer;

    g_Task->unk_0B += 1;
    g_Task->unk_09 += 4;
    timer         = g_Task->timer + 4;
    g_Task->timer = timer;
    if ((timer & 0xFF) == 0x20) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF118(void) {
    u8 temp_v0;
    u8 temp_v0_2;

    g_Task->unk_0B += 1;
    temp_v0 = g_Task->unk_09;
    if (temp_v0 != 0) {
        g_Task->unk_09 = temp_v0 - 0xC;
    }
    temp_v0_2     = g_Task->timer - 4;
    g_Task->timer = temp_v0_2;
    if (!(temp_v0_2 & 0xFF)) {
        D_801EB4E0->unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF1B0);

INCLUDE_ASM(func_801EF380);

INCLUDE_ASM(func_801EF71C);

INCLUDE_ASM(func_801EF920);
