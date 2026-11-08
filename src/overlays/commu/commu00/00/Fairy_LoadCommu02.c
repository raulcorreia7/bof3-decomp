#include "commu00_00.h"

MATCH void Fairy_LoadCommu02(void) {
    g_AreaWalkFlags |= AREA_WALK_BUSY_ALL;
    if (g_SceneEventSelection == 3) {
        EMI_LoadArchive(EMI_SLOT_COMMU02B);
    } else {
        EMI_LoadArchive(EMI_SLOT_COMMU02);
    }
    FAIRY_EVENT_STEP = FAIRY_EVENT_STEP + 1;
}
