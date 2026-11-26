#include "game_00.h"

MATCH void func_8019A6AC(void) {
    Actor* work;

    SELF(Actor)->timer--;
    if (SELF(Actor)->timer == 0) {
        SELF(Actor)->header.mode++;
        return;
    }
    SELF(Actor)->tint.bytes.rgb.r -= 6;
    SELF(Actor)->tint.bytes.rgb.g -= 6;
    SELF(Actor)->tint.bytes.rgb.b -= 6;
    Script_AnimStepLoop();
    work = SELF(Actor);
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
