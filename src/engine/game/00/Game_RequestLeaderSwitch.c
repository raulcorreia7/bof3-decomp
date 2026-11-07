#include "game_00.h"

/* func_801B5684 */
MATCH s32 Game_RequestLeaderSwitch(void) {
    if (g_PartySize >= 2U) {
        if (!((g_GameFlags | g_AreaWalkFlags) & AREA_WALK_ACCEPT_LOCK) &&
            (g_InputPressed & g_InputMasks[INPUT_SLOT_SWITCH_LEADER])) {
            if (Party_CanSwitchLeader() & BYTE_MASK) {
                g_Task->header.mode = FIELD_MODE_LEADER_SWITCH;
                g_Task->header.step = 0;
                g_Task->unk_03      = 0;
                g_AreaWalkFlags |= AREA_WALK_LEADER_SWITCH_ACTIVE;
                return 1;
            }
        }
    }
    return 0;
}
