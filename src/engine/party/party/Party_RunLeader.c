#include "engine/game/00/game_00.h"

/* func_801B00F8 */
/* Runs the leader's frame: the per-frame helper, the countdown byte, then the mode handler. */
MATCH void Party_RunLeader(void) {
    u8 countdown;

    func_801C3154();
    countdown = D_80146256;
    if (countdown != 0) {
        D_80146256 = countdown - 1;
    }
    func_801BDBC4();
    g_PartyLeaderModes[SELF(Actor)->header.mode]();
}
