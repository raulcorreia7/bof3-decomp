#include "plp016_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CF70C(void) {
    Script_AnimStepLoop();
}

MATCH void func_801CF72C(void) {
    SYS_DISPATCH_TASK(D_801D0668, 2, g_Self);
}

MATCH void func_801CF770(void) {
    SYS_DISPATCH_TASK(D_801D0670, 3, g_Self);
}

MATCH void PlChar_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801D02A0, PlChar_ProbeFacingClearance);
}
