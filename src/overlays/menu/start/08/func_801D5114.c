#include "start_08.h"

extern s8 D_80148656; /* local: s8 read (lb); sibling copies are u8 */

/* Bubble-sorts the panel group's entries so items usable by the acting party member come first; the parallel row of
 * the second table moves with each swap. */
MATCH void func_801D5114(void) {
    u8  type;
    u8  mask;
    u8  i;
    u8  j;
    u8* left;
    u8* right;

    func_801D4A44();
    type = D_80148504.group;
    mask = 1 << g_CharSlot[g_PartyFieldOrder[D_80148656]];
    for (i = 0; i < INV_SLOTS_PER_CATEGORY - 1; i++) {
        left  = g_ItemCategoryIds[type];
        right = g_ItemCategoryCounts[type];
        for (j = 0; j < INV_SLOTS_PER_CATEGORY - 1 - i; j++) {
            if (left[0] != 0 && left[1] != 0 && (mask & Item_GetEquipability(type, left[0])) == 0 && (mask & Item_GetEquipability(type, left[1])) != 0) {
                Menu_SwapBytes(left, left + 1);
                Menu_SwapBytes(right, right + 1);
            }
            left++;
            right++;
        }
    }
}
