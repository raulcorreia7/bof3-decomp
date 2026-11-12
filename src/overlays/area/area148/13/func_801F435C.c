#include "area148_13.h"

MATCH void func_801F435C(void) {
    Actor* actor;

    if (g_GameStateIndex != 0) {
        func_801F4798(&g_Task->pos, &g_Task->unk_18);
        return;
    }
    actor = g_Task;
    actor->unk_18 += actor->vx;
    actor->timer -= 1;
    actor->unk_1C += actor->vy;
    func_801F4798(&g_Task->pos, &g_Task->unk_18);
    func_801F4614();
    if (g_Task->timer == 0) {
        g_Task->direction_08 = (g_Task->direction_08 + 2) & 0x7;
        func_801F45C8();
        g_Task->timer  = 80;
        g_Task->unk_0A = RANDOM_MOD(45);
        if (g_Task->unk_0A != 0) {
            g_Task->timer -= 1;
            g_Task->header.mode = 2;
        }
    }
}
