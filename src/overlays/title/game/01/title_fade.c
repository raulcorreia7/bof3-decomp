#include "game_01.h"

/* At fade phase `2`, the handler arms a 360-tick delay and advances the
 * frontend state.
 */
MATCH void Game_WaitTitleFade(void) {
    if (LOBU(g_UiTitleFadePhase) == 2u) {
        u16 state;
        u16 timer;
        timer = 360u;
        /* FAKE: block boundary keeps the 360 load ahead of the state read for the delay slot. */
        ORDER_LOCK(state = g_UiTitleState);
        g_UiTitleTimer = timer;
        g_UiTitleState = state + 1u;
    }
}
