#include "area170_13.h"

MATCH void func_801F5708(void) {
    Actor* work;
    s32    request;

    work = SELF(Actor);
    if (SYS_TestFlag(g_SceneEventFlags, 121) != 0) {
        request = 1;
    } else if (Item_Add(ITEM_CATEGORY_WEAPON, WEAPON_HE_SHELLS, 1, 0) == 0) {
        request = 3;
    } else {
        SYS_SetFlag(g_SceneEventFlags, 121);
        Script_Select(1);
        UI_MessageStartArea(MSG_AREA170_FOUND_HE_SHELLS);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        goto done;
    }
    UI_MessageRequest(request);
done:
    Scene_SetupParty(13);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    SELF_SET(work);
}
