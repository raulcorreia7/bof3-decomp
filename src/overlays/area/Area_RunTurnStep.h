/* One definition shared by the area overlays; every change here must verify every member. */
MATCH void Area_RunTurnStep(void) {
    Actor* actor;
    s32    heading;

    actor   = g_SpadWork;
    heading = actor->unk_6C;
    actor->unk_09--;
    actor->unk_6C = (heading + actor->vz) & 0xFFF;
    if (g_SpadWork->unk_09 == 0) {
        g_SpadWork->unk_01 = 1;
        Area_FinishTurnStep();
    } else {
        AREA_TURN_SYNC();
    }
}
