#include "area098_13.h"

MATCH void func_801F3AA8(void) {
    u8 temp_v0;
    u8 temp_v1;

    temp_v1 = g_SpadWork->unk_06;
    g_SpadWork->unk_06 = temp_v1 + 1;
    if (!(temp_v1 & 3)) {
        Area_ClaimSpawnSlot();
    }
    func_801F5940();
    Area_StepSpawnSlots();
    temp_v0 = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        s32 x;
        s32 y;
        s32 z;
        u8  t;

        x                 = g_SpadWork->unk_64;
        y                 = g_SpadWork->unk_68;
        g_SpadWork->unk_0C = -0x1000;
        g_SpadWork->unk_10 = -0x400;
        do {
        } while (0); /* FAKE: the empty loop keeps the unk_01/unk_6C loads below the constant stores. */
        t                  = g_SpadWork->unk_01;
        z                  = g_SpadWork->unk_6C;
        t                  = t + 1;
        g_SpadWork->unk_18 = x;
        g_SpadWork->unk_1C = y;
        g_SpadWork->gravity = z;
        do {
        } while (0); /* FAKE: the empty loop keeps the byte store last in retail's schedule. */
        g_SpadWork->unk_01 = t;
    }
}
