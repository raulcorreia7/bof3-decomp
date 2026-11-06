#include "start_08.h"

MATCH void func_801E2668(s32 icon_kind, s32 icon_x, s32 icon_y) {
    Menu_DrawCommandRow(icon_x, icon_y, 6, icon_kind & BYTE_MASK, g_SaveData.window_style);
}
