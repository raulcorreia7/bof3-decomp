#include "area111_13.h"

MATCH void func_801F2CFC(void) {
    u8     remaining;
    Actor* actor;

    func_801F2DA0(&g_SpadWork->x, (s16)g_SpadWork->unk_2E, (s16)g_SpadWork->unk_30);
    actor     = g_SpadWork;
    remaining = --actor->unk_09;
    actor->unk_2E += 0x40;
    actor->unk_30 += 0x40;
    if (remaining == 0) {
        g_SpadWork->unk_01++;
    }
}
