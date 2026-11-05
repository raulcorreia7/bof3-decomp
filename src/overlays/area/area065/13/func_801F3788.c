#include "area065_13.h"

MATCH void func_801F3788(void) {
    Actor* scratch;

    scratch = g_SpadWork;
    scratch->unk_30 -= 0xA;
    if ((s16)scratch->unk_30 < 0xC9) {
        scratch->unk_03++;
    }

    if (D_801454F2 != 0 && g_SpadWork->unk_0B != 0) {
        goto force; /* skips the 0x100 test: force state byte 0x03 */
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto force; /* skips the 0x100 test: force state byte 0x03 */
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done; /* skips the forced write: panel `0x5C` draws next */
    }
force:
    ((u8*)g_SpadWork)[3] = 3;
done:
    func_801F40FC(0x5C, g_SpadWork->unk_30);
}
