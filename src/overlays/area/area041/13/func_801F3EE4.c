#include "area041_13.h"

MATCH void func_801F3EE4(void) {
    func_801F4118();
    TASK(Actor)->unk_0A -= 1;
    if (TASK(Actor)->unk_0A == 0) {
        TASK(Actor)->unk_0A = 8;
        TASK(Actor)->unk_04 = 2;
    }
    g_Game.current->u.field.unk_122 -= 2;
}
