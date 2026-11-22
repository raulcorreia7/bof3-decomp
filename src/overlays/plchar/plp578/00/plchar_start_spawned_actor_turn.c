#include "plp578_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CF868(void) {
    SYS_DISPATCH_TASK(D_801CFAF4, 2, g_Task);
}

/* func_801CF8AC */
#include "overlays/plchar/shared/PlChar_StartSpawnedActorTurn.h"

#include "overlays/plchar/shared/PlChar_ClearModeIfSlotFree.h"

MATCH void func_801CFA30(void) {
    D_801CFAFC[TASK(Actor)->unk_2C]();
}

MATCH void func_801CFA74(void) {
    D_801CFB08[TASK(Actor)->unk_2C]();
}
