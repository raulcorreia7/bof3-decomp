#include "engine/game/00/game_00.h"

/* func_801A2788 */
/* Runs the handler of the given mode once on the current actor. */
MATCH void Actor_RunMode(s32 mode_index) {
    ActorModeCallback* slot;

    slot = &g_ActorModes[mode_index & BYTE_MASK];
    (*slot)(g_CurrentActor);
}
