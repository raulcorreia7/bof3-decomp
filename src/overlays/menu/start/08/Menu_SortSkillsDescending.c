#include "start_08.h"

/* The ability cost is the sort key. Indexed at each use
 * so the symbol address rematerializes per access (no held base pointer);
 * the record type is what keeps the 0x14 scale in the index. */

/* Bubble-sorts the ten-entry party id list of the selection work record into descending order of
 * the item table's sort key, skipping zero entries.
 */
/* func_801D942C */
MATCH void Menu_SortSkillsDescending(void) {
    u8* list;
    u8* next;
    u8* work;
    u8  i;
    u8  j;
    u8  cur;
    u8  nxt;
    s32 n;

    Menu_PackSkills();
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
                    if ((nxt != 0) && (g_Abilities[cur].cost < g_Abilities[nxt].cost)) {
                        Menu_SwapBytes3(list, next);
                    }
                }
                next++;
                j++;
                list++;
            } while (j < n);
        }
        i++;
        j = 0;
    } while (i < 9);
}
