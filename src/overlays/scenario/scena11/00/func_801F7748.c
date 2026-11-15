#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7748(void) {
    SYS_DISPATCH_BYTE(D_801FAEFC, g_SceneState.state_04);
}

MATCH void func_801F7784(void) {
}
