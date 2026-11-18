#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7A00(void) {
    SYS_DISPATCH_BYTE(D_801FE3E4, g_ScenarioState.state_04);
}

MATCH void func_801F7A3C(void) {
}
