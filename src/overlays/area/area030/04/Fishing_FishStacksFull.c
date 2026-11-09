#include "area030_04.h"

/* Whether every fish species is held at the stack limit: counts the item slots
 * of ITEM_JELLYFISH through ITEM_MACKEREL that are full. */
/* func_801E1C10 */
MATCH bool Fishing_FishStacksFull(void) {
    s32 fish;
    s32 count;
    s32 i;

    fish  = ITEM_JELLYFISH;
    count = 0;
    while (fish <= ITEM_MACKEREL) {
        for (i = 0; i < INV_SLOTS_PER_CATEGORY; i++) {
            if (g_InventoryIds[ITEM_CAT_ITEM][i] == fish && g_InventoryCounts[ITEM_CAT_ITEM][i] == ITEM_STACK_MAX) {
                count++;
            }
        }
        fish++;
    }
    return count >= FISHING_FISH_SPECIES;
}
