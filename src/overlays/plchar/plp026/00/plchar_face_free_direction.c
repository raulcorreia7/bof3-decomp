#include "plp026_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CFB30(void) {
    Script_AnimStepLoop();
}

MATCH void func_801CFB50(void) {
    SYS_DISPATCH_TASK(D_801D0A8C, 2, g_Self);
}

MATCH void func_801CFB94(void) {
    SYS_DISPATCH_TASK(D_801D0A94, 3, g_Self);
}

MATCH void PlChar_FaceFreeDirection(void) {
    CHAR_FACE_FREE_DIRECTION(func_801D06C4, PlChar_ProbeFacingClearance);
}
