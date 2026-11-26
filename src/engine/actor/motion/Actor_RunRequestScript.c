#include "engine/game/00/game_00.h"

/* func_801A1A24 */
/* Mode 6: raises the script request bit every frame unless the live flag is 8. */
MATCH void Actor_RunRequestScript(u8* record) {
    Actor* work = TASK(Actor);

    if (work->unk_06 != 8) {
        record[0x74] |= ACTOR_INTERACTION_SCRIPT_REQUEST;
    }
}
