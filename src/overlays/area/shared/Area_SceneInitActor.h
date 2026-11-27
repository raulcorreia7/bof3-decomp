/* Marks the work flags, looks up scene record 0x158, loads byte 0x29
 * with 5, clears the tint bytes and moves the handler to state 1.
 */
/* func_801F3124 (area104), func_801F3078 (area121) */
MATCH void Area_SceneInitActor(void) {
    SELF(Actor)->active_flags = 0x80;
    Area_SceneSelectRecord(0x158);
    SELF(Actor)->draw_layer = 5;
    SELF(Actor)->mirror     = 0;
    ACTOR_CLEAR_TINT();
    SELF(Actor)->header.mode = 1;
}
