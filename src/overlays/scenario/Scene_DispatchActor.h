/* Dispatches a scenario actor to its callback handler. One definition shared by scenario overlays;
 * every change here must verify every member. */
/* Scene_DispatchActor (scena00 0x801FC7D0), Scene_DispatchActor (scena03 0x801FC46C), Scene_DispatchActor (scena04 0x801F9D48), Scene_DispatchActor (scena05 0x801FCA58), Scene_DispatchActor (scena06 0x801FCDD0), Scene_DispatchActor (scena07 0x801FD3BC), Scene_DispatchActor (scena08 0x801FE018), Scene_DispatchActor (scena09 0x801FC5E4), Scene_DispatchActor (scena10 0x801FD464), Scene_DispatchActor (scena11 0x801FA5B8), Scene_DispatchActor (scena12 0x801FC574), Scene_DispatchActor (scena13 0x801FB350), Scene_DispatchActor (scena14 0x801FB37C), Scene_DispatchActor (scena15 0x801FDD80), Scene_DispatchActor (scena17 0x801F887C), Scene_DispatchActor (scena18 0x801F6CAC), Scene_DispatchActor (scena19 0x801F6D10) */
MATCH void Scene_DispatchActor(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = g_SceneActorDispatch[index];
    handler(entity, g_SceneFlags);
}
