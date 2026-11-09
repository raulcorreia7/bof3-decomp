#include "engine/slus/slus.h"

/* exchange-sorts the 4-byte records at 0x80143740 by their high
 * halfword, swapping each out-of-order pair through the scratch word at
 * 0x1F80000C.
 */
MATCH void func_80153D34(void) {
    s32 i;
    s32 j;
    u32 current;

    for (i = 0; i < D_8014933D; i++) {
        for (j = i + 1; j < D_8014933D; j++) {
            current = D_80143740[i];
            if ((D_80143740[j] >> 16) < (current >> 16)) {
                VOL(u32, D_1F80000C) = current;
                D_80143740[i]        = D_80143740[j];
                D_80143740[j]        = VOL(u32, D_1F80000C);
            }
        }
    }
}
