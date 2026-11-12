#include "area170_13.h"

MATCH void func_801F5708(void) {
    Actor* work;
    s32    request;

    work = g_Task;
    if (SYS_TestFlag(g_SceneEventFlags, 121) != 0) {
        request = 1;
    } else if (Item_Add(ITEM_CAT_WEAPON, WEAPON_HE_SHELLS, 1, 0) == 0) {
        request = 3;
    } else {
        SYS_SetFlag(g_SceneEventFlags, 121);
        Actor_SelectScript(1);
        Message_StartAreaMessage(34);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        goto done;
    }
    Message_Request(request);
done:
    func_801BE1B0(13);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    TASK_SET(work);
}
