#include "game_00.h"

/* Opcodes 0x60 to 0x66 of the actor script table: pick the facing animation
 * script for the task from its facing, lock the route, and select the script.
 * The bases index the script table records; their animation roles are not
 * proven. Named from the case bodies. */
/* Opcodes 0x60 to 0x66 of the actor script table: pick the facing animation
 * script for the task from its facing, lock the route, and select the script.
 * The bases index the script table records; their animation roles are not
 * proven. Named from the case bodies. */
typedef enum ActorScriptFaceOp {
    ACTOR_SCRIPT_FACE_SELECT_FACING  = 0x60, /* the script for the current facing */
    ACTOR_SCRIPT_FACE_SELECT_BASE_14 = 0x61, /* facing + bank base 0x14 */
    ACTOR_SCRIPT_FACE_SELECT_BASE_1C = 0x62, /* facing + bank base 0x1C */
    ACTOR_SCRIPT_FACE_SELECT_BASE_24 = 0x63, /* facing + bank base 0x24 */
    ACTOR_SCRIPT_FACE_SELECT_BASE_2C = 0x64, /* facing + bank base 0x2C */
    ACTOR_SCRIPT_FACE_AXIS_BASE_34   = 0x65, /* straighten to the axis facing, script base 0x34 + axis */
    ACTOR_SCRIPT_FACE_AXIS_BASE_10   = 0x66, /* straighten to the axis facing, script base 0x10 + axis */
} ActorScriptFaceOp;

MATCH u8 func_801ABA24(void* sub, s32 target, u8 value) {
    u8  action;
    u8  result;
    u32 mode;
    /* FAKE: work pointer pinned to a0, the retail home. */
    FAKE_REG(Actor*, work, "a0");

    action = ((u8*)target)[FIELD(u16, sub, 0xAu)];
    switch (action) {
        case ACTOR_SCRIPT_FACE_SELECT_BASE_14:
            result = (g_Task->direction_08 & 0x7) + 0x14;
            break;
        case ACTOR_SCRIPT_FACE_SELECT_BASE_1C:
            result = (g_Task->direction_08 & 0x7) + 0x1C;
            break;
        case ACTOR_SCRIPT_FACE_SELECT_BASE_24:
            result = (g_Task->direction_08 & 0x7) + 0x24;
            break;
        case ACTOR_SCRIPT_FACE_SELECT_BASE_2C:
            result = (g_Task->direction_08 & 0x7) + 0x2C;
            break;
        case ACTOR_SCRIPT_FACE_AXIS_BASE_34:
            work   = g_Task;
            mode   = work->direction_08;
            result = ((mode >> 1) & 0x3) | 0x34;
            /* 0x65 and 0x66 share the route update at set_route. */
            goto set_route;
        case ACTOR_SCRIPT_FACE_AXIS_BASE_10:
            work   = g_Task;
            mode   = work->direction_08;
            result = ((mode >> 1) & 0x3) | 0x10;
        set_route:
            mode &= 6;
            mode += 1;
            work->direction_08 = mode;
            break;
        case ACTOR_SCRIPT_FACE_SELECT_FACING:
        default:
            result = g_Task->direction_08 & 0x7;
            break;
    }
    FIELD(u8, sub, 0x0u) |= 0x40;
    g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    Actor_SelectScript(result);
    return g_Task->direction_08;
}
