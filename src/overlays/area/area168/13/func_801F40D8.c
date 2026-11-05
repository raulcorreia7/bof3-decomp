#include "area168_13.h"

MATCH void func_801F40D8(void) {
    Actor* scratch;

    scratch = g_SpadWork;
    scratch->unk_30 -= 0x10;
    if ((s16)scratch->unk_30 <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(2, 3));
        }
        scratch = g_SpadWork;
        scratch->state_02 = 1;
    }
    func_801F4158_area168(0, 1);
    func_801F4158_area168(1, 2);
}
