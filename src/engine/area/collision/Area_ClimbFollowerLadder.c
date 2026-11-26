#include "engine/game/00/game_00.h"

/* func_801BD83C */
/* Compares the height of the member being followed with the actor's own and climbs up, climbs down or jumps off. */
MATCH void Area_ClimbFollowerLadder(void) {
    s32 alt;
    s32 diff;
    s32 result;
    s32 type;
    u16 screen_y;
    u8  mode;
    s32 offset;
    s32 value;

    offset   = TASK(Actor)->unk_06 * BATTLE_PARTY_STRIDE;
    mode     = (&g_Game.members[0].u.field.mode.unsigned_value)[offset];
    screen_y = FIELD(u16, &g_Game.members[0].pos.z.part.integer, offset);
    if (mode == 3) {
        value = COORD_INT(TASK(Actor)->pos.z);
        diff  = value - (s16)screen_y;
        diff  = ABS(diff);
        if (diff >= 0x81) {
            result = (s16)screen_y < value;
        } else {
            result = 3;
        }
    } else {
        alt    = COORD_INT(TASK(Actor)->pos.z);
        result = ((s16)screen_y < alt) * 2;
    }
    type = result & BYTE_MASK;
    switch (type) {
        case 0:
            Area_ClimbUp();
            break;
        case 1:
            Area_ClimbDown();
            break;
        case 2:
            Area_ClimbJumpOff();
            break;
    }
}
