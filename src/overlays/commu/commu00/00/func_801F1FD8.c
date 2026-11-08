#include "commu00_00.h"

MATCH void func_801F1FD8(void) {
    g_AreaWalkFlags |= AREA_WALK_BUSY_ALL;
    EMI_LoadArchive(EMI_SLOT_COMMU03);
    FAIRY_EVENT_STEP = FAIRY_EVENT_STEP + 1;
}
