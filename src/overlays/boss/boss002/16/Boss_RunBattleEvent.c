#include "boss002_16.h"

MATCH u8 Boss_RunBattleEvent(u32 mode) {
    if ((u8)mode == 0) {
        if BATTLE_IS_VICTORY () {
            g_UIPanelMode = 2;
            UI_MessageStartArea(MSG_BOSS002_025);
        }
    }
    return 0;
}
