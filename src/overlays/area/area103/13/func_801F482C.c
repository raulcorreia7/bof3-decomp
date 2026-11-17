#include "area103_13.h"

/* func_801F482C */
MATCH void func_801F482C(void) {
    RECT rect;
    s32  x;
    s32  y;

    x = (((g_Task->pos.x.fixed >> 12) & 0x1F) ^ 0x10) >> 1;
    y = (g_Task->pos.y.fixed >> 12) & 0x1F;

    rect.x = 368;
    rect.y = 416;
    rect.w = x;
    rect.h = y;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 624 - x, 288 - y);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MOVE));

    rect.x = x + 368;
    rect.y = 416;
    rect.w = 16 - x;
    rect.h = y;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 608, 288 - y);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MOVE));

    rect.x = 368;
    rect.y = y + 416;
    rect.w = x;
    rect.h = 32 - y;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 624 - rect.w, 256);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MOVE));

    rect.x = x + 368;
    rect.y = y + 416;
    rect.w = 16 - x;
    rect.h = 32 - y;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 608, 256);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(DR_MOVE));
}
