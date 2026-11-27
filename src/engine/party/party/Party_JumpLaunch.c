#include "engine/game/00/game_00.h"

/* func_801B744C */
/* Sets the jump velocity and gravity and plays the jump sound. */
MATCH void Party_JumpLaunch(void) {
    u8 rate; /* the g_RouteSpeedScale entry func_801BC4D0 calls the rate */

    if (Script_AnimStepOnce() & BYTE_MASK) {
        rate                 = g_RouteSpeedScale[g_Game.current->u.field.counter.unsigned_value];
        SELF(Actor)->timer   = 32 / rate;
        SELF(Actor)->vx      = g_FacingOffsets[SELF(Actor)->direction].x * rate * (SELF(Actor)->voice_flags.scene_flag + 1);
        SELF(Actor)->vy      = g_FacingOffsets[SELF(Actor)->direction].y * rate * (SELF(Actor)->voice_flags.scene_flag + 1);
        SELF(Actor)->vz      = (SELF(Actor)->voice_flags.scene_flag + 1) << 6;
        SELF(Actor)->gravity = -((SELF(Actor)->voice_flags.scene_flag + 1) * 8);
        if (SELF(Actor)->unk_05 == 0) {
            s32 dx;
            s32 dy;

            dx                    = SELF(Actor)->vx * SELF(Actor)->timer;
            dy                    = SELF(Actor)->vy * SELF(Actor)->timer;
            MEM(s32, 0x80149308u) = SELF(Actor)->pos.x.fixed + dx;
            MEM(s32, 0x8014930Cu) = SELF(Actor)->pos.y.fixed + dy;
            MEM(s16, 0x8014932Eu) = rate * 8;
        }
        Script_Request((SELF(Actor)->direction == FACING_RIGHT) ? 0x3AU : 0x3BU);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        SELF(Actor)->timer -= 1;
        SELF(Actor)->vz += SELF(Actor)->gravity;
        Actor_MovementUpdate();
        SELF(Actor)->unk_03 = PARTY_JUMP_STEP_TRAVEL;
    }
}
