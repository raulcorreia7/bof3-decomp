#include "plp016_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801CFF30 */
#include "overlays/plchar/shared/PlChar_SpawnLinkedActor.h"

MATCH void func_801D001C(void) {
    SYS_DISPATCH_TASK(D_801D0684, 3, g_Self);
}

MATCH void func_801D0060(void) {
    CHAR_START_FACING_TURN(PlChar_ProbeFacingClearance);
}
