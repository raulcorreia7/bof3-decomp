#include "area189_13.h"

MATCH void func_801F6088(void) {
    s32 i;
    u16 amount;
    u16 loss;

    for (i = 0; i < 7; i++) {
        amount = (g_Characters[i].base.max_hp + 25) / 50;
        loss   = g_Characters[i].hp;
        if (amount < loss) {
            loss = amount;
        } else {
            loss--;
        }
        g_Characters[i].hp -= loss;
    }
}
