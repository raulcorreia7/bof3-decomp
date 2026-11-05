/* Loads the work x coordinate with 300 and clears its timer, removes the
 * scan bars and steps the handler.
 */
/* func_801D15CC (sce15ef3), func_801D0DE8 (sce15ef2) */
MATCH void Scene_ClearScanBarsAndAdvance(void) {
    Actor* work;

    work         = g_Task;
    work->unk_2E = 300;
    work->unk_09 = 0;
    Scene_ClearScanBars();
    g_Task->mode = g_Task->mode + 1;
}
