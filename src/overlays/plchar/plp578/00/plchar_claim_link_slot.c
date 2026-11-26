#include "plp578_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE610(void) {
    SYS_DISPATCH_TASK(D_801CFAC4, 2, g_Self);
}

MATCH void func_801CE654(void) {
    CHAR_START_FREE_FACING;
}

#include "overlays/plchar/shared/PlChar_ClaimLinkSlot.h"
