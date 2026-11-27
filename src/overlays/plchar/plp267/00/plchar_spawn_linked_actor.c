#include "plp267_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801CF62C */
#include "overlays/plchar/shared/PlChar_SpawnLinkedActor.h"

MATCH void func_801CF718(void) {
    SYS_DISPATCH_TASK(D_801D09C4, 3, g_Self);
}

MATCH void func_801CF75C(void) {
    CHAR_START_FACING_TURN(PlChar_ProbeFacingClearance);
}
