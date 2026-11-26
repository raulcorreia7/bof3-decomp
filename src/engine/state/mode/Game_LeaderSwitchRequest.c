#include "engine/game/00/game_00.h"

/* func_801B5684 */
MATCH bool Game_LeaderSwitchRequest(void) {
    if (g_Game.party_size >= 2U) {
        if (!((g_Game.flags | g_Game.walk_flags) & AREA_WALK_ACCEPT_LOCK) && (g_PadStates[0].pressed & g_InputMasks[FIELD_INPUT_SWITCH_LEADER])) {
            if (Party_CanSwitchLeader() & BYTE_MASK) {
                SELF(Actor)->header.mode = FIELD_TASK_MODE_LEADER_SWITCH;
                SELF(Actor)->header.step = 0;
                SELF(Actor)->unk_03      = 0;
                g_Game.walk_flags |= AREA_WALK_LEADER_SWITCH_ACTIVE;
                return 1;
            }
        }
    }
    return 0;
}
