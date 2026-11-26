#include "magic162_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC28_3.h"

#include "overlays/bmagic/shared/func_801EED38_2.h"

#include "overlays/bmagic/shared/Effect_ReplacePaletteFade.h"

#include "overlays/bmagic/shared/Effect_BrightenPalette.h"

/* func_801EF158 */
MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(5);
}

#include "overlays/bmagic/shared/Effect_FadePaletteOut.h"

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

#include "overlays/bmagic/shared/func_801EF338.h"

#include "overlays/bmagic/shared/func_801EF37C.h"

#include "overlays/bmagic/shared/Effect_SparkleLaunch.h"

#include "overlays/bmagic/shared/func_801EF678.h"

#include "overlays/bmagic/shared/func_801EF728.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawRays.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawWedges.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawDisc.h"

/* func_801EFFFC */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

#include "overlays/bmagic/shared/func_801F0068.h"
