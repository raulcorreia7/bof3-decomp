#include "area175_13.h"

MATCH void func_801F4594(Actor* actor) {
    actor->header.mode = 4;
    actor->unk_78      = 2;
    actor->unk_77      = 0xD;
    actor->unk_7E      = 0;
    SYS_SetFlag(g_SceneEventFlags, 149);
    func_801BE1B0(4);
    g_ScriptVars[0] = 0;
}
