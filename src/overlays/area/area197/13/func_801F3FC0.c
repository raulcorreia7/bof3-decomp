#include "area197_13.h"

MATCH void func_801F3FC0(void) {
    if (g_Task->unk_0A != 0) {
        g_Task->pos.x.fixed += D_801F4A88[g_Task->unk_0A & 0xF] << 11;
        g_Task->pos.y.fixed -= D_801F4A88[g_Task->unk_0A & 0xF] << 11;
        g_Task->unk_0A -= 1;
        g_CurrentActor->unk_7E -= 2;
    } else {
        g_Task->unk_04 = 0;
    }
}
