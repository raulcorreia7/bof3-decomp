/* Projects the ring points around ring->center onto the screen. One definition shared by the area overlays;
   every change here must verify every member. */
/* func_801F30B0 (area080) */
MATCH void Area_ProjectRing(AreaRing* ring) {
    s32 point[3];
    u8  camera[32];
    s32 angle;
    u8  i;

    Area_SetCameraMatrix(camera);
    Area_ProjectPoint(ring->base, &ring->screen_base);
    Area_ProjectPoint(ring->center, &ring->screen_center);

    for (i = 0, angle = 0; i < AREA_RING_POINTS; i++) {
        point[0] = ring->center[0] + ((ring->radius * rcos((u16)angle)) >> 4);
        point[1] = ring->center[1] + ((ring->radius * rsin((u16)angle)) >> 4);
        point[2] = ring->center[2];
        Area_ProjectPoint(point, &ring->screen[i]);
        angle += AREA_RING_ANGLE_STEP;
    }
}
