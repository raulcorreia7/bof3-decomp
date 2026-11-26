#include "engine/game/00/game_00.h"

/* func_801C364C */
/* Starts the floor damage step with a damage row unless a cell under the actor has the wanted code. */
MATCH s32 Party_StartFloorDamage(s32 wanted_code, s32 damage_index, s32 find_facing) {
    s32 i;
    s32 route;
    s32 result;
    s32 enabled;

    if (Area_CellTestCorners(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, SELF(Actor)->voice_flags.scene_flag, wanted_code & BYTE_MASK, 0) & BYTE_MASK) {
        return 0;
    }
    enabled = find_facing & BYTE_MASK;
    /* FAKE: holds the loop init after the gate mask. */
    FAKE_BARRIER();
    i = 0;
    if (enabled) {
        for (;;) {
            route  = ((SELF(Actor)->direction ^ 0x4) + i) & 0x7;
            result = Game_TestPlacement(SELF(Actor)->pos.x.fixed + g_FacingSteps[route].x * 2, SELF(Actor)->pos.y.fixed + g_FacingSteps[route].y * 2, 0, COORD_INT(SELF(Actor)->pos.z)) & BYTE_MASK;
            /* FAKE: holds the increment after the probe call. */
            FAKE_BARRIER();
            i++;
            if (!result) {
                break;
            }
            if (i >= 8) {
                break;
            }
        }
        SELF(Actor)->direction = route ^ 0x4;
    }
    SELF(Actor)->header.mode  = 2;
    SELF(Actor)->header.step  = PARTY_MOVE_STEP_FLOOR_DAMAGE;
    SELF(Actor)->unk_03       = 0;
    SELF(Actor)->unk_04       = 0;
    SELF(Actor)->param.unk_0B = damage_index;
    return 1;
}
