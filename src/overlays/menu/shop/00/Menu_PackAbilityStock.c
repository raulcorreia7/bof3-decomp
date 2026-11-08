#include "shop_00.h"

/* func_801E1BCC */
MATCH void Menu_PackAbilityStock(void) {
    u8* row;
    u8  i;
    u8  j;

    for (i = 0; i < ABILITY_STOCK_SLOT_COUNT - 1; i++) {
        row = D_8014546C;
        for (j = 0; j < ABILITY_STOCK_SLOT_COUNT - 1 - i; j++) {
            if (*row == 0 && *(row + 1) != 0) {
                Menu_SwapBytes_801E1BB8(row, row + 1);
            }
            row++;
        }
    }
}
