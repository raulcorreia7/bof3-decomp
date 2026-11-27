#include "engine/game/00/game_00.h"

/* func_801BB8E8 */
MATCH void Actor_SnapFacing(u8 arg_a, u8 arg_b, u8 arg_c) {
    Actor* work;
    u8     current;

    work    = SELF(Actor);
    current = work->direction;

    if (current & 0x1) {
        return;
    }

    if (current == arg_a) {
        work->direction = arg_c;
    } else if (current == arg_b) {
        work->direction = arg_c;
    } else {
        work->direction = arg_c ^ 0x4;
    }
}
