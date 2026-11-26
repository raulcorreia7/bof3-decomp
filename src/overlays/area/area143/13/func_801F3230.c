#include "area143_13.h"

MATCH void func_801F3230(void) {
    if (g_AreaSceneMode != 1) {
        return;
    }
    SELF(Actor)->param.unk_0B = 0;
    SELF(Actor)->pos.z.fixed  = 0;
    SELF(Actor)->header.step += 1;
}
