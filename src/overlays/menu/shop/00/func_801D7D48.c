#include "shop_00.h"

MATCH void func_801D7D48(void) {
    u8* slot;

    slot = &D_80148656;
    func_801D7E1C(*slot, 152, 63, 0, 0xFF);
    func_801D8050(0);
    Menu_DrawCursorFrame(17, (((s8)*slot * 0x36) + 0x3E) & 0xFFFE, 128, 52, 1, 6);
    if (func_801D81B4(slot + 5, D_8014865F) & BYTE_MASK) {
        D_80148651 -= 6;
    }
}
