/* Initialises the area work bytes and loads scene 0x1D1. */
/* func_801F2F24 (area152), func_801F2FD0 (area151) */

MATCH void WorldMap_StartScene(void) {
    TASK(Actor)->active_flags = 0x80;
    Area_SceneSelectRecord(0x1D1);
    TASK(Actor)->draw_layer = 5;
    TASK(Actor)->mirror     = 0;
    ACTOR_CLEAR_TINT();
    TASK(Actor)->header.mode = 1;
}
