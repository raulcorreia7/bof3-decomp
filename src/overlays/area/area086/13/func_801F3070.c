#include "area086_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3070(void) {
    GFX_ADD_LAYER_DRAW_MODE(6, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));
}
#else
INCLUDE_ASM(func_801F3070);
#endif
