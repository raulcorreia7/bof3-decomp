#include "area082_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F46C8(s32 turn, s32 count, s32 angle, s32 height) {
    s32 tpage;

    PushMatrix();
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(DR_MODE));
    PopMatrix();
}
#else
INCLUDE_ASM(func_801F46C8);
#endif
