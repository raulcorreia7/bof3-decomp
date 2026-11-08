#include "game_00.h"

/* func_801B5684 */
MATCH s32 Game_RequestLeaderSwitch(void) {
    if (g_Game.party_size >= 2U) {
        if (!((g_Game.flags | g_Game.walk_flags) & AREA_WALK_ACCEPT_LOCK) &&
            (g_InputPressed & g_InputMasks[FIELD_INPUT_SWITCH_LEADER])) {
            if (Party_CanSwitchLeader() & BYTE_MASK) {
                g_Task->header.mode = FIELD_TASK_MODE_LEADER_SWITCH;
                g_Task->header.step = 0;
                g_Task->unk_03      = 0;
                g_Game.walk_flags |= AREA_WALK_LEADER_SWITCH_ACTIVE;
                return 1;
            }
        }
    }
    return 0;
}
