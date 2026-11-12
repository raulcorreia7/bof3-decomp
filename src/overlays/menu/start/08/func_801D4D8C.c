#include "start_08.h"

MATCH void func_801D4D8C(void) {
    s32 ring;
    s32 inner;
    s32 limit;
    s32 span;
    u8* left;
    u8* right;
    u8* out;
    u8  left_id;
    u8  right_id;

    func_801D4A44();
    for (ring = 0; (u32)(ring & BYTE_MASK) < INV_SLOTS_PER_CATEGORY - 1; ring += 1) {
        left  = g_InventoryIds[1];
        out   = g_InventoryIds[1] + 0x200;
        limit = 127 - (ring & BYTE_MASK);
        inner = 0;
        if (limit > 0) {
            span  = limit;
            right = g_InventoryIds[1] + 1;
            do {
                left_id = *left;
                if (left_id != 0) {
                    right_id = *right;
                    if (right_id != 0) {
                        if (g_Weapons[left_id].power < g_Weapons[right_id].power) {
                            Menu_SwapBytes(left, right);
                            Menu_SwapBytes(out, out + 1);
                        }
                    }
                }
                right += 1;
                left += 1;
                inner += 1;
                out += 1;
            } while ((inner & BYTE_MASK) < span);
        }
    }
}
