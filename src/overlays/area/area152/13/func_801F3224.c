#include "area152_13.h"

MATCH void func_801F3224(void) {
    u8* scratch;
    u8* check;

    Actor_SetScreenOrigin();

    scratch = SELF(u8);
    scratch[0x09] -= 1;

    check = SELF(u8);
    *(s32*)(scratch + 0x40) -= 0x2000;

    if (check[0x09] == 0) {
        if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            Actor_Clear();
            return;
        }
        check[0x48]              = 0;
        SELF(Actor)->header.mode = 1;
        return;
    }

    Area_AddActor();
}
