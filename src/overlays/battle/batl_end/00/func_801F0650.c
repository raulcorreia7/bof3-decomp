#include "batl_end_00.h"

MATCH void func_801F0650(void) {
    u8  slot;
    u16 item;
    u16 x_offset;
    u16 y_offset;

    func_801F039C(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, 280, g_MenuCurrentPanel->unk_09);
    for (slot = 0; slot < D_80146327.count; slot++) {
        item = *(u16*)&D_80146327.items[slot * 2];
        if (item != 0) {
            x_offset = (slot & 1) * 138 + 5;
            y_offset = (slot >> 1) * 13 + 4;
            func_801F0A74(g_MenuCurrentPanel->pos.x + x_offset, g_MenuCurrentPanel->pos.y + y_offset, 0, item >> 8, item & BYTE_MASK, D_80146327.levels[slot], 0);
        }
    }
}
