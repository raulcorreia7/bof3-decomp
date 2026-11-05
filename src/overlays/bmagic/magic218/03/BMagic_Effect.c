#include "magic218_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDB8};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE18(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EEE5C(void) {
    SYS_DISPATCH_BYTE(D_801EF774, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        Effect_SetActorMatrix();
        func_801EF250();
        PopMatrix();
    }
}

MATCH void func_801EEEE4(void) {
    PartyBattler* src;
    PartyBattler* dst;

    if (--g_Task->unk_09 == 0) {
        src            = BATTLE_ACTIVE_WORK;
        dst            = g_Task;
        dst->x         = src->x;
        dst->y         = src->y;
        dst->z         = src->z;
        dst->unk_5D    = 0x10;
        g_Task->unk_09 = 0x10;
        g_Task->timer  = 4;
        g_Task->step++;
    }
}

INCLUDE_ASM(func_801EEF84);

MATCH void func_801EF0F0(void) {
    u8 count;
    u8 timer;

    if (g_FrameCount & 1) {
        timer = g_Task->timer;
        if (timer < 0x20U) {
            g_Task->timer = timer + 1;
        }
    }
    g_Task->unk_09 += 1;
    count          = g_Task->unk_5D - 1;
    g_Task->unk_5D = count;
    if ((count << 0x18) == 0) {
        D_801EB4E0->unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF250);

INCLUDE_ASM(func_801EF70C);
