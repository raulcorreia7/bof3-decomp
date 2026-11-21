/* Projects the ring points around ring->center onto the screen. */
/* func_801F30B0 (area080) */
MATCH void Area_ProjectRing(AreaRing* ring) {
    s32 point[3];
    u8  camera[32];
    s32 angle;
    u8  i;

    Camera_SetMatrix(camera);
    Camera_ProjectPoint(&ring->base.vx, &ring->screen_base);
    Camera_ProjectPoint(&ring->center.vx, &ring->screen_center);

    for (i = 0, angle = 0; i < AREA_RING_POINTS; i++) {
        point[0] = ring->center.vx + ((ring->radius * rcos((u16)angle)) >> 4);
        point[1] = ring->center.vy + ((ring->radius * rsin((u16)angle)) >> 4);
        point[2] = ring->center.vz;
        Camera_ProjectPoint(point, &ring->screen[i]);
        angle += AREA_RING_ANGLE_STEP;
    }
}
