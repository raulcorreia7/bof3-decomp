#include "start_08.h"

/* Bubble-sorts the nine-entry item-id list the battle selection resolves by ability cost,
 * after Menu_PackSkills has moved the empty entries to the end.
 */
/* func_801D9548 */
MATCH void Menu_SortSkillsAscending(void) {
    u8* work;
    u8* row;
    u8  i;
    u8  j;
    u8  cur;
    u8  nxt;

    Menu_PackSkills();
    work = g_BattleChoicePanel;
    for (i = 0; i < 9; i++) {
        row = Party_GetAbilities(work[0xA], work[0xB], 0);
        for (j = 0; j < 9 - i; j++) {
            cur = *row;
            if (cur != 0) {
                nxt = *(row + 1);
                if ((nxt != 0) && (g_Abilities[cur].cost > g_Abilities[nxt].cost)) {
                    Menu_SwapBytes3(row, row + 1);
                }
            }
            row++;
        }
    }
}
