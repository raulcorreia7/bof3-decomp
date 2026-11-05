#include "area170_13.h"

MATCH void func_801F5708(void) {
    Actor* work;
    s32    request;

    work = g_Task;
    if (SYS_TestFlag(g_SceneEventFlags, 0x79) != 0) {
        request = 1;
    } else if (Item_Add(ITEM_CAT_WEAPON, 0x4B, 1, 0) == 0) {
        request = 3;
    } else {
        SYS_SetFlag(g_SceneEventFlags, 0x79);
        Actor_SelectScript(1);
        Message_StartAreaMessage(0x22);
        SND_PlayCue(EMI_CUE_ID(1, 6));
        goto done;
    }
    Resource_RequestArea(request);
done:
    func_801BE1B0(0xD);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    TASK_SET(work);
}
