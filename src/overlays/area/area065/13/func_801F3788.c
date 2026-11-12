#include "area065_13.h"

MATCH void func_801F3788(void) {
    Actor* scratch;

    scratch = g_Task;
    scratch->screen_y -= 0xA;
    if ((s16)scratch->screen_y < 0xC9) {
        scratch->unk_03++;
    }

    if (D_801454F2 != 0 && g_Task->param.unk_0B != 0) {
        goto force; /* skips the 0x100 test: force state byte 0x03 */
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto force; /* skips the 0x100 test: force state byte 0x03 */
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done; /* skips the forced write: panel `0x5C` draws next */
    }
force:
    g_Task->unk_03 = 3;
done:
    func_801F40FC(92, g_Task->screen_y);
}
