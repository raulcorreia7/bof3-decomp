#include "plp278_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801CFA64(void) {
    SYS_DISPATCH_TASK(D_801CFCEC, 2, g_Self);
}

#include "overlays/plchar/shared/PlChar_ClaimHelperSlotStep.h"

/* func_801CFAA8 */
MATCH void PlChar_StartSpawnedActorTurn(void) {
    PlChar_ClaimHelperSlotStep();
}

#include "overlays/plchar/shared/PlChar_ClearModeIfSlotFree.h"

MATCH void func_801CFC2C(void) {
    D_801CFCF4[SELF(Actor)->unk_2C]();
}

MATCH void func_801CFC70(void) {
    D_801CFD00[SELF(Actor)->unk_2C]();
}
