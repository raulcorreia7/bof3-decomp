#include "plp267_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801D0900(void) {
    D_801D09E8[SELF(Actor)->unk_2C]();
}

MATCH void func_801D0944(void) {
    D_801D09F4[SELF(Actor)->unk_2C]();
}
