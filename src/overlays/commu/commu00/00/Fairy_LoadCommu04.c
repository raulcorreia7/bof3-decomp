#include "commu00_00.h"

MATCH void Fairy_LoadCommu04(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        g_AreaWalkFlags |= AREA_WALK_BUSY_ALL;
        EMI_LoadArchive(EMI_SLOT_COMMU04);
        FAIRY_EVENT_STEP = FAIRY_EVENT_STEP + 1;
    }
}
