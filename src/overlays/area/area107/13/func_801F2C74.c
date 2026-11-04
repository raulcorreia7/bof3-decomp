#include "area107_13.h"

MATCH void func_801F2C74(void) {
    if (g_GameStateIndex != 3) {
        if (g_BattleCount % 5 != 0) {
            ((Actor*)g_SpadWork)->unk_01 = 0;
        } else {
            Game_SetScriptActive();
            ((Actor*)g_SpadWork)->unk_01 = 2;
        }
    }
}
