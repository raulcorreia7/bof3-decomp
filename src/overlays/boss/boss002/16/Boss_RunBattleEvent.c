#include "boss002_16.h"

MATCH u8 Boss_RunBattleEvent(u32 mode) {
    if ((u8)mode == 0) {
        if BATTLE_IS_VICTORY () {
            g_MenuPanelMode = 2;
            Message_StartAreaMessage(MSG_025);
        }
    }
    return 0;
}
