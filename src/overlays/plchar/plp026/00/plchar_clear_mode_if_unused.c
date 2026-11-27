#include "plp026_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_ClearModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801D06C4);

/* func_801D0868 */
#include "overlays/plchar/shared/PlChar_ProbeFacingClearance.h"

MATCH void func_801D09CC(void) {
    D_801D0AB4[SELF(Actor)->unk_2C]();
}

MATCH void func_801D0A10(void) {
    D_801D0AC0[SELF(Actor)->unk_2C]();
}
