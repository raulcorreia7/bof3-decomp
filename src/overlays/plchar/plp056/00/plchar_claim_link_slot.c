#include "plp056_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CF338(void) {
    SYS_DISPATCH_TASK(D_801D087C, 2, g_Self);
}

MATCH void func_801CF37C(void) {
    CHAR_START_FREE_FACING;
}

#include "overlays/plchar/shared/PlChar_ClaimLinkSlot.h"
