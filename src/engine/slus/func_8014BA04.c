#include "engine/slus/slus.h"

/* clears the eight halfwords ending at offset 0x6E and the 16-byte run at
 * offset 0x70 of the g_CallbackSlot work area.
 */
MATCH void func_8014BA04(void) {
    u8* base;
    u8* p;
    s32 i;

    base = (u8*)(s32)g_CallbackSlot;
    p    = base + 0xE;
    i    = 7;
    do {
        *(u16*)(p + 0x60) = 0;
        i -= 1;
        p -= 2;
    } while (i >= 0);

    for (i = 0; i < 16; i++) {
        ((u8*)(s32)g_CallbackSlot + i)[0x70] = 0;
    }
}
