#include "shop_00.h"

/* The ability cost is the sort key. Indexed at each use
 * so the symbol address rematerializes per access (no held base pointer).
 */

/* func_801E1D84 */
MATCH void Menu_SortAbilityStockByCostAscending(void) {
    u8* abilities;
    u8  i;
    u8  j;
    u8  cur;

    Menu_PackAbilityStock();
    for (i = 0; i < ABILITY_STOCK_SLOT_COUNT - 1; i++) {
        abilities = D_8014546C;
        for (j = 0; j < ABILITY_STOCK_SLOT_COUNT - 1 - i; j++) {
            cur = *abilities;
            if ((cur != 0) && (*(abilities + 1) != 0) && (g_Abilities[cur].cost > g_Abilities[*(abilities + 1)].cost)) {
                Menu_SwapBytes6(abilities, abilities + 1);
            }
            abilities++;
        }
    }
}
