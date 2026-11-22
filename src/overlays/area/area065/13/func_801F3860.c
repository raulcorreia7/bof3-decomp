#include "area065_13.h"

MATCH void func_801F3860(void) {
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
    func_801F40FC(92, TASK(Actor)->screen_y);
}
