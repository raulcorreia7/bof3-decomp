MATCH void Area_UpdateTurn(void) {
    Actor* actor;
    s32    heading;

    actor   = TASK(Actor);
    heading = actor->angle_z;
    actor->timer--;
    actor->angle_z = (heading + actor->vz) & 0xFFF;
    if (TASK(Actor)->timer == 0) {
        TASK(Actor)->header.mode = 1;
        Area_EndTurn();
    } else {
        AREA_TURN_SYNC();
    }
}
