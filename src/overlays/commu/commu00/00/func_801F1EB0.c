#include "commu00_00.h"

MATCH void func_801F1EB0(void) {
    g_AreaWalkFlags |= AREA_WALK_BUSY_ALL;
    if (g_SaveData.scene_event.selection == 3) {
        EMI_LoaderStreamInitSlot(EMI_SLOT_COMMU02B);
    } else {
        EMI_LoaderStreamInitSlot(EMI_SLOT_COMMU02);
    }
    FAIRY_EVENT_STEP = FAIRY_EVENT_STEP + 1;
}
