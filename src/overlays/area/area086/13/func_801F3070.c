#include "area086_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3070(void) {
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), 0);
    GFX_AddPrim(6, sizeof(DR_MODE));
}
#else
INCLUDE_ASM(func_801F3070);
#endif
