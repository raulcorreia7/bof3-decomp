#include "area042_13.h"
#include "menu/save_data.h"

/* func_801F4188 */
MATCH s32 Scene_EventBegin(void) {
    u8 i;
    u8 phase;

    if (SYS_TestFlag(g_SceneEventFlags, 0x12) && SYS_TestFlag(g_SceneEventFlags, 0x13) && SYS_TestFlag(g_SceneEventFlags, 0x14) && SYS_TestFlag(g_SceneEventFlags, 0x15) &&
        !SYS_TestFlag(g_SceneEventFlags, 0x11)) {
        Game_SetScriptActive();
        g_SceneEventState.step      = 0;
        g_SceneEventState.mode      = 7;
        g_SceneEventState.selection = 0x3C;
        phase                       = g_SaveData.scene_event_timer / 30;
        if (phase >= 6) {
            D_801F56F8 = 2;
        } else if (phase == 5) {
            D_801F56F8 = 1;
        } else {
            D_801F56F8 = 0;
        }
        for (i = 0; i < ACTOR_COUNT; i++) {
            if ((g_Actors[i].header.flags & ACTOR_FLAG_IN_USE) && g_Actors[i].unk_06 == 9 && (u8)(g_Actors[i].unk_05 - 0x5C) < 3 && SYS_TestFlag(D_80144FC4, D_801F56F8 + 0x5C)) {
                g_Self = &g_Actors[i];
                Script_Select(1);
                g_Self = g_CurrentActor;
                break;
            }
        }
        return 1;
    }
    return 0;
}
