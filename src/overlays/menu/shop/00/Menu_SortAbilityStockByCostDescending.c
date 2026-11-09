#include "shop_00.h"

/* Item table: 0x14-byte records; byte 0 is the sort key. */

/* func_801E1C88 */
MATCH void Menu_SortAbilityStockByCostDescending(void) {
    u8* row;
    u8  i;
    u8  j;
    u8  cur;
    u8  nxt;

    Menu_PackAbilityStock();
    for (i = 0; i < ABILITY_STOCK_SLOT_COUNT - 1; i++) {
        row = D_8014546C;
        for (j = 0; j < ABILITY_STOCK_SLOT_COUNT - 1 - i; j++) {
            cur = *row;
            if (cur != 0) {
                nxt = *(row + 1);
                if ((nxt != 0) && (D_801CA71A[cur].unk_00 < D_801CA71A[nxt].unk_00)) {
                    Menu_SwapBytes6(row, row + 1);
                }
            }
            row++;
        }
    }
}
