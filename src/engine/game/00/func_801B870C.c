#include "game_00.h"

MATCH void func_801B870C(void) {
    /* INFERRED: g_Game.current is an untyped record in this TU. */
    g_Game.current->u.field.mode_12B.u8_value = 5;
    D_801CD36C[g_Task->unk_03]();
    Actor_StepAnimLoop();
}
