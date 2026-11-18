#include "game_00.h"

/* func_80197C1C */
MATCH void Battle_WalkToEncounter(void) {
    u8   local_ready;
    u16* state;

    local_ready = Battle_WalkMembersIn();
    Actor_RunInteractions();
    Area_RunLoadingFrame();
    if (EMI_IsReady() && local_ready && g_AreaCameraMoving == 0) {
        state = &g_GameEntrySubstate;
        (*state)++;
    }
}
