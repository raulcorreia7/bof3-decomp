#include "plp478_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CF488(void) {
    SYS_DISPATCH_TASK(D_801CF708, 2, g_Task);
}

#include "overlays/plchar/shared/PlChar_ClaimHelperSlotStep.h"

/* func_801CF4CC */
MATCH void PlChar_StartSpawnedActorTurn(void) {
    PlChar_ClaimHelperSlotStep();
}

#include "overlays/plchar/shared/PlChar_ClearModeIfSlotFree.h"

MATCH void func_801CF650(void) {
    D_801CF710[TASK(Actor)->unk_2C]();
}

MATCH void func_801CF694(void) {
    D_801CF71C[TASK(Actor)->unk_2C]();
}
