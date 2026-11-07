#include "area098_13.h"

MATCH s32 func_801F4E7C(void) {
    u8  i;
    s32 live;
    u8* slot;
    u8  buffer[0x20];

    live = 0;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 0x3C0, 0), 0);
    GFX_AddPrim(2, 0xC);
    Area_SetCameraMatrix(buffer);
    slot = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < 16; i += 1, slot += 0x1C) {
        if (slot[0] != 0) {
            D_801F5FBC[slot[1]](slot);
            live = 1;
            func_801F4BC0(slot);
        }
    }
    return live;
}
