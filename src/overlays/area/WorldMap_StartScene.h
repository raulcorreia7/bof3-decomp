/* Initialises the area work bytes and loads scene 0x1D1. One definition shared
 * by the two world area overlays; every change here must verify every member. */
/* func_801F2F24 (area152), func_801F2FD0 (area151) */
MATCH void WorldMap_StartScene(void) {
    g_Task->active_flags = 0x80;
    Area_FindSceneRecord(0x1D1);
    TASK_BYTES[0x29]    = 5;
    TASK_BYTES[0x2A]    = 0;
    TASK_BYTES[0x5D]    = 0;
    TASK_BYTES[0x5E]    = 0;
    TASK_BYTES[0x5F]    = 0;
    g_Task->header.mode = 1;
}
