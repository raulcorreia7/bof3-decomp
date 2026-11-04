#include "start_08.h"

MATCH void func_801D9350(void) {
    SkillOrder* work;
    u8*         row;
    u8*         next;
    u8          i;
    u8          j;
    s32         limit;

    work = (SkillOrder*)g_BattleChoicePanel;
    for (i = 0; i < 9; i++) {
        j   = 0;
        row = Party_GetAbilities(work->party_slot, work->ability_group, 0);
        if (9 - i > 0) {
            limit = 9 - i;
            next  = row + 1;
            do {
                if (*row == 0 && *next != 0) {
                    Menu_SwapBytes_801D933C(row, next);
                }
                next++;
                j++;
                row++;
            } while (j < limit);
        }
    }
}
