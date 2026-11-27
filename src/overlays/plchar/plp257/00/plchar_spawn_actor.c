#include "plp257_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801CFE54(void) {
    D_801CFF20[SELF(Actor)->unk_2C]();
}

MATCH void func_801CFE98(void) {
    D_801CFF2C[SELF(Actor)->unk_2C]();
}
