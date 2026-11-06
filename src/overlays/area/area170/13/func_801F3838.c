#include "area170_13.h"

MATCH void func_801F3838(u16 line_index) {
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, line_index & BYTE_MASK, 896, 256), 0);
    GFX_AddPrim(2, 0xC);
}
