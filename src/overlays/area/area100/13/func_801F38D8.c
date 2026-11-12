#include "area100_13.h"

MATCH void func_801F38D8(void) {
    ActorSlot* slot;
    u8         index;

    switch (g_SceneEventStep) {
        case 0:
            func_801C601C(0);
            g_SceneEventStep = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 1) {
                index = Actor_FindFreeSlot() & BYTE_MASK;
                if (index != 0xFF) {
                    slot               = &g_ActorSlots[index];
                    slot->header.flags = ACTOR_FLAG_IN_USE;
                    slot->type         = 0x9B;
                    slot->pos.x.fixed  = 0x460000;
                    slot->pos.y.fixed  = 0x340000;
                }
                D_801448EE       = 0x1E;
                g_SceneEventStep = 2;
            }
            break;
        case 2: {
            u16* timer = &D_801448EE;

            if (TIMER_EXPIRED(*timer)) {
                g_SceneEventStep = 3;
                g_ScriptVars[0]++;
            }
        } break;
        case 3:
            if (g_ScriptVars[0] == 0) {
                Message_StartAreaMessage(3);
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
                g_SceneEventStep = 4;
            }
            break;
        case 4:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
    }
}
