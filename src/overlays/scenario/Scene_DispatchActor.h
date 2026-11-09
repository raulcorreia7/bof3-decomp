/* Dispatches a scenario actor to its callback handler. One definition shared by scenario overlays;
 * every change here must verify every member. */
/* func_801FC46C (scena03), func_801F9D48 (scena04), func_801FCA58 (scena05),
 * func_801FCDD0 (scena06), func_801FD3BC (scena07), func_801FE018 (scena08), func_801FC5E4 (scena09),
 * func_801FD464 (scena10), func_801FA5B8 (scena11), func_801FC574 (scena12), func_801FB350 (scena13),
 * func_801FB37C (scena14), func_801FDD80 (scena15), func_801F887C (scena17), func_801F6CAC (scena18),
 * func_801F6D10 (scena19) */
MATCH void Scene_DispatchActor(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = g_SceneActorDispatch[index];
    handler(entity, g_SceneFlags);
}
