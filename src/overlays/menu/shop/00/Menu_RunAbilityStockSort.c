#include "shop_00.h"

/* func_801E1B80 */
MATCH void Menu_RunAbilityStockSort(s32 cursor_row) {
    g_AbilityStockSortFuncs[cursor_row & BYTE_MASK]();
}
