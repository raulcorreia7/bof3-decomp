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
    Magic117Steps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

#include "overlays/bmagic/Effect_StartPaletteFade.h"

INCLUDE_ASM(func_801EF0F8);

/* Hint: template_edit shape close; extra nop and loop-slot reload remain at +0x128, size 0x13C vs 0x138 (not attempted; scheduling/reload). */
INCLUDE_ASM(func_801EF20C);

MATCH void Effect_PlayOnce2(void) {
    BATTLE_PLAY_ONCE();
}
