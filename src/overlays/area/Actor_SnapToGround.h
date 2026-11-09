/* Project the focus point and keep the result as the work height. One
 * definition shared by the world area overlays; every change here must verify
 * every member address. */
/* func_801F2D5C (area036), func_801F2DD4 (area146), func_801F2EE4 (area116), func_801F3014 (area059), func_801F3CDC
   (area100), func_801F3E58 (area112), func_801F3F48 (area143) */
MATCH void Actor_SnapToGround(void) {
    Actor* work;
    Actor* depth_target;
    s32    result;

    work                      = g_Task;
    result                    = Area_SampleHeight(work->pos.x.fixed, work->pos.y.fixed);
    depth_target              = g_Task;
    depth_target->pos.z.fixed = result << 16;
    depth_target->header.mode++;
}
