#include "area128_13.h"

MATCH void func_801F31D0(void) {
    if (g_GameLastAreaId == AREA_ID_STEEL_BEACH_MAP) {
        SYS_SetFlag(g_SceneEventFlags, 67);
        SYS_ClearFlag(g_SceneEventFlags, 66);
        Area_RunBundleObjects();
    }
    if (g_ScenarioState.scenario_id >= 11 && SYS_TestFlag(g_SceneEventFlags, 67)) {
        Area_SetCellCode(31, 57, 0xC0);
        Area_SetCellCode(32, 57, 0xC0);
        Area_SetCellCode(31, 58, 0xA1);
        Area_SetCellCode(32, 58, 0xA1);
    }
}
