#include "area041_13.h"

MATCH void func_801F3E80(void) {
    TASK(Actor)->vx = 16384;
    func_801F4118();
    TASK(Actor)->unk_0A = 7;
    TASK(Actor)->unk_04 = 1;
    g_Game.current->u.field.unk_122 -= 2;
}
