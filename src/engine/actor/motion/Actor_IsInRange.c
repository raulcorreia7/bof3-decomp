#include "engine/game/00/game_00.h"

/* func_801BDD58 */
/* Returns whether a point lies within reach of an actor record. */
MATCH u8 Actor_IsInRange(s32 pos_x, s32 pos_y, s16 z, s32 reach, Actor* record) {
    s32 step_x;
    s32 step_y;
    s32 x;
    s32 y;
    s32 height;
    s32 bound;

    height = abs(record->pos.z.part.integer - z);
    reach += record->voice_flags.scene_flag;
    if (height > (reach << 7) + 0x100) {
        return 0;
    }
    step_x = record->vx * record->timer;
    step_y = record->vy * record->timer;
    x      = record->pos.x.fixed + step_x;
    y      = record->pos.y.fixed + step_y;
    bound  = (reach + 2) << 15;
    if (abs(pos_x - x) < bound) {
        if (abs(pos_y - y) < bound) {
            return 1;
        }
    }
    return 0;
}
