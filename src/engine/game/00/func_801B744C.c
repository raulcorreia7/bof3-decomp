#include "game_00.h"

MATCH void func_801B744C(void) {
    u8 rate; /* the g_RouteSpeedScale entry func_801BC4D0 calls the rate */

    if (func_8014DAEC() & BYTE_MASK) {
        rate                = g_RouteSpeedScale[g_GameState->counter_11C.u8_value];
        g_SpadWork->unk_09  = 0x20 / rate;
        g_SpadWork->unk_0C  = g_FacingOffsets[g_SpadWork->direction_08].x * rate * (g_SpadWork->state_70.byte + 1);
        g_SpadWork->unk_10  = g_FacingOffsets[g_SpadWork->direction_08].y * rate * (g_SpadWork->state_70.byte + 1);
        g_SpadWork->vz      = (g_SpadWork->state_70.byte + 1) << 6;
        g_SpadWork->gravity = -((g_SpadWork->state_70.byte + 1) * 8);
        if (g_SpadWork->unk_05 == 0) {
            s32 dx;
            s32 dy;

            dx                    = g_SpadWork->unk_0C * g_SpadWork->unk_09;
            dy                    = g_SpadWork->unk_10 * g_SpadWork->unk_09;
            MEM(s32, 0x80149308u) = g_SpadWork->x.fixed + dx;
            MEM(s32, 0x8014930Cu) = g_SpadWork->y.fixed + dy;
            MEM(s16, 0x8014932Eu) = rate * 8;
        }
        Actor_RequestScript((g_SpadWork->direction_08 == 3) ? 0x3AU : 0x3BU);
        SND_PlayCue(EMI_CUE_ID(1, 4));
        g_SpadWork->unk_09 -= 1;
        g_SpadWork->vz += g_SpadWork->gravity;
        func_801B0DFC();
        g_SpadWork->unk_03 = 2;
    }
}
