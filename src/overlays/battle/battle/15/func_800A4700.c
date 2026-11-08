#include "battle_15.h"

MATCH void func_800A4700(void) {
    if (g_BattleChoicePhase == 0) {
        EMI_LoaderStreamInitSlot(EMI_SLOT_BATL_DRA);
        *(u8*)&g_Battle.ui_state += 1;
    }
}
