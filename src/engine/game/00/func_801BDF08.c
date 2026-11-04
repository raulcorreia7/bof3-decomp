#include "game_00.h"

MATCH s32 func_801BDF08(void) {
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

    work   = g_SpadWork;
    found  = 0;
    step_x = g_FacingSteps[work->direction_08].x;
    step_y = D_80181B98[work->direction_08 * 2];
    pos_x  = work->x.fixed + step_x;
    pos_y  = work->y.fixed + step_y;
    if (g_GameFlags & 0x1000) {
        pos_x += step_x;
        pos_y += step_y;
    }
    dist    = Area_ReadHeight(pos_x, pos_y);
    counter = g_SpadWork->z.part.integer;
    diff    = counter - dist;
    if (ABS(diff) > 0x100) {
        dist = counter;
    }
    for (i = 0, offset = 0; i < 34; i++, offset += ACTOR_SIZE) {
        if (((u8*)g_Actors)[offset] != 0 && !((&D_8014688F)[offset] & 0x80)) {
            rec = (Actor*)((u8*)g_Actors + offset);
            if (func_801BDD58(pos_x, pos_y, dist, g_SpadWork->state_70.byte, rec) & BYTE_MASK) {
                found        = 1;
                rec->roll_90 = FIELD(u16, D_80146918, offset) + 1;
            }
        }
    }
    if (found != 0) {
        g_GameState->counter_11C.u8_value = 3;
        g_SpadWork->unk_09                = 0;
    }
    return found;
}
