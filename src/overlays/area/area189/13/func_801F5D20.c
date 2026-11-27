#include "area189_13.h"

MATCH void func_801F5D20(void) {
    Actor_ClearVelocity();
    SELF(Actor)->script_record                  = 0;
    g_Game.current->u.field.mode.unsigned_value = 0;
    SELF(Actor)->header.step                    = 2;
}
