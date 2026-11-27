#include "plp056_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_ClearModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801D04C8);

/* func_801D066C */
#include "overlays/plchar/shared/PlChar_ProbeFacingClearance.h"

MATCH void func_801D07D0(void) {
    D_801D08BC[SELF(Actor)->unk_2C]();
}

MATCH void func_801D0814(void) {
    D_801D08C8[SELF(Actor)->unk_2C]();
}
