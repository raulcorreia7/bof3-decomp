#include "start_08.h"

MATCH void func_801D4A44(void) {
    u8* row;
    u8* pair;
    u8  i;
    u8  j;

    for (i = 0; i < INV_SLOTS_PER_CATEGORY - 1; i++) {
        row  = g_ItemCategoryIds[g_UIPanelTasks[13].unk_0A];
        pair = g_ItemCategoryCounts[g_UIPanelTasks[13].unk_0A];
        for (j = 0; j < INV_SLOTS_PER_CATEGORY - 1 - i; j++) {
            if (row[0] == 0 && row[1] != 0) {
                Menu_SwapBytes(row, row + 1);
                Menu_SwapBytes(pair, pair + 1);
            }
            row++;
            pair++;
        }
    }
}
