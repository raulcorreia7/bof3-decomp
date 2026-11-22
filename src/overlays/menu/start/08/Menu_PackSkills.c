#include "start_08.h"

/* func_801D9350 */
MATCH void Menu_PackSkills(void) {
    SkillOrder* work;
    u8*         abilities;
    u8*         next;
    u8          i;
    u8          j;
    s32         limit;

    work = (SkillOrder*)g_BattleChoicePanel;
    for (i = 0; i < 9; i++) {
        j         = 0;
        abilities = Party_GetAbilities(work->party_slot, work->ability_group, 0);
        if (9 - i > 0) {
            limit = 9 - i;
            next  = abilities + 1;
            do {
                if (*abilities == 0 && *next != 0) {
                    Menu_SwapBytes3(abilities, next);
                }
                next++;
                j++;
                abilities++;
            } while (j < limit);
        }
    }
}
