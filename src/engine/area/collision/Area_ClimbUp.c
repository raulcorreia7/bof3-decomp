#include "engine/game/00/game_00.h"

/* func_801C5558 */
/* Raises the actor 16 units and enters the dismount step once it reaches the hold height of the ground ahead. */
MATCH void Area_ClimbUp(void) {
    Actor* work;
    u16    z;
    u8     facing;
    s32    reach;
    s32    ahead_x;
    s32    ahead_y;
    s32    ground;
    s16    hold_offset;

    work                   = SELF(Actor);
    z                      = COORD_INT(work->pos.z) + 16;
    facing                 = work->direction;
    COORD_INT(work->pos.z) = z;

    work    = SELF(Actor);
    reach   = work->voice_flags.scene_flag + 2;
    /* FAKE: non-const view of the facing table on the first read keeps retail's store order. */
    ahead_x = (*(Offset2(*)[8])g_FacingSteps)[facing].x * reach;
    ahead_y = g_FacingSteps[facing].y * reach;
    ground  = Area_HeightRead(work->pos.x.fixed + ahead_x, work->pos.y.fixed + ahead_y);

    hold_offset = g_AreaClimbHeightOffsets[g_Game.current->chr.character_id];

    work = SELF(Actor);
    if ((s16)COORD_INT(work->pos.z) >= ground - hold_offset) {
        work->header.step = 3;
    }

    Script_AnimStepLoop();
}
