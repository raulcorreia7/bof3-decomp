#include "area033_13.h"

MATCH void func_801F375C(void) {
    u8* scratch;

    scratch = SELF(u8);
    if (scratch[0x0B] == 0) {
        scratch[9]++;
        scratch = SELF(u8);
        if (scratch[9] >= 0x5A) {
            scratch[0x0B]++;
        }
    }

    if (D_801454F2 != 0 && SELF(Actor)->param.unk_0B != 0) {
        goto bump;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump;
    }
    if ((g_Game.flags & GAME_FLAG_SCRIPT_ACTIVE) == 0) {
        goto done;
    }
bump:
    SELF(Actor)->unk_03++;
done:
    func_801F3FF8(0x5C, SELF(Actor)->screen_y);
}
