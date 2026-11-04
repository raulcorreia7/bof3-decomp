#include "magic046_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

INCLUDE_ASM(func_801EED28);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEF70(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEFB4(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC00.steps;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF014);

INCLUDE_ASM(func_801EF090);

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801EF1F0(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

INCLUDE_ASM(func_801EF250);

#include "overlays/bmagic/Effect_AddActorStepOnPlaying.h"

MATCH void func_801EF304(void) {
    func_801E5988();
}

MATCH void func_801EF324(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        func_801EFB90();
        func_801EFC48();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF3B8);

INCLUDE_ASM(func_801EF540);

INCLUDE_ASM(func_801EF660);

INCLUDE_ASM(func_801EF7E8);

MATCH void func_801EFB90(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(BATTLE_ACTIVE_WORK);
}

INCLUDE_ASM(func_801EFC48);

/* func_801EFED0 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
