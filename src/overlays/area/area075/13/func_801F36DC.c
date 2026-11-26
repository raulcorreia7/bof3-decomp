#include "area075_13.h"

MATCH void func_801F36DC(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x07));
    } else {
        SELF(Actor)->pos.y.fixed = g_AreaScrollTargetY;
        g_ScriptState->cursor -= 2;
    }
}
