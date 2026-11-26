#include "game_00.h"

MATCH void func_801B870C(void) {
    /* INFERRED: g_Game.current is an untyped work record in this TU. Offset 0x12B is
     * a u8 flag (also written by Area_ClimbDismountExit). Promotion to a named field needs
     * a proven struct owner/layout from callers, strides, and field accesses. */
    g_Game.current->u.field.mode.unsigned_value = 5;
    D_801CD36C[TASK(Actor)->unk_03]();
    Script_AnimStepLoop();
}
