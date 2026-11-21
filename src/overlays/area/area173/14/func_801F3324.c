#include "area173_14.h"

MATCH void func_801F3324(s32 source_y, s32 dest_y) {
    RECT rect;
    setRECT(&rect, 576, source_y + 256, 88, 48);
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 576, dest_y + 256);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(DR_MOVE));
}
