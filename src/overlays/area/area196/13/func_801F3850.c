#include "area196_13.h"

MATCH void func_801F3850(void) {
    RECT rect;

    setRECT(&rect, 424, 320 - (SELF(Actor)->unk_0A >> 1), 16, 32);
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 0x198, 0x120);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(DR_MOVE));
}
