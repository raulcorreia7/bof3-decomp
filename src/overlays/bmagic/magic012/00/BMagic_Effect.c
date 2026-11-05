#include "magic012_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Bmagic_DispatchTaskPair(func_801EEC5C, func_801EEEAC);
}

INCLUDE_ASM(func_801EEC5C);

INCLUDE_ASM(func_801EEEAC);

MATCH void func_801EEFF8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EF03C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 2, g_Task);
}

MATCH void func_801EF080(void) {
    u8 value;

    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & 0xFF)) {
        g_Task->facing = D_801EB4E0->facing;
        g_Task->unk_0C = 0x20000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed        = D_801EB4E0->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed        = D_801EB4E0->pos.y.fixed + g_Task->unk_10;
        COORD_INT(g_Task->pos.z) = (u16)COORD_INT(D_801EB4E0->pos.z) + 0x100;
        g_Task->unk_0B             = rand() & 7;
        g_Task->unk_09             = 0x10;
        g_Task->timer              = 0;
        g_Task->step += 1;
    }
}

INCLUDE_ASM(func_801EF188);

INCLUDE_ASM(func_801EF3C4);

INCLUDE_ASM(func_801EF4B8);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

INCLUDE_ASM(func_801EF6A4);

INCLUDE_ASM(func_801EF79C);
