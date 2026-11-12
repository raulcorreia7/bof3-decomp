#include "area095_13.h"

MATCH void func_801F351C(void) {
    Actor* actor = g_Task;

    if (COORD_INT(actor->pos.y) == 58) {
        switch ((u16)(COORD_INT(actor->pos.x) - 0x40)) {
            case 0:
                actor->direction_08 = FACING_RIGHT;
                Area_StartDirectionalScript(actor);
                return;
            case 2:
                actor->direction_08 = FACING_LEFT;
                Area_StartDirectionalScript(actor);
                return;
        }
    }
    g_ScriptState->cursor += 2;
}
