#include "area175_13.h"

MATCH void func_801F44D8(void) {
    if (g_SceneState.scenario_id >= 8) {
        func_801EECA4();
    }
    D_801455C7 = 0;
    if (D_80143F03 != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 12));
    }
}
