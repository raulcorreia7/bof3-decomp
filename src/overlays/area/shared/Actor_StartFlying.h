/* Gives each flock member a velocity from its facing, backs it off along it so the flock enters from out of view (members 1 and 2 two cells to either side) and selects the script for that facing; Actor_Fly follows. */
MATCH void Actor_StartFlying(void) {
    Actor* scratch;
    u16    value;
    u16    y;

    Area_SceneSelectRecord(0x46);

    SELF(Actor)->unk_48       = 0;
    SELF(Actor)->active_flags = 0;
    SELF(Actor)->draw_layer   = 5;

    scratch              = SELF(Actor);
    scratch->vx          = (s16)g_FlockVelocity[scratch->direction].x;
    scratch->vy          = (s16)g_FlockVelocity[scratch->direction].y;
    scratch->pos.x.fixed = g_Game.members[0].pos.x.fixed;
    scratch->pos.y.fixed = g_Game.members[0].pos.y.fixed;

    if (scratch->unk_06 != 0) {
        COORD_INT(scratch->pos.x) -= (s32)(g_FlockVelocity[scratch->direction].x << 16) >> 29;
        value                     = COORD_INT(scratch->pos.y) - ((s32)(g_FlockVelocity[scratch->direction].y << 16) >> 29);
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

    scratch = SELF(Actor);
    COORD_INT(scratch->pos.x) -= (s32)(g_FlockVelocity[scratch->direction].x << 16) >> 25;
    y                         = COORD_INT(scratch->pos.y) - ((s32)(g_FlockVelocity[scratch->direction].y << 16) >> 25);
    scratch->param.unk_0B     = 0;
    COORD_INT(scratch->pos.y) = y;
    SELF(Actor)->header.mode++;

    Script_Select(g_FlockScript[SELF(Actor)->direction][0]);

    SELF(Actor)->mirror = g_FlockScript[SELF(Actor)->direction][1];
    Area_AddGridActor();
}
