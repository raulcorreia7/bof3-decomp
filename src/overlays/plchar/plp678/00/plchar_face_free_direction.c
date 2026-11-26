#include "plp678_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CE610(void) {
    Script_AnimStepLoop();
}

MATCH void func_801CE630(void) {
    SYS_DISPATCH_TASK(D_801D0570, 2, g_Self);
}

MATCH void func_801CE674(void) {
    SYS_DISPATCH_TASK(D_801D0578, 3, g_Self);
}

/* func_801CE6B8 */
MATCH void PlChar_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801CF1A4, PlChar_ProbeFacingClearance);
}
