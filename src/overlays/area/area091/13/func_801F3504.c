#include "area091_13.h"

MATCH void func_801F3504(void) {
    g_Task->unk_0A -= 1;
    if (g_Task->unk_0A == 0) {
        D_80146867     = 1;
        g_Task->unk_04 = 0;
        g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
        g_CurrentActor->unk_7E += 1;
        Game_ClearScriptActive();
    }
    func_801F2ED4(g_Task->unk_0A * 0xA, 0xFF);
}
