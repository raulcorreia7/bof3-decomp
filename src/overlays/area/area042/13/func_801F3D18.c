#include "area042_13.h"

MATCH void func_801F3D18(s32 column) {
    RECT rect;

    setRECT(&rect, (column * 8) + 0x1C8, 352, 8, 0x78);
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, D_801F5358[COORD_INT(SELF(Actor)->pos.x)] + 0x1C0, 0x160);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, 0x18);
}
