/* Moves the actor by the projected velocity when the tile is classified, then
 * runs the area projection and update. One definition shared by the world area
 * overlays; every change here must verify every member. */
/* func_801F4528 (area016), func_801F4528 (area045), func_801F4528 (area115), func_801F453C (area121), func_801F4558
   (area087), func_801F4560 (area065), func_801F5088 (area088) */
MATCH void Actor_MoveByVelocity(void) {
    Actor* work;
    Actor* scratch;

    scratch = g_Task;
    if (scratch->unk_0B != 0) {
        if ((scratch->header.flags & 0x80) != 0) {
            Actor_Clear();
            return;
        }
    } else if ((scratch->header.flags & 0x80) == 0) {
        scratch->unk_0B = 1;
    }

    work = g_Task;
    work->pos.x.fixed += work->vx;
    work->pos.y.fixed += work->vy;
    func_8014D978();
    func_8014D290();
}
