#include "plp247_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801CFA74(void) {
    D_801CFB34[SELF(Actor)->unk_2C]();
}

MATCH void func_801CFAB8(void) {
    D_801CFB40[SELF(Actor)->unk_2C]();
}
