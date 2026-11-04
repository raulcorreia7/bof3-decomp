#include "start_08.h"

/* Item table: 0x14-byte records, byte 0 is the sort key. Indexed at each use
 * so the symbol address rematerializes per access (no held base pointer);
 * the record type is what keeps the 0x14 scale in the index. */

/* Bubble-sorts the ten-entry party id list of the selection work record into descending order of
 * the item table's sort key, skipping zero entries.
 */
MATCH void func_801D942C(void) {
    u8* list;
    u8* next;
    u8* work;
    u8  i;
    u8  j;
    u8  cur;
    u8  nxt;
    s32 n;

    func_801D9350();
    work = g_BattleChoicePanel;
    i    = 0;
    j    = 0;
    do {
        list = Party_GetAbilities(work[0xA], work[0xB], 0);
        /* The pass length is written out twice on purpose: the test's
         * temporary is the value the body stores into the loop limit. */
        if (9 - i > 0) {
            n    = 9 - i;
            next = list + 1;
            do {
                cur = list[0];
                if (cur != 0) {
                    nxt = next[0];
                    if ((nxt != 0) && (D_801CA71A[cur].unk_00 < D_801CA71A[nxt].unk_00)) {
                        Menu_SwapBytes_801D933C(list, next);
                    }
                }
                next++;
                j++;
                list++;
            } while ((u8)j < n);
        }
        i++;
        j = 0;
    } while ((u8)i < 9);
}
