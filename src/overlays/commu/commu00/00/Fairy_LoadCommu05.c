#include "commu00_00.h"

MATCH void Fairy_LoadCommu05(void) {
    if (D_80145E44 == 0 && g_FairyVillagePendingQueueCount == 0 && g_FairyVillageUpdateCount == 0) {
        g_SceneEventState.mode = SCENE_EVENT_MESSAGE;
    } else {
        g_AreaWalkFlags |= AREA_WALK_BUSY_ALL;
        EMI_ArchiveLoad(EMI_SLOT_COMMU05);
        FAIRY_EVENT_STEP = FAIRY_EVENT_STEP + 1;
    }
}
