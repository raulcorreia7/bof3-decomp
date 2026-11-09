#include "engine/slus/slus.h"

/* swaps the two indexed words of the D_80148214 table.
 */
MATCH void Area_SwapActors(s32 first, s32 second) {
    Actor** table;
    Actor** a;
    Actor** b;
    s32     ib;
    Actor*  temp;

    ib    = second & BYTE_MASK;
    table = D_80148214;
    b     = &table[ib];
    a     = &table[first & BYTE_MASK];
    temp  = *b;
    *b    = *a;
    *a    = temp;
}
