#include "area098_13.h"

MATCH void func_801F5E1C(void) {
    s8* flag;

    flag = &D_801448EC;
    if (*flag == 0 && g_GameStateIndex != 2) {
        D_80145040 = D_80145EC4[0];
        D_80145044 = D_80145EC8;
        D_80145048 = g_GameAreaId;
        func_8019FA28(0x62, 0x380000, 0x2C0000, 1);
        Game_ClearScriptActive();
        D_801448EB = 0;
        *flag      = 0;
    }
}
