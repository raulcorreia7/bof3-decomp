#include "area189_13.h"

MATCH void func_801F4D14(void) {
    u8* flags;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Game_ClearScriptActive();
        flags  = &D_80146871;
        *flags = *flags & 0xFE;
        if (D_801448EC != 0) {
            Game_RequestAreaChange(0x96, 0x180000, 0x300000, 1);
        } else {
            Game_RequestAreaChange(0xC1, 0x1A8000, 0x1C0000, 1);
        }
        D_801448EB = 0;
        D_801448EC = 0;
    }
}
