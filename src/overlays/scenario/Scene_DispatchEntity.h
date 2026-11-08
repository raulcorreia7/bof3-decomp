/* Dispatches a scene entity by its callback index. One definition shared by scenario overlays;
 * every change here must verify every member. */
/* Scene_DispatchEntity (sce15ef0 0x801D0C0C), Scene_DispatchEntity (sce15ef1 0x801D0C0C), Scene_DispatchEntity (sce15ef3 0x801D0C0C), Scene_DispatchEntity (scena03 0x801F6E78), Scene_DispatchEntity (scena04 0x801F6D08), Scene_DispatchEntity (scena05 0x801F7400), Scene_DispatchEntity (scena07 0x801F6DD4), Scene_DispatchEntity (scena08 0x801F6F50), Scene_DispatchEntity (scena09 0x801F7364), Scene_DispatchEntity (scena10 0x801F6F70), Scene_DispatchEntity (scena12 0x801F717C), Scene_DispatchEntity (scena13 0x801F6EAC), Scene_DispatchEntity (scena15 0x801F6F40) */
MATCH void Scene_DispatchEntity(void) {
    u8* entity;

    g_SceneEntityDispatch[entity[1]]();
}
