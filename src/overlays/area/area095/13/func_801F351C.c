#include "area095_13.h"

MATCH void func_801F351C(void) {
    Actor* actor = g_SpadWork;

    if (actor->y.part.integer == 0x3A) {
        switch ((u16)(actor->x.part.integer - 0x40)) {
            case 0:
                actor->direction_08 = 3;
                func_801F3450(actor);
                return;
            case 2:
                actor->direction_08 = 7;
                func_801F3450(actor);
                return;
        }
    }
    g_ScriptState->cursor += 2;
}
