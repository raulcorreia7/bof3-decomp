#include "magic158_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEF0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EEF34(void) {
    SYS_DISPATCH_BYTE(D_801EF788, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        func_801EF2F0();
        func_801EF3EC();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEFBC);

MATCH void func_801EF140(void) {
    u8 count;
    u8 timer;

    count                    = g_Task->unk_09;
    COORD_INT(g_Task->pos.z) = (u16)COORD_INT(g_Task->pos.z) - 0x60;
    if ((count & 0xFF) != 0x10) {
        g_Task->unk_09 = count + 1;
    }
    timer = g_Task->timer;
    if (timer != 0x10) {
        g_Task->timer = timer + 2;
    }
    if (COORD_INT(g_Task->pos.z) == COORD_INT(BATTLE_ACTIVE_WORK->pos.z)) {
        g_Task->step += 1;
    }
}

INCLUDE_ASM(func_801EF1C8);

INCLUDE_ASM(func_801EF2F0);

INCLUDE_ASM(func_801EF3EC);

/* func_801EF708 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
