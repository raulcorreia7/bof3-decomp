#include "game_00.h"

MATCH void func_8019A6AC(void) {
    Actor* work;

    TASK(Actor)->timer--;
    if (TASK(Actor)->timer == 0) {
        TASK(Actor)->header.mode++;
        return;
    }
    TASK(Actor)->tint.bytes.rgb.r -= 6;
    TASK(Actor)->tint.bytes.rgb.g -= 6;
    TASK(Actor)->tint.bytes.rgb.b -= 6;
    Script_AnimStepLoop();
    work = TASK(Actor);
    if (work->unk_05 == 6) {
        if ((work->timer & 0x1) != 0) {
            work->screen_y++;
        }
        Area_AddActor();
    } else {
        if ((work->timer & 0x1) != 0) {
            work->vy--;
        }
        Area_AddGridActor();
    }
}
