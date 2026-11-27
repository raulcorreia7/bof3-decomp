#include "engine/game/00/game_00.h"

/* func_801BDF08 */
MATCH s32 Area_GetActorFacingStepX(void) {
    Actor* work;
    Actor* rec;
    s32    step_x;
    s32    step_y;
    s32    pos_x;
    s32    pos_y;
    s16    dist;
    s16    counter;
    s32    diff;
    s32    i;
    s32    offset;
    s8     found;

    work   = SELF(Actor);
    found  = 0;
    step_x = g_FacingSteps[work->direction].x;
    step_y = g_FacingSteps[work->direction].y;
    pos_x  = work->pos.x.fixed + step_x;
    pos_y  = work->pos.y.fixed + step_y;
    if (g_Game.flags & 0x1000) {
        pos_x += step_x;
        pos_y += step_y;
    }
    dist    = Area_HeightRead(pos_x, pos_y);
    counter = COORD_INT(SELF(Actor)->pos.z);
    diff    = counter - dist;
    if (ABS(diff) > 0x100) {
        dist = counter;
    }
    for (i = 0, offset = 0; i < 34; i++, offset += ACTOR_SIZE) {
        if (((u8*)g_Actors)[offset] != 0 && !((&g_Actors[0].option_flags)[offset] & 0x80)) {
            rec = (Actor*)((u8*)g_Actors + offset);
            if (Actor_IsInRange(pos_x, pos_y, dist, SELF(Actor)->voice_flags.scene_flag, rec) & BYTE_MASK) {
                found        = 1;
                rec->roll_90 = FIELD(u16, D_80146918, offset) + 1;
            }
        }
    }
    if (found != 0) {
        g_Game.current->u.field.counter.unsigned_value = 3;
        SELF(Actor)->timer                             = 0;
    }
    return found;
}
