#include "area098_13.h"

MATCH void func_801F35B0(void) {
    Actor* task;
    s32    count;

    count = g_Task->unk_0A;
    if (count == g_Task->unk_06) {
        func_801F40D0(count);
        if (g_Task->unk_06 != 0) {
            g_Task->unk_06 -= 2;
        }
        g_Task->unk_0A = 0;
    } else {
        g_Task->unk_0A = count + 1;
    }
    func_801F42E8();
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_MessageRequest == 0x12 && D_80146875 == 0xC) {
        task         = g_Task;
        task->timer  = 0;
        task->vx     = 40960;
        task->vy     = 45056;
        task->unk_18 = 0;
        task->unk_1C = 0;
        g_Task->header.mode += 1;
    }
}
