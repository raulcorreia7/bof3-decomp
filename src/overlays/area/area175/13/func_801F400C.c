#include "area175_13.h"

MATCH void func_801F400C(void) {
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        SELF(Actor)->pos.x.fixed += D_801F5360[g_FrameCount & 0xF] << 11;
        SELF(Actor)->pos.y.fixed -= D_801F5360[g_FrameCount & 0xF] << 11;
        g_CurrentActor->unk_7E -= 2;
    } else {
        SELF(Actor)->pos.x.fixed = TO_COORD(44);
        SELF(Actor)->pos.y.fixed = TO_COORD(92);
        SELF(Actor)->unk_04      = 0;
    }
}
