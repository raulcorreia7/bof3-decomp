/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */

MATCH void func_801F3060(void) {
    TASK(Actor)->active_flags = 0x80;
    Area_SceneSelectRecord(AREA_SCENE_RECORD);
    TASK(Actor)->draw_layer = 5;
    TASK(Actor)->mirror     = 0;
    ACTOR_CLEAR_TINT();
    TASK(Actor)->header.mode = 1;
}
