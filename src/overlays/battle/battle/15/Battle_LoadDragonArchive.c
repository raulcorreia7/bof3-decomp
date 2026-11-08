#include "battle_15.h"

/* func_800A4700 */
MATCH void Battle_LoadDragonArchive(void) {
    if (g_BattleChoicePhase == 0) {
        EMI_LoadArchive(EMI_SLOT_BATL_DRA);
        *(u8*)&g_Battle.ui_state += 1;
    }
}
