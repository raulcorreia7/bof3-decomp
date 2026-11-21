#include "shop_00.h"

/* The ability cost is the sort key. Indexed at each use
 * so the symbol address rematerializes per access (no held base pointer).
 */

/* func_801E1D84 */
MATCH void Menu_SortAbilityStockByCostAscending(void) {
    u8* row;
    u8  i;
    u8  j;
    u8  cur;

    Menu_PackAbilityStock();
    for (i = 0; i < ABILITY_STOCK_SLOT_COUNT - 1; i++) {
        row = D_8014546C;
        for (j = 0; j < ABILITY_STOCK_SLOT_COUNT - 1 - i; j++) {
            cur = *row;
            if ((cur != 0) && (*(row + 1) != 0) && (g_Abilities[cur].cost > g_Abilities[*(row + 1)].cost)) {
                Menu_SwapBytes6(row, row + 1);
            }
            row++;
        }
    }
}
