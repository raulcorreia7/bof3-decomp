#include "plp016_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_ClearModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801D02A0);

/* func_801D0444 */
#include "overlays/plchar/shared/PlChar_ProbeFacingClearance.h"

MATCH void func_801D05A8(void) {
    D_801D0690[SELF(Actor)->unk_2C]();
}

MATCH void func_801D05EC(void) {
    D_801D069C[SELF(Actor)->unk_2C]();
}
