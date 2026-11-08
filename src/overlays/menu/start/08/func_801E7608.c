#include "start_08.h"

void func_801E7514(s32 x, s32 y, s32 icon, s32 palette); /* extern */

MATCH void func_801E7608(void) {
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(1, 1, 704, 256), 0);
    GFX_AddPrim(2U, sizeof(DR_MODE));
    func_801E7514(0x1A, 0x18, 0, 2);
    func_801E7514(0x10A, 0x88, 1, 2);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(1, 1, 576, 256), 0);
    GFX_AddPrim(2U, sizeof(DR_MODE));
    func_801E7514(-6, 0x1C, 2, 2);
    func_801E7514(0xDA, 0x1C, 3, 2);
}
