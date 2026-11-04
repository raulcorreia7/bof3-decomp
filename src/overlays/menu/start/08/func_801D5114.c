#include "start_08.h"

extern s8 D_80148656; /* local: s8 read (lb); sibling copies are u8 */

/* Bubble-sorts the panel group's entries so items usable by the acting party member come first; the parallel row of
 * the second table moves with each swap. */
MATCH void func_801D5114(void) {
    u8  kind;
    u8  mask;
    u8  i;
    u8  j;
    u8* left;
    u8* right;

    func_801D4A44();
    kind = D_80148504.group;
    mask = 1 << g_CharSlot[D_80144F5A[D_80148656]];
    for (i = 0; i < 127; i++) {
        left  = D_801C893C[kind];
        right = D_801C8950[kind];
        for (j = 0; j < 127 - i; j++) {
            if (left[0] != 0 && left[1] != 0 && (u8)(mask & Item_GetEquipability(kind, left[0])) == 0 &&
                (u8)(mask & Item_GetEquipability(kind, left[1])) != 0) {
                Menu_SwapBytes(left, left + 1);
                Menu_SwapBytes(right, right + 1);
            }
            left++;
            right++;
        }
    }
}
