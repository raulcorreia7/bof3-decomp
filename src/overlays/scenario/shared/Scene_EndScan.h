/* Loads the work x coordinate with 300 and clears its timer, removes the
 * scan bars and steps the handler.
 */
/* func_801D15CC (sce15ef3), func_801D0DE8 (sce15ef2) */
MATCH void Scene_EndScan(void) {
    Actor* work;

    work           = SELF(Actor);
    work->screen_x = 300;
    work->timer    = 0;
    Scene_ClearScanBars();
    SELF(Actor)->header.mode = SELF(Actor)->header.mode + 1;
}
