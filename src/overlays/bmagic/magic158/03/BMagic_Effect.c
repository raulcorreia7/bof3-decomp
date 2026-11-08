#include "magic158_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC04_2.h"

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEF0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EEF34(void) {
    SYS_DISPATCH_BYTE(D_801EF788, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
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
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) - 0x60;
    if ((count & 0xFF) != 0x10) {
        g_Task->unk_09 = count + 1;
    }
    timer = g_Task->timer;
    if (timer != 0x10) {
        g_Task->timer = timer + 2;
    }
    if (COORD_INT(g_Task->pos.z) == COORD_INT(BATTLE_ACTIVE_WORK->pos.z)) {
        g_Task->header.step += 1;
    }
}

/* magic045 shape with the angle cell as s16* &D_1F800004 reaches 4 bytes short; retail keeps the masked phase in v0 and shifts it twice (sll a0 then sll v0), ours puts it in a0; first diff +0x14 */
INCLUDE_ASM(func_801EF1C8);

INCLUDE_ASM(func_801EF2F0);

INCLUDE_ASM(func_801EF3EC);

/* func_801EF708 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
