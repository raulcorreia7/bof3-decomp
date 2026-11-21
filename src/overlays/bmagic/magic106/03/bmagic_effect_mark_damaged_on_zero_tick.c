#include "magic106_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

MATCH void func_801EEEE0(void) {
    BMagicOrbit* work;

    work = g_BMagicOrbit;
    D_801EF9C0[work->header.mode]();
}

MATCH void func_801EEF24(void) {
    SYS_DISPATCH_BYTE(D_801EF9C4, g_BMagicOrbit->header.step);
    if (g_BMagicOrbit->header.flags != 0 && g_BMagicOrbit->header.step != 0) {
        Effect_SetOrbitModelMatrix();
        func_801EF5F4();
        PopMatrix();
    }
}
