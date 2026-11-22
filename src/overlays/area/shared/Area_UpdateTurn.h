MATCH void Area_UpdateTurn(void) {
    Actor* actor;
    s32    heading;

    actor   = TASK(Actor);
    heading = actor->unk_6C;
    actor->timer--;
    actor->unk_6C = (heading + actor->vz) & 0xFFF;
    if (TASK(Actor)->timer == 0) {
        TASK(Actor)->header.mode = 1;
        Area_EndTurn();
    } else {
        AREA_TURN_SYNC();
    }
}
