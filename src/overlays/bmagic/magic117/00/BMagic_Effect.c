#include "magic117_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC24.h"

/* blocker: no matched C template (magic010/00 func_801EEC80). */
INCLUDE_ASM(func_801EEC90);

INCLUDE_ASM(func_801EED2C);

INCLUDE_ASM(func_801EEE40);

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF000(void) {
    EffectStepFuncs4 handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_Task);
}

#include "overlays/bmagic/Effect_StartPaletteFade.h"

INCLUDE_ASM(func_801EF0F8);

INCLUDE_ASM(func_801EF20C);

MATCH void Effect_PlayOnce_801EF344(void) {
    BATTLE_PLAY_ONCE();
}
