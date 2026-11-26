#include "area168_13.h"

MATCH void func_801F40D8(void) {
    Actor* scratch;

    scratch = SELF(Actor);
    scratch->screen_y -= 0x10;
    if ((s16)scratch->screen_y <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
        }
        scratch              = SELF(Actor);
        scratch->header.step = 1;
    }
    func_801F4158_area168(0, 1);
    func_801F4158_area168(1, 2);
}
