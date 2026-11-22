#include "area065_13.h"

MATCH void func_801F3960(void) {
    Actor* scratch;
    s32    armed;

    scratch = TASK(Actor);
    scratch->screen_y += 0xA;
    if ((s16)scratch->screen_y >= 0xF0) {
        scratch->unk_03 = 0;
    }
    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        armed               = 1;
        TASK(Actor)->unk_03 = armed;
    }
    func_801F40FC(92, TASK(Actor)->screen_y);
}
