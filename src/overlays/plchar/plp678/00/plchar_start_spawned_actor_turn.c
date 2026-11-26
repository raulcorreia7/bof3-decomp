#include "plp678_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801D0314(void) {
    SYS_DISPATCH_TASK(D_801D05BC, 2, g_Self);
}

/* func_801D0358 */
#include "overlays/plchar/shared/PlChar_StartSpawnedActorTurn.h"

#include "overlays/plchar/shared/PlChar_ClearModeIfSlotFree.h"

MATCH void func_801D04DC(void) {
    D_801D05C4[SELF(Actor)->unk_2C]();
}

MATCH void func_801D0520(void) {
    D_801D05D0[SELF(Actor)->unk_2C]();
}
