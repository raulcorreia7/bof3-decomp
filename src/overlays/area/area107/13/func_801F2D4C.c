#include "area107_13.h"

MATCH void func_801F2D4C(void) {
    Actor* work;
    s32    timer;
    s8     step;

    ACTOR_COUNT_DOWN(SELF(Actor), timer, timer);
    if (!(timer & BYTE_MASK)) {
        UI_MessageStartArea(MSG_AREA107_TIDE_LEVEL_CHANGED);
        work              = SELF(Actor);
        g_GameStateIndex  = GAME_REQUEST_MESSAGE;
        work->header.mode = 4;
    } else {
        step                     = D_801F2E58[SELF(Actor)->timer & 0x3];
        g_AreaCameraRefreshCount = 2;
        g_AreaCameraOffsetY += step * 4;
    }
}
