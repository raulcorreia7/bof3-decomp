/* Initialises the area work bytes and loads scene 0x1D1. One definition shared
 * by the two world area overlays; every change here must verify every member. */
/* func_801F2F24 (area152), func_801F2FD0 (area151) */
MATCH void WorldMap_StartScene(void) {
    g_SpadWork->flags_24 = 0x80;
    Area_FindSceneRecord(0x1D1);
    ((u8*)g_SpadWork)[0x29] = 5;
    ((u8*)g_SpadWork)[0x2A] = 0;
    ((u8*)g_SpadWork)[0x5D] = 0;
    ((u8*)g_SpadWork)[0x5E] = 0;
    ((u8*)g_SpadWork)[0x5F] = 0;
    ((u8*)g_SpadWork)[0x01] = 1;
}
