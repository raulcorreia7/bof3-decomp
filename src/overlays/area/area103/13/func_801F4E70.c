#include "area103_13.h"

MATCH void func_801F4E70(s32 frame) {
    RECT rect;
    s32  idx;

    idx = frame * 2;
    setRECT(&rect, D_801F5A14[idx] + 576, D_801F5A15[idx] + 256, 32, 64);
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, SELF(Actor)->param.unk_0B * 48 + 576, 256);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, 24);
}
