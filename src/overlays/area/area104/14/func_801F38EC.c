#include "area104_14.h"

MATCH void func_801F38EC(void) {
    if (g_Task->unk_0B == 0) {
        g_Task->unk_09++;
        if (g_Task->unk_09 >= 0x5A) {
            g_Task->unk_0B++;
        }
    }

    if (D_801454F2 != 0 && g_Task->unk_0B != 0) {
        goto bump; /* skips the 0x100 test: advance state byte 0x03 */
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump; /* skips the 0x100 test: advance state byte 0x03 */
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done; /* skips the advance: panel `0x5C` draws next */
    }
bump:
    g_Task->unk_03++;
done:
    Area_DrawHudBanner(0x5C, g_Task->unk_30);
}
