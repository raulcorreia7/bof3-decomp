#include "area033_13.h"

MATCH void func_801F3684(void) {
    Actor* scratch;

    scratch = g_SpadWork;
    scratch->unk_30 -= 0xA;
    if ((s16)scratch->unk_30 < 0xC9) {
        scratch->unk_03++;
    }

    if ((D_801454F2 != 0 && ((u8*)g_SpadWork)[0x0B] != 0) || g_GameStateIndex == GAME_REQUEST_MESSAGE ||
        (g_GameFlags & GAME_FLAG_SCRIPT_ACTIVE) != 0) {
        ((u8*)g_SpadWork)[3] = 3;
    }
    func_801F3FF8(0x5C, g_SpadWork->unk_30);
}
