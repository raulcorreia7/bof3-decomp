/* Draw a light pillar at the current task's position. */
/* Area_DrawActorLightPillar (area100 0x801F3D28, area112 0x801F3EA4, area116 0x801F2F30, area143 0x801F3F94, area146 0x801F2E20). */
MATCH void Area_DrawActorLightPillar(void) {
    s32    pos[3];
    Actor* work = g_Task;

    pos[0] = work->pos.x.fixed;
    pos[1] = work->pos.y.fixed;
    pos[2] = work->pos.z.fixed;
    Area_DrawLightPillar(pos);
}
