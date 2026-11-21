#include "magic166_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEEF0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF34(void) {
    BMAGIC_DISPATCH_AND_DRAW_IN_OWN_MATRIX(D_801EF71C, func_801EF284, func_801EF380);
}
