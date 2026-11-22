#include "area098_13.h"

MATCH void func_801F35B0(void) {
    Actor* task;
    s32    count;

    count = TASK(Actor)->unk_0A;
    if (count == TASK(Actor)->unk_06) {
        func_801F40D0(count);
        if (TASK(Actor)->unk_06 != 0) {
            TASK(Actor)->unk_06 -= 2;
        }
        TASK(Actor)->unk_0A = 0;
    } else {
        TASK(Actor)->unk_0A = count + 1;
    }
    func_801F42E8();
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_UiMessageRequest == 0x12 && g_ScenarioState.step == 0xC) {
        task         = TASK(Actor);
        task->timer  = 0;
        task->vx     = 40960;
        task->vy     = 45056;
        task->unk_18 = 0;
        task->unk_1C = 0;
        TASK(Actor)->header.mode += 1;
    }
}
