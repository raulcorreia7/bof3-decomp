#include "start_08.h"

/* Bubble-sorts the group's id row by rank; the mirror row swaps in step. */
MATCH void func_801D4FCC(void) {
    u8* ids;
    u8* mirror;
    u8  i;
    u8  j;
    u32 group;

    func_801D4A44();
    group = D_8014850E;
    for (i = 0; i < 127; i++) {
        ids    = D_801C893C[group];
        mirror = D_801C8950[group];
        for (j = 0; j < 127 - i; ids++, mirror++, j++) {
            if (ids[0] != 0 && ids[1] != 0) {
                if ((u8)Item_GetKind(group, ids[0]) > (u8)Item_GetKind(group, ids[1])) {
                    Menu_SwapBytes(ids, ids + 1);
                    Menu_SwapBytes(mirror, mirror + 1);
                }
            }
        }
    }
}
