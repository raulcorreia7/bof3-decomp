#include "area104_14.h"

MATCH void func_801F2E8C(void) {
    g_SceneEventMode = 0x28;
    g_GameFlags |= (GAME_FLAG_RUN_LOCK | GAME_FLAG_SCRIPT_ACTIVE);
    if (!Item_VitalHas(VITAL_ITEM_SEA_CHARTS)) {
        g_SceneEventStep = 0;
        g_AreaSceneMode++;
    } else {
        func_801F656C();
        g_SceneEventStep = 2;
    }
}
