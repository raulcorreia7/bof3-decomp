#include "area033_13.h"

MATCH void func_801F375C(void) {
    u8* scratch;

    scratch = (u8*)g_SpadWork;
    if (scratch[0x0B] == 0) {
        scratch[9]++;
        scratch = (u8*)g_SpadWork;
        if (scratch[9] >= 0x5A) {
            scratch[0x0B]++;
        }
    }

    if (D_801454F2 != 0 && ((u8*)g_SpadWork)[0x0B] != 0) {
        goto bump;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump;
    }
    if ((g_GameFlags & GAME_FLAG_SCRIPT_ACTIVE) == 0) {
        goto done;
    }
bump:
    ((u8*)g_SpadWork)[3]++;
done:
    func_801F3FF8(0x5C, g_SpadWork->unk_30);
}
