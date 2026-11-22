#include "area148_13.h"

MATCH void func_801F435C(void) {
    Actor* actor;

    if (g_GameStateIndex != 0) {
        func_801F4798(&TASK(Actor)->pos, &TASK(Actor)->unk_18);
        return;
    }
    actor = TASK(Actor);
    actor->unk_18 += actor->vx;
    actor->timer -= 1;
    actor->unk_1C += actor->vy;
    func_801F4798(&TASK(Actor)->pos, &TASK(Actor)->unk_18);
    func_801F4614();
    if (TASK(Actor)->timer == 0) {
        TASK(Actor)->direction = (TASK(Actor)->direction + 2) & 0x7;
        func_801F45C8();
        TASK(Actor)->timer  = 80;
        TASK(Actor)->unk_0A = RANDOM_MOD(45);
        if (TASK(Actor)->unk_0A != 0) {
            TASK(Actor)->timer -= 1;
            TASK(Actor)->header.mode = 2;
        }
    }
}
