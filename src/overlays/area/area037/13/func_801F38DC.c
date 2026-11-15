#include "area037_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F38DC(void) {
    s8* state;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SYS_SetFlag(state + 0x63C, 114);
                Game_RequestAreaChange(AREA_ID_WYNDIA_LOWER, TO_COORD_HALF(44), TO_COORD(39), FACING_UP);
                g_GameRequestKind = 0xFE;
                *state            = *state + 1;
            }
            break;
        case 1:
            if (g_GameStateIndex == 0) {
                Message_StartAreaMessage(0xB5);
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
                *state           = *state + 1;
            }
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                UI_SetMode(1);
                g_AreaDrawFlags = 0x1F;
                *state          = *state + 1;
            }
            break;
        case 3:
            if (WINDOW_EFFECT_IDLE()) {
                Game_ClearScriptActive();
                g_SceneEventMode = 0;
                *state           = 0;
                D_80146867       = 0;
            }
            break;
    }
}
#else
INCLUDE_ASM(func_801F38DC);
#endif
