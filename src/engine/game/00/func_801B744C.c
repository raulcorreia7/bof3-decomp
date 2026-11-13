#include "game_00.h"

MATCH void func_801B744C(void) {
    u8 rate; /* the g_RouteSpeedScale entry func_801BC4D0 calls the rate */

    if (Actor_StepAnimOnce() & BYTE_MASK) {
        rate            = g_RouteSpeedScale[g_Game.current->u.field.counter_11C.u8_value];
        g_Task->timer   = 32 / rate;
        g_Task->vx      = g_FacingOffsets[g_Task->direction_08].x * rate * (g_Task->state_70.byte + 1);
        g_Task->vy      = g_FacingOffsets[g_Task->direction_08].y * rate * (g_Task->state_70.byte + 1);
        g_Task->vz      = (g_Task->state_70.byte + 1) << 6;
        g_Task->gravity = -((g_Task->state_70.byte + 1) * 8);
        if (g_Task->unk_05 == 0) {
            s32 dx;
            s32 dy;

            dx                    = g_Task->vx * g_Task->timer;
            dy                    = g_Task->vy * g_Task->timer;
            MEM(s32, 0x80149308u) = g_Task->pos.x.fixed + dx;
            MEM(s32, 0x8014930Cu) = g_Task->pos.y.fixed + dy;
            MEM(s16, 0x8014932Eu) = rate * 8;
        }
        Actor_RequestScript((g_Task->direction_08 == FACING_RIGHT) ? 0x3AU : 0x3BU);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        g_Task->timer -= 1;
        g_Task->vz += g_Task->gravity;
        Actor_UpdateMovement();
        g_Task->unk_03 = 2;
    }
}
