#include "area041_13.h"

MATCH void func_801F3EE4(void) {
    func_801F4118();
    SELF(Actor)->unk_0A -= 1;
    if (SELF(Actor)->unk_0A == 0) {
        SELF(Actor)->unk_0A = 8;
        SELF(Actor)->unk_04 = 2;
    }
    g_Game.current->u.field.unk_122 -= 2;
}
