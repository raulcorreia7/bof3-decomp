/* Marks the work flags, looks up scene record 0x158, loads byte 0x29
 * with 5, clears the tint bytes and moves the handler to state 1.
 */
/* func_801F3124 (area104), func_801F3078 (area121) */
MATCH void Area_InitSceneActor(void) {
    g_Task->active_flags = 0x80;
    Area_SelectSceneRecord(0x158);
    g_Task->draw_layer = 5;
    g_Task->unk_2A     = 0;
    ACTOR_CLEAR_TINT();
    g_Task->header.mode = 1;
}
