#include "area175_13.h"

MATCH void func_801F400C(void) {
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        g_Task->pos.x.fixed += D_801F5360[g_FrameCount & 0xF] << 11;
        g_Task->pos.y.fixed -= D_801F5360[g_FrameCount & 0xF] << 11;
        g_CurrentActor->unk_7E -= 2;
    } else {
        g_Task->pos.x.fixed = TO_COORD(44);
        g_Task->pos.y.fixed = TO_COORD(92);
        g_Task->unk_04      = 0;
    }
}
