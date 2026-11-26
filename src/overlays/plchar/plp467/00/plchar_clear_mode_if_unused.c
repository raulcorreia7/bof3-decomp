#include "plp467_00.h"
#include "engine/game/00/game_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/plchar/shared/PlChar_ClearModeIfUnused.h"

#include "overlays/plchar/shared/Char_ProbeFacingBlocked.h"
CHAR_DEFINE_PROBE_FACING_BLOCKED(func_801CF3C0);

/* func_801CF564 */
#include "overlays/plchar/shared/PlChar_ProbeFacingClearance.h"

MATCH void func_801CF6C8(void) {
    SYS_DISPATCH_TASK(D_801D03EC, 2, g_Self);
}
