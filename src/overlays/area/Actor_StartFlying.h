/* Gives each flock member a velocity from its facing, backs it off along it so the flock enters from out of view (members 1 and 2 two cells to either side) and selects the script for that facing; Actor_Fly follows. */
MATCH void Actor_StartFlying(void) {
    Actor* scratch;
    u16    value;
    u16    y;

    Area_SelectSceneRecord(0x46);

    g_Task->unk_48       = 0;
    g_Task->active_flags = 0;
    g_Task->draw_layer   = 5;

    scratch              = g_Task;
    scratch->vx          = (s16)g_FlockVelocity[scratch->direction_08].x;
    scratch->vy          = (s16)g_FlockVelocity[scratch->direction_08].y;
    scratch->pos.x.fixed = g_Game.members[0].pos.x.fixed;
    scratch->pos.y.fixed = g_Game.members[0].pos.y.fixed;

    if (scratch->unk_06 != 0) {
        COORD_INT(scratch->pos.x) -= (s32)(g_FlockVelocity[scratch->direction_08].x << 16) >> 29;
        value                     = COORD_INT(scratch->pos.y) - ((s32)(g_FlockVelocity[scratch->direction_08].y << 16) >> 29);
        COORD_INT(scratch->pos.y) = value;
        if (scratch->unk_06 == 1) {
            if (scratch->vx == 0) {
                COORD_INT(scratch->pos.x) += 2;
            } else {
                COORD_INT(scratch->pos.y) = value + 2;
            }
        } else {
            if (scratch->vx == 0) {
                COORD_INT(scratch->pos.x) -= 2;
            } else {
                COORD_INT(scratch->pos.y) = value - 2;
            }
        }
    }

    scratch = g_Task;
    COORD_INT(scratch->pos.x) -= (s32)(g_FlockVelocity[scratch->direction_08].x << 16) >> 25;
    y                         = COORD_INT(scratch->pos.y) - ((s32)(g_FlockVelocity[scratch->direction_08].y << 16) >> 25);
    scratch->param.unk_0B     = 0;
    COORD_INT(scratch->pos.y) = y;
    g_Task->header.mode++;

    Actor_SelectScript(g_FlockScript[g_Task->direction_08][0]);

    g_Task->unk_2A = g_FlockScript[g_Task->direction_08][1];
    func_8014D290();
}
