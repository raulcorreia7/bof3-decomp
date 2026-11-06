#include "area104_14.h"

MATCH void func_801F2E8C(void) {
    D_801448EB = 0x28;
    g_GameFlags |= (GAME_FLAG_RUN_LOCK | GAME_FLAG_SCRIPT_ACTIVE);
    if (!Item_VitalHas(VITAL_ITEM_SEA_CHARTS)) {
        D_801448EC = 0;
        g_AreaSceneMode++;
    } else {
        func_801F656C();
        D_801448EC = 2;
    }
}
