#include "battle_03.h"

/* func_801E7818 */
MATCH void Battle_UpdateFormChange(void) {
    BattleFormChangeSteps table = g_BattleFormChangeSteps;

    table.modes[SELF(PartyMember)->header.mode]();
}
