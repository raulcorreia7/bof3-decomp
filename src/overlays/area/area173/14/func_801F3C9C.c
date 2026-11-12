#include "area173_14.h"

MATCH void func_801F3C9C(void) {
    s32 trigger;

    trigger = 0;
    if (g_AreaSceneMode == 1) {
        trigger         = 1;
        g_AreaSceneMode = 0;
    }
    if (abs(g_Game.members[0].pos.y.fixed - (TO_COORD(COORD_INT(g_Task->pos.y) + 1) | COORD_HALF)) <= COORD_HALF &&
        abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(g_Task->pos.x) + 1)) <= TO_COORD(2)) {
        trigger = 1;
    }
    if (trigger == 0) {
        return;
    }
    SYS_ClearFlag(g_SceneEventFlags, g_Task->direction_08);
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
    }
    g_Task->header.step++;
    func_801F3FBC(0, 1);
    func_801F3FBC(1, 1);
}
