#include "magic074_03.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawRays.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawWedges.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawDisc.h"

/* func_801F03D4 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

MATCH void func_801F0440(void) {
    D_801F20DC->header.flags = 0;
    D_801F20DC->header.mode  = 0;
    D_801F20DC->header.step  = 0;
    D_801F20DC->unk_03       = 0;
    D_801F20DC->unk_04       = 0;
}
