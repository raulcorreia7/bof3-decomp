#include "plp267_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CEE08(void) {
    Script_AnimStepLoop();
}

MATCH void func_801CEE28(void) {
    SYS_DISPATCH_TASK(D_801D09A8, 2, g_Self);
}

MATCH void func_801CEE6C(void) {
    SYS_DISPATCH_TASK(D_801D09B0, 3, g_Self);
}

MATCH void PlChar_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801CF99C, PlChar_ProbeFacingClearance);
}
