#include "engine/game/00/game_00.h"

/* func_801B7950 */
/* Grabs the ladder and starts the climb. */
MATCH void Party_LadderUpGrab(void) {
    Actor* work;

    Area_ClimbStartGrab();
    work = SELF(Actor);
    work->unk_04++;
}
