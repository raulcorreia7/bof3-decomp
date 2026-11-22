#include "area141_13.h"

/* func_801F4300 */
MATCH void Area_CellSetRun(u8* table, u8 arg) {
    u8 count;
    u8 i;

    count = table[2] & 0x7F;
    if ((table[2] & 0x80) != 0) {
        for (i = 0; i < count; i++) {
            Area_CellSetCode(table[0] + i, table[1], (arg != 0) ? table[3] : table[4]);
        }
    } else {
        for (i = 0; i < count; i++) {
            Area_CellSetCode(table[0], table[1] + i, (arg != 0) ? table[3] : table[4]);
        }
    }
}
