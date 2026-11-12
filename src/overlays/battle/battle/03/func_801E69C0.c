#define GAME_SCRATCH_BASE_SCALAR
#include "battle_03.h"

MATCH void func_801E69C0(void) {
    u8 value;
    u8 next;

    value         = g_Task->unk_09;
    D_1F800002    = value;
    D_1F800001    = value;
    D_1F800000[0] = value;
    func_801D99AC(0, 0, 11);
    next           = g_Task->unk_09 + 1;
    g_Task->unk_09 = next;
    if (next == 0xFFu) {
        g_Task->header.mode += 1;
    }
}
