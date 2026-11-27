#include "start_08.h"

/* Bubble-sorts the group's id row by rank; the mirror row swaps in step. */
MATCH void func_801D4FCC(void) {
    u8* ids;
    u8* mirror;
    u8  i;
    u8  j;
    u32 group;

    func_801D4A44();
    group = g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0A;
    for (i = 0; i < INV_SLOTS_PER_CATEGORY - 1; i++) {
        ids    = g_ItemCategoryIds[group];
        mirror = g_ItemCategoryCounts[group];
        for (j = 0; j < INV_SLOTS_PER_CATEGORY - 1 - i; ids++, mirror++, j++) {
            if (ids[0] != 0 && ids[1] != 0) {
                if ((u8)Item_GetIcon(group, ids[0]) > (u8)Item_GetIcon(group, ids[1])) {
                    Menu_SwapBytes(ids, ids + 1);
                    Menu_SwapBytes(mirror, mirror + 1);
                }
            }
        }
    }
}
