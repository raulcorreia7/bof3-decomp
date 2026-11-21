/* Updates the area camera height to the ground under the party position g_Game.members[0].pos.x.fixed/g_Game.members[0].pos.y.fixed: the sampled height is stored, or 0x20 below it when the camera already sits at that exact height, and the camera refresh counter advances by 2. */
/* func_801F3618 (area095/13), func_801F35A8 (area096/13) */
MATCH void Area_UpdateCameraHeight(void) {
    s32 height;

    height = Area_SampleHeight(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed);
    if (g_AreaCameraHeight == height) {
        height -= 0x20;
    }
    g_AreaCameraHeight = height;
    FAKE_BARRIER(); /* FAKE: keeps the camera store above the refresh-count load */
    g_AreaCameraRefreshCount += 2;
}
