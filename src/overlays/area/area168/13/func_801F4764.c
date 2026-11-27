#include "area168_13.h"

MATCH void func_801F4764(void) {
    Actor* record;

    MESSAGE_REQUEST_CLEAR();
    if (g_UIMessageChoice == 3) {
        Scene_StartEvent(SCENE_EVENT_INN, 0x5);
        g_SceneEventState.selection = 0xFF;
    }
    record         = (u8*)g_ScriptWorkRecord;
    record->unk_18 = D_801F4F94[g_UIMessageChoice * 2];
    /* FAKE: retail reloads the selection byte after the 0x18 store. */
    FAKE_BARRIER();
    record->unk_1C = D_801F4F95[g_UIMessageChoice * 2];
}
