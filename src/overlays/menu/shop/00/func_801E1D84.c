#include "shop_00.h"

/* Item table: 0x14-byte records; byte 0 is the sort key. Indexed at each use
 * so the symbol address rematerializes per access (no held base pointer).
 */

MATCH void func_801E1D84(void) {
    u8* row;
    u8  i;
    u8  j;
    u8  cur;

    func_801E1BCC();
    for (i = 0; i < 127; i++) {
        row = D_8014546C;
        for (j = 0; j < 127 - i; j++) {
            cur = *row;
            if ((cur != 0) && (*(row + 1) != 0) && (D_801CA71A[cur].unk_00 > D_801CA71A[*(row + 1)].unk_00)) {
                Menu_SwapBytes_801E1BB8(row, row + 1);
            }
            row++;
        }
    }
}
