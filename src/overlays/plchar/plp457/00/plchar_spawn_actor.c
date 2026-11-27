#include "plp457_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_SpawnActor.h"

#include "overlays/plchar/shared/PlChar_ProbeFacingCell.h"

MATCH void func_801CF878(void) {
    D_801CF93C[SELF(Actor)->unk_2C]();
}

MATCH void func_801CF8BC(void) {
    D_801CF948[SELF(Actor)->unk_2C]();
}
