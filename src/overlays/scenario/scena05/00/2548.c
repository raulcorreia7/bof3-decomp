#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9148(void) {
    u8* step = &D_80146875;

    switch (*step) {
        case 0:
            if (*g_ScriptVars == 0x23) {
                *step = 1;
            }
            break;
        case 1:
            if (*g_ScriptVars == 0x23) {
                *step = 4;
                SYS_SetFlag(g_SceneFlags, 24);
                if (SYS_TestFlag(g_SceneFlags, 23) == 0) {
                    D_80146866 = 4;
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, 0x270000, 0xAD0000, FACING_RIGHT);
                    g_GamePrevSelection = 0xFF;
                }
                if (SYS_TestFlag(g_SceneFlags, 22) == 0) {
                    D_80146866 = 1;
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, 0x270000, 0xAD0000, 0x83);
                    g_GamePrevSelection = 0xFF;
                }
            }
            break;
        case 4:
            if (*g_ScriptVars == 3) {
                SYS_SetFlag(g_SceneFlags, 25);
                SYS_SetFlag(g_SceneFlags, 20);
                SYS_SetFlag(g_SceneFlags, 26);
                D_80146865 = 0;
                D_80146866 = 0;
                D_80146867 = 0;
                Game_ClearScriptActive();
                *step      = 0;
                D_80146874 = 0;
            }
            break;
    }
}

MATCH void func_801F92EC(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            MESSAGE_START_WAIT(0);
            *state = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state     = 0;
                D_80146874 = 0;
            }
            return;
    }
}

MATCH void func_801F937C(void) {
}
