#include "boss002_16.h"

MATCH u8 Boss_HandleBattleEvent(u32 mode) {
    if ((u8)mode == 0) {
        if BATTLE_IS_VICTORY () {
            g_MenuPanelMode = 2;
            Message_StartAreaMessage(0x19);
        }
    }
    return 0;
}
