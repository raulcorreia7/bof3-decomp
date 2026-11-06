#include "shop_00.h"

MATCH void func_801D7D48(void) {
    u8* slot;

    slot = &D_80148656;
    func_801D7E1C(*slot, 0x98, 0x3F, 0, 0xFF);
    func_801D8050(0);
    Menu_DrawCursorFrame(0x11, (((s8)*slot * 0x36) + 0x3E) & 0xFFFE, 0x80, 0x34, 1, 6);
    if (func_801D81B4(slot + 5, D_8014865F) & BYTE_MASK) {
        D_80148651 -= 6;
    }
}
