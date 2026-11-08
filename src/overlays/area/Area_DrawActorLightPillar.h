/* Draw a light pillar at the current task's position. One definition shared by the area overlays
 * that place one.
 */
/* func_801F3D28 (area100), func_801F3EA4 (area112), func_801F2F30 (area116) */
MATCH void Area_DrawActorLightPillar(void) {
    s32    pos[3];
    Actor* work = g_Task;

    pos[0] = work->pos.x.fixed;
    pos[1] = work->pos.y.fixed;
    pos[2] = work->pos.z.fixed;
    Area_DrawLightPillar(pos);
}
