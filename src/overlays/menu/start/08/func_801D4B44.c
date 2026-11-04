#include "start_08.h"

MATCH void func_801D4B44(void) {
    s32 n;
    u8  j;
    u8  i;
    u8* row;
    u8* nxt;
    u8* mirror;
    u8  c0;
    u8  c1;

    func_801D4A44();
    i = 0;
    do {
        row    = g_InventoryIds[0];
        mirror = row + 0x200;
        j      = 0;
        if (127 - (i & BYTE_MASK) > 0) {
            n   = 127 - (i & BYTE_MASK);
            nxt = row + 1;
            do {
                c0 = *row;
                if (c0 != 0) {
                    c1 = *nxt;
                    if ((c1 != 0) && !(g_Items[c0].flags & 1) && (g_Items[c1].flags & 1)) {
                        Menu_SwapBytes(row, nxt);
                        Menu_SwapBytes(mirror, mirror + 1);
                    }
                }
                nxt++;
                row++;
                j++;
                mirror++;
            } while ((u8)j < n);
        }
        i++;
    } while ((u8)i < 127);
}
