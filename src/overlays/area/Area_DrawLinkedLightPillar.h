/* Draws a light pillar at the position of the actor that the scratchpad link cell (0x44) points to. One definition
 * shared by the area overlays; every change here must verify every member. */
/* Area_DrawLinkedLightPillar (area036 0x801F2DA8, area059 0x801F3060) */
MATCH void Area_DrawLinkedLightPillar(void) {
    Actor* work;
    s32    pos[3];

    work   = SP_REF(Actor*, 0x44);
    pos[0] = work->pos.x.fixed;
    pos[1] = work->pos.y.fixed;
    pos[2] = work->pos.z.fixed;
    Area_DrawLightPillar(pos);
}
