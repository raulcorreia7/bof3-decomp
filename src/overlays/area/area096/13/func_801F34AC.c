#include "area096_13.h"

MATCH void func_801F34AC(void) {
    Actor* actor = g_Task;

    if (COORD_INT(actor->y) == 0x3A) {
        switch ((u16)(COORD_INT(actor->x) - 0x40)) {
            case 0:
                actor->direction_08 = 3;
                Area_StartDirectionalScript(actor);
                return;
            case 2:
                actor->direction_08 = 7;
                Area_StartDirectionalScript(actor);
                return;
        }
    }
    g_ScriptState->cursor += 2;
}
