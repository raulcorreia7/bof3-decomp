#include "plp015_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CF70C(void) {
    SYS_DISPATCH_TASK(D_801CFBBC, 2, g_Self);
}

MATCH void func_801CF750(void) {
    CHAR_START_FREE_FACING;
}

#include "overlays/plchar/shared/PlChar_ClaimLinkSlot.h"
