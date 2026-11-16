/* Starts turning the task's facing one step toward the target, the short way round. Returns 0 when they are more
 * than two steps apart or already equal. */
/* func_801F5988 (area104), func_801F5ECC (area121). Every change must verify every member. */
MATCH u8 Area_StartTurn(s32 direction, s32 previous) {
    u8 current;
    u8 target;

    current = direction;
    target  = previous;
    if (abs(current - target) >= 3) {
        if (current < target) {
            current = direction + 8;
        } else {
            target = previous + 8;
        }
        if (abs(current - target) >= 3) {
            return 0;
        }
    }
    if (current != target) {
        if (target < current) {
            g_Task->vz           = -0x40;
            g_Task->direction_08 = g_Task->direction_08 - 1;
        } else {
            g_Task->vz           = 0x40;
            g_Task->direction_08 = g_Task->direction_08 + 1;
        }
        g_Task->direction_08 &= 7;
        g_Game.members[0].facing = g_Task->direction_08;
        g_Task->timer            = 8;
        Area_UpdateTurn();
        g_Task->header.mode = 2;
        return 1;
    }
    return 0;
}
