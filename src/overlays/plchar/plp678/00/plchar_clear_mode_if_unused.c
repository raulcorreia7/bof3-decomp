#include "plp678_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_ClearModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801CF1A4);

/* func_801CF348 */
#include "overlays/plchar/shared/PlChar_ProbeFacingClearance.h"

MATCH void func_801CF4AC(void) {
    SYS_DISPATCH_TASK(D_801D0598, 2, g_Self);
}
