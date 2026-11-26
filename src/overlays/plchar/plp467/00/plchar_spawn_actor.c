#include "plp467_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801D0324(void) {
    D_801D0404[SELF(Actor)->unk_2C]();
}

MATCH void func_801D0368(void) {
    D_801D0410[SELF(Actor)->unk_2C]();
}
