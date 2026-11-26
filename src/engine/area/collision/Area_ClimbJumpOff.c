#include "engine/game/00/game_00.h"

/* func_801C56E4 */
/* Jumps off the ladder: flips the facing, plays the jump animation, sets gravity -8 and enters the jump step at its fall sub-step. */
MATCH void Area_ClimbJumpOff(void) {
    u8     animation;
    Actor* actor;
    Actor* actor_b;

    actor            = SELF(Actor);
    actor->direction = (actor->direction ^ 0x4);
    animation        = 59;
    if (SELF(Actor)->direction == FACING_RIGHT) {
        animation = 58;
    }
    Script_Request(animation);
    GFX_PaletteLoad((SELF(Actor)->unk_05 << 6) + GAME_PALETTE_STAGE, 0);
    Actor_ClearVelocity();
    actor_b                  = SELF(Actor);
    actor_b->gravity         = -8;
    actor_b->header.mode     = 2;
    SELF(Actor)->header.step = PARTY_MOVE_STEP_JUMP;
    SELF(Actor)->unk_03      = PARTY_JUMP_STEP_FALL;
}
