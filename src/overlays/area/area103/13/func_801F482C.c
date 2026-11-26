#include "area103_13.h"

/* func_801F482C */
MATCH void func_801F482C(void) {
    RECT rect;
    s32  x;
    s32  y;

    x = (((SELF(Actor)->pos.x.fixed >> 12) & 0x1F) ^ 0x10) >> 1;
    y = (SELF(Actor)->pos.y.fixed >> 12) & 0x1F;

    setRECT(&rect, 368, 416, x, y);
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 624 - x, 288 - y);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MOVE));

    setRECT(&rect, x + 368, 416, 16 - x, y);
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 608, 288 - y);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MOVE));

    setRECT(&rect, 368, y + 416, x, 32 - y);
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 624 - rect.w, 256);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MOVE));

    setRECT(&rect, x + 368, y + 416, 16 - x, 32 - y);
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 608, 256);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MOVE));
}
