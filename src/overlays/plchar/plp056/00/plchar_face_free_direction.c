#include "plp056_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CF934(void) {
    Script_AnimStepLoop();
}

MATCH void func_801CF954(void) {
    SYS_DISPATCH_TASK(D_801D0894, 2, g_Self);
}

MATCH void func_801CF998(void) {
    SYS_DISPATCH_TASK(D_801D089C, 3, g_Self);
}

MATCH void PlChar_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801D04C8, PlChar_ProbeFacingClearance);
}
