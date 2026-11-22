#include "area152_13.h"

/* func_801F36EC */
MATCH void Area_CountHudBannerHold(void) {
    Actor* scratch;

    scratch = TASK(Actor);
    if (scratch->param.unk_0B == 0) {
        scratch->timer++;
        scratch = TASK(Actor);
        if (scratch->timer >= 90) {
            scratch->param.unk_0B++;
        }
    }

    if (D_801454F2 != 0 && TASK(Actor)->param.unk_0B != 0) {
        goto bump;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump;
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done;
    }
bump:
    TASK(Actor)->unk_03++;
done:
    Area_DrawHudBanner(92, TASK(Actor)->screen_y);
}
