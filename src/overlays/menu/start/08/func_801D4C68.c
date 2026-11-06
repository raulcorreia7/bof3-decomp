#include "start_08.h"

MATCH void func_801D4C68(void) {
    u8* a;
    u8* b;
    u8* c;
    u32 i;
    s32 j;
    s32 n;
    s32 lim;
    u8  x;
    u8  y;

    func_801D4A44();
    for (i = 0; (i & BYTE_MASK) < INV_SLOTS_PER_CATEGORY - 1; i++) {
        a = g_InventoryIds[0];
        c = a + 0x200;
        n = INV_SLOTS_PER_CATEGORY - 1 - (i & BYTE_MASK);
        j = 0;
        if (n > 0) {
            lim = n;
            b   = a + 1;
            do {
                x = *a;
                if (x != 0) {
                    y = *b;
                    if (y != 0) {
                        if (!(g_Items[x].flags & ITEM_TARGET_SELECTABLE)) {
                            if (g_Items[y].flags & ITEM_TARGET_SELECTABLE) {
                                Menu_SwapBytes(a, b);
                                Menu_SwapBytes(c, c + 1);
                            }
                        }
                    }
                }
                b++;
                a++;
                j++;
                c++;
            } while ((j & BYTE_MASK) < lim);
        }
    }
}
