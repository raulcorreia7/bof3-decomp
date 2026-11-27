#include "area173_14.h"

MATCH void func_801F3F08(void) {
    Actor* scratch;
    s32    delta;

    scratch = SELF(Actor);
    scratch->screen_y -= 0x10;
    if (scratch->screen_y <= 0) {
        SYS_SetFlag(g_SceneEventFlags, scratch->direction);
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
        }
        scratch              = SELF(Actor);
        scratch->header.step = 1;
    }
    if (SELF(Actor)->screen_y >= 0x80) {
        delta = -2;
    } else {
        delta = -1;
    }
    func_801F3FBC(0, delta);
    func_801F3FBC(1, 1);
}
