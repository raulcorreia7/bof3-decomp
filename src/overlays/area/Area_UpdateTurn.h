/* One definition shared by the area overlays; every change here must verify every member. */
MATCH void Area_UpdateTurn(void) {
    Actor* actor;
    s32    heading;

    actor   = g_Task;
    heading = actor->unk_6C;
    actor->timer--;
    actor->unk_6C = (heading + actor->vz) & 0xFFF;
    if (g_Task->timer == 0) {
        g_Task->header.mode = 1;
        Area_EndTurn();
    } else {
        AREA_TURN_SYNC();
    }
}
