#include "area098_13.h"

MATCH void func_801F35B0(void) {
    Actor* task;
    s32    count;

    count = SELF(Actor)->unk_0A;
    if (count == SELF(Actor)->unk_06) {
        func_801F40D0(count);
        if (SELF(Actor)->unk_06 != 0) {
            SELF(Actor)->unk_06 -= 2;
        }
        SELF(Actor)->unk_0A = 0;
    } else {
        SELF(Actor)->unk_0A = count + 1;
    }
    func_801F42E8();
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_UIMessageRequest == 0x12 && g_ScenarioState.step == 0xC) {
        task         = SELF(Actor);
        task->timer  = 0;
        task->vx     = 40960;
        task->vy     = 45056;
        task->unk_18 = 0;
        task->unk_1C = 0;
        SELF(Actor)->header.mode += 1;
    }
}
