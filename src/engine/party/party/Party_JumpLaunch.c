#include "engine/game/00/game_00.h"

/* func_801B744C */
/* Sets the jump velocity and gravity and plays the jump sound. */
MATCH void Party_JumpLaunch(void) {
    u8 rate; /* the g_RouteSpeedScale entry func_801BC4D0 calls the rate */

    if (Script_AnimStepOnce() & BYTE_MASK) {
        rate                 = g_RouteSpeedScale[g_Game.current->u.field.counter.unsigned_value];
        TASK(Actor)->timer   = 32 / rate;
        TASK(Actor)->vx      = g_FacingOffsets[TASK(Actor)->direction].x * rate * (TASK(Actor)->voice_flags.scene_flag + 1);
        TASK(Actor)->vy      = g_FacingOffsets[TASK(Actor)->direction].y * rate * (TASK(Actor)->voice_flags.scene_flag + 1);
        TASK(Actor)->vz      = (TASK(Actor)->voice_flags.scene_flag + 1) << 6;
        TASK(Actor)->gravity = -((TASK(Actor)->voice_flags.scene_flag + 1) * 8);
        if (TASK(Actor)->unk_05 == 0) {
            s32 dx;
            s32 dy;

            dx                    = TASK(Actor)->vx * TASK(Actor)->timer;
            dy                    = TASK(Actor)->vy * TASK(Actor)->timer;
            MEM(s32, 0x80149308u) = TASK(Actor)->pos.x.fixed + dx;
            MEM(s32, 0x8014930Cu) = TASK(Actor)->pos.y.fixed + dy;
            MEM(s16, 0x8014932Eu) = rate * 8;
        }
        Script_Request((TASK(Actor)->direction == FACING_RIGHT) ? 0x3AU : 0x3BU);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        TASK(Actor)->timer -= 1;
        TASK(Actor)->vz += TASK(Actor)->gravity;
        Actor_MovementUpdate();
        TASK(Actor)->unk_03 = PARTY_JUMP_STEP_TRAVEL;
    }
}
