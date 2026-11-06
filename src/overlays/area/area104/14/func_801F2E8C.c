#include "area104_14.h"

MATCH void func_801F2E8C(void) {
    g_SaveData.scene_event.mode = 0x28;
    g_GameFlags |= (GAME_FLAG_RUN_LOCK | GAME_FLAG_SCRIPT_ACTIVE);
    if (!Item_VitalHas(VITAL_ITEM_SEA_CHARTS)) {
        g_SaveData.scene_event.step = 0;
        g_AreaSceneMode++;
    } else {
        func_801F656C();
        g_SaveData.scene_event.step = 2;
    }
}
