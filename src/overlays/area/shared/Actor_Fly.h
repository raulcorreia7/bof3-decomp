/* Flies the flock member across the map by its velocity, then runs the area projection and update; frees it once it has been on screen and leaves. */
/* func_801F4528 (area016), func_801F4528 (area045), func_801F4528 (area115), func_801F453C (area121), func_801F4558
   (area087), func_801F4560 (area065), func_801F5088 (area088) */
MATCH void Actor_Fly(void) {
    Actor* work;
    Actor* scratch;

    scratch = TASK(Actor);
    if (scratch->param.unk_0B != 0) {
        if ((scratch->header.flags & 0x80) != 0) {
            Actor_Clear();
            return;
        }
    } else if ((scratch->header.flags & 0x80) == 0) {
        scratch->param.unk_0B = 1;
    }

    work = TASK(Actor);
    work->pos.x.fixed += work->vx;
    work->pos.y.fixed += work->vy;
    Script_AnimStepLoop();
    Area_AddGridActor();
}
