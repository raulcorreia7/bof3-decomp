/* One definition shared by the area overlays; every change here must verify every member. */
/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */
MATCH void func_801F3060(void) {
    g_Task->active_flags = 0x80;
    Area_FindSceneRecord(AREA_SCENE_RECORD);
    TASK_BYTES[0x29] = 5;
    TASK_BYTES[0x2A] = 0;
    TASK_BYTES[0x5D] = 0;
    TASK_BYTES[0x5E] = 0;
    TASK_BYTES[0x5F] = 0;
    TASK_BYTES[1]    = 1;
}
