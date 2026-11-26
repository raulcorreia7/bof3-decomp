#include "engine/game/00/game_00.h"

/* func_801B870C */
/* Runs the cell walk sub-step the actor's unk_03 selects, then advances the animation. */
MATCH void Party_CellWalkRun(void) {
    /* INFERRED: g_Game.current is an untyped work record in this TU. Offset 0x12B is
     * a u8 flag (also written by Area_ClimbDismountExit). Promotion to a named field needs
     * a proven struct owner/layout from callers, strides, and field accesses. */
    g_Game.current->u.field.mode.unsigned_value = 5;
    g_PartyCellWalkSteps[TASK(Actor)->unk_03]();
    Script_AnimStepLoop();
}
