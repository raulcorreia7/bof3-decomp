#include "engine/slus/slus.h"

/* resets the mode record. */
MATCH void Area_ResetScene(void) {
    Actor*       work;
    PartyMember* mode_work;

    work                               = g_Task;
    mode_work                          = g_Game.current;
    g_AreaCameraStep                   = 0;
    g_AreaCameraHeightStep             = 0;
    work->vx                           = 0;
    work->vy                           = 0;
    work->vz                           = 0;
    *(u8*)&mode_work->u.turn.hp_change = 3; /* FAKE: retail stores the byte. */
    if (g_Game.input & INPUT_DIRECTIONAL) {
        func_80167428();
    } else {
        g_Task->header.mode = 1;
    }
}
