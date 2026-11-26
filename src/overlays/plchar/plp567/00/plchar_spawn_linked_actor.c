#include "plp567_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801CF430 */
#include "overlays/plchar/shared/PlChar_SpawnLinkedActor.h"

MATCH void func_801CF51C(void) {
    SYS_DISPATCH_TASK(D_801D07CC, 3, g_Self);
}

MATCH void func_801CF560(void) {
    CHAR_START_FACING_TURN(PlChar_ProbeFacingClearance);
}
