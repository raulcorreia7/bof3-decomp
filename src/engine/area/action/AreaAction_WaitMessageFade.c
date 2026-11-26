#include "engine/game/00/game_00.h"

/* func_801AD9C4 */
MATCH void AreaAction_WaitMessageFade(void) {
    if (g_SysThreads[0].tail.game_entry.request == GAME_REQUEST_MESSAGE) {
        return;
    }

    SELF(Actor)->unk_04 = 5;
}
