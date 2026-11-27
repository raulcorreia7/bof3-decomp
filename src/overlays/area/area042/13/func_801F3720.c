#include "area042_13.h"

MATCH void func_801F3720(void) {
    Actor* work;

    func_801F37A8(SELF(Actor)->pos.z.fixed, (SELF(Actor)->param.unk_0B & 0xF8) << 0x10);
    work = SELF(Actor);
    work->param.unk_0B -= 4;
    work->pos.z.fixed += 4;
    if (SELF(Actor)->pos.z.fixed >= -0x7F) {
        g_SceneEventState.step = 4;
        Actor_Clear();
    }
}
