#include "area065_13.h"

MATCH void func_801F3960(void) {
    Actor* scratch;
    s32    armed;

    scratch = g_Task;
    scratch->screen_y += 0xA;
    if ((s16)scratch->screen_y >= 0xF0) {
        scratch->unk_03 = 0;
    }
    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        armed          = 1;
        g_Task->unk_03 = armed;
    }
    func_801F40FC(92, g_Task->screen_y);
}
