/* Runs the scene entity's handler for its current mode. */
/* func_801D0C04 (sce15ef0), func_801D0C04 (sce15ef1), func_801D0C04 (sce15ef3), func_801F6E70 (scena03),
 * func_801F6D00 (scena04), func_801F73F8 (scena05), func_801F6DCC (scena07), func_801F6F48 (scena08),
 * func_801F735C (scena09), func_801F6F68 (scena10), func_801F7174 (scena12), func_801F6EA4 (scena13),
 * func_801F6F38 (scena15) */
MATCH void Scene_DispatchEntity(void) {
    g_SceneEntityDispatch[g_Task->header.mode]();
}
