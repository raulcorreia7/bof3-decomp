#include "area065_13.h"

MATCH void func_801F3860(void) {
    Actor* scratch;

    scratch = g_SpadWork;
    if (((u8*)scratch)[0xB] == 0) {
        ((u8*)scratch)[9]++;
        scratch = g_SpadWork;
        if (((u8*)scratch)[9] >= 0x5A) {
            ((u8*)scratch)[0xB]++;
        }
    }

    if (D_801454F2 != 0 && ((u8*)g_SpadWork)[0x0B] != 0) {
        goto bump; /* skips the 0x100 test: advance state byte 0x03 */
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump; /* skips the 0x100 test: advance state byte 0x03 */
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done; /* skips the advance: panel `0x5C` draws next */
    }
bump:
    ((u8*)g_SpadWork)[0x03]++;
done:
    func_801F40FC(0x5C, g_SpadWork->unk_30);
}
