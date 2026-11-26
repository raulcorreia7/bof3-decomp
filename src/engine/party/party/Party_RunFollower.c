#include "engine/game/00/game_00.h"

/* func_801BBE48 */
/* Runs a follower's frame: the per-frame helper, then the mode handler. */
MATCH void Party_RunFollower(void) {
    func_801C3154();
    g_PartyFollowerModes[SELF(Actor)->header.mode]();
}
