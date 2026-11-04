#include "start_08.h"

MATCH void func_801D4A44(void) {
    u8* row;
    u8* pair;
    u8  i;
    u8  j;

    for (i = 0; i < 127; i++) {
        row  = D_801C893C[D_8014850E];
        pair = D_801C8950[D_8014850E];
        for (j = 0; j < 127 - i; j++) {
            if (row[0] == 0 && row[1] != 0) {
                Menu_SwapBytes(row, row + 1);
                Menu_SwapBytes(pair, pair + 1);
            }
            row++;
            pair++;
        }
    }
}
