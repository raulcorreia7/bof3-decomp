#include "area141_13.h"

MATCH void func_801F4230(Actor* actor) {
    switch (actor->unk_7C) {
        case 0xC000:
            func_801F4300(&D_801F4D94, 0);
            func_801F4300(&D_801F4D94 + 5, 0);
            break;
        case 0xC001:
            Game_SetScriptActive();
            Char_RebuildPartyStats();
            g_SceneEventMode = 0x34;
            g_SceneEventStep = 0;
            break;
        case 0xC002:
            Game_SetScriptActive();
            g_SceneEventMode = 0x34;
            g_SceneEventStep = 10;
            break;
    }
}
