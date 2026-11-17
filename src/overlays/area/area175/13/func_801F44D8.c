#include "area175_13.h"

MATCH void func_801F44D8(void) {
    if (g_ScenarioState.scenario_id >= 8) {
        func_801EECA4();
    }
    D_801455C7 = 0;
    if (g_GameCellType != 0) {
        SND_PlaySE(EMI_CUE_ID(SND_BANK_AREA, 12));
    }
}
