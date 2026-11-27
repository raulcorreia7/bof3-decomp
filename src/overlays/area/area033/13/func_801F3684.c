#include "area033_13.h"

MATCH void func_801F3684(void) {
    Actor* scratch;

    scratch = SELF(Actor);
    scratch->screen_y -= 0xA;
    if (scratch->screen_y < 0xC9) {
        scratch->unk_03++;
    }

    if ((D_801454F2 != 0 && SELF(Actor)->param.unk_0B != 0) || g_GameStateIndex == GAME_REQUEST_MESSAGE || (g_Game.flags & GAME_FLAG_SCRIPT_ACTIVE) != 0) {
        SELF(Actor)->unk_03 = 3;
    }
    func_801F3FF8(0x5C, SELF(Actor)->screen_y);
}
