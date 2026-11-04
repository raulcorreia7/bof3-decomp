#include "start_08.h"

/* Item table (0x14-byte records) the sort compares through; the type is
 * shared with etc/shop/00 in include/menu/item.h. */

/* Bubble-sorts the nine-entry item-id list the battle selection resolves by item-table byte 0,
 * after func_801D9350 has moved the empty entries to the end.
 */
MATCH void func_801D9548(void) {
    u8* work;
    u8* row;
    u8  i;
    u8  j;
    u8  cur;
    u8  nxt;

    func_801D9350();
    work = g_BattleChoicePanel;
    for (i = 0; i < 9; i++) {
        row = Party_GetAbilities(work[0xA], work[0xB], 0);
        for (j = 0; j < 9 - i; j++) {
            cur = *row;
            if (cur != 0) {
                nxt = *(row + 1);
                if ((nxt != 0) && (D_801CA71A[cur].unk_00 > D_801CA71A[nxt].unk_00)) {
                    Menu_SwapBytes_801D933C(row, row + 1);
                }
            }
            row++;
        }
    }
}
