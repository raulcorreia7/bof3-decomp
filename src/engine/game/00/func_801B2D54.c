#include "game_00.h"

MATCH void func_801B2D54(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        g_Game.current->u.field.mode.value = 0;
    }
}
