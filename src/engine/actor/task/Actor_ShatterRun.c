#include "engine/game/00/game_00.h"

/* func_8019F818 */
/* Spins the shards and runs the dust of a broken actor. */
MATCH void Actor_ShatterRun(Actor* actor) {
    Actor_ShatterSpinShards();
    Actor_ShatterRunDust();
}
