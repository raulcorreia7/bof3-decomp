#include "area107_13.h"

MATCH void func_801F2C74(void) {
    if (g_GameStateIndex != GAME_REQUEST_BATTLE) {
        if (g_BattleCount % 5 != 0) {
            ((Actor*)g_Task)->mode = 0;
        } else {
            Game_SetScriptActive();
            ((Actor*)g_Task)->mode = 2;
        }
    }
}
