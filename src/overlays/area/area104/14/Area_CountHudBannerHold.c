#include "area104_14.h"

/* func_801F38EC */
MATCH void Area_CountHudBannerHold(void) {
    if (TASK(Actor)->param.unk_0B == 0) {
        TASK(Actor)->timer++;
        if (TASK(Actor)->timer >= 90) {
            TASK(Actor)->param.unk_0B++;
        }
    }

    if (D_801454F2 != 0 && TASK(Actor)->param.unk_0B != 0) {
        goto bump; /* skips the 0x100 test: advance state byte 0x03 */
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump; /* skips the 0x100 test: advance state byte 0x03 */
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done; /* skips the advance: panel `0x5C` draws next */
    }
bump:
    TASK(Actor)->unk_03++;
done:
    Area_DrawHudBanner(92, TASK(Actor)->screen_y);
}
