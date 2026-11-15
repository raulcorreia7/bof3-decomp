#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8564(void) {
    switch (D_80146875) {
        case 0:
            D_80146866 = 2;
            D_80146875 = 1;
            func_8019FA28(0x34, TO_COORD(0x3E), TO_COORD(0x27), 0x84);
            g_GamePrevSelection = 0xFF;
            break;
        case 1:
            if (g_ScriptVars[0] == 3) {
                func_801C601C(0);
                D_80146875 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0xD) {
                func_801BFE34(TO_COORD(0x3E), TO_COORD(0x20), 0x11);
                D_80146875 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0xF) {
                func_801C7A54(0x11);
                D_80146875 = 7;
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 0x14) {
                func_801BE1B0(0);
                D_80146875 = 8;
            }
            break;
        case 8:
            if (g_ScriptVars[0] == 0x16) {
                D_80146866 = 3;
                D_80146875 = 9;
                SYS_SetFlag(g_SceneFlags, 5);
                func_8019FA28(0x34, TO_COORD(0x85), TO_COORD(0xF), 0x85);
                g_GamePrevSelection = 0x3B;
            }
            break;
        case 9:
            if (g_ScriptVars[0] == 8) {
                g_GameFlags |= 0x20;
                SYS_SetFlag(g_SceneFlags, 6);
                Game_ClearScriptActive();
                D_80146865 = 0;
                D_80146866 = 0;
                D_80146875 = 0;
                D_80146874 = 5;
            }
            break;
        case 20:
            Message_StartAreaMessage(0xB);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            D_80146875       = 0x15;
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScriptVars[0] = 0;
                D_80146866      = 0;
                D_80146875      = 0;
                D_80146874      = 5;
            }
            break;
    }
}
