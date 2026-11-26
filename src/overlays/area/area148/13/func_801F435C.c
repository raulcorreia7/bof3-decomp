#include "area148_13.h"

MATCH void func_801F435C(void) {
    Actor* actor;

    if (g_GameStateIndex != 0) {
        func_801F4798(&SELF(Actor)->pos, &SELF(Actor)->unk_18);
        return;
    }
    actor = SELF(Actor);
    actor->unk_18 += actor->vx;
    actor->timer -= 1;
    actor->unk_1C += actor->vy;
    func_801F4798(&SELF(Actor)->pos, &SELF(Actor)->unk_18);
    func_801F4614();
    if (SELF(Actor)->timer == 0) {
        SELF(Actor)->direction = (SELF(Actor)->direction + 2) & 0x7;
        func_801F45C8();
        SELF(Actor)->timer  = 80;
        SELF(Actor)->unk_0A = RANDOM_MOD(45);
        if (SELF(Actor)->unk_0A != 0) {
            SELF(Actor)->timer -= 1;
            SELF(Actor)->header.mode = 2;
        }
    }
}
