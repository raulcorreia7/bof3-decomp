#include "engine/slus/slus.h"

/* swaps the two indexed words of the D_8014828C table.
 */
MATCH void Area_SwapObjects(s32 first, s32 second) {
    s32* a;
    s32* b;
    s32* base;
    s32  idx1;
    s32  idx0;
    s32  temp;

    idx1 = second & BYTE_MASK;
    base = D_8014828C;
    b    = &base[idx1];
    idx0 = first & BYTE_MASK;
    a    = &base[idx0];
    temp = *b;
    *b   = *a;
    *a   = temp;
}
