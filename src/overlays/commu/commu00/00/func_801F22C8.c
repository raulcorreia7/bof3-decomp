#include "commu00_00.h"

MATCH void func_801F22C8(void) {
    if (D_80145E44 == 0 && g_FairyVillagePendingQueueCount == 0 && g_FairyVillageUpdateCount == 0) {
        g_SceneEventMode = 6;
    } else {
        g_AreaWalkFlags |= AREA_WALK_BUSY_ALL;
        EMI_LoaderStreamInitSlot(EMI_SLOT_COMMU05);
        FAIRY_EVENT_STEP = FAIRY_EVENT_STEP + 1;
    }
}
