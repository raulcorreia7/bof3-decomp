#include "magic162_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28_3.h"

#include "overlays/bmagic/func_801EED38_2.h"

#include "overlays/bmagic/Effect_ReplacePaletteFade.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

/* func_801EF158 */
MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(5);
}

#include "overlays/bmagic/Effect_FadePaletteOut.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/func_801EF338.h"

#include "overlays/bmagic/func_801EF37C.h"

#include "overlays/bmagic/Effect_LaunchSparkle.h"

#include "overlays/bmagic/func_801EF678.h"

#include "overlays/bmagic/func_801EF728.h"

#include "overlays/bmagic/Effect_DrawSparkleRays.h"

#include "overlays/bmagic/Effect_DrawSparkleWedges.h"

#include "overlays/bmagic/Effect_DrawSparkleDisc.h"

/* func_801EFFFC */
#include "overlays/bmagic/BMagic_AllocEffect.h"

#include "overlays/bmagic/func_801F0068.h"
