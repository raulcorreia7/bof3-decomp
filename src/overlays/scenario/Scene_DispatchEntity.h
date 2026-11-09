/* Dispatches a scene entity by its callback index. One definition shared by scenario overlays;
 * every change here must verify every member. */
/* func_801D0C0C (sce15ef0), func_801D0C0C (sce15ef1), func_801D0C0C (sce15ef3), func_801F6E78 (scena03),
 * func_801F6D08 (scena04), func_801F7400 (scena05), func_801F6DD4 (scena07), func_801F6F50 (scena08),
 * func_801F7364 (scena09), func_801F6F70 (scena10), func_801F717C (scena12), func_801F6EAC (scena13),
 * func_801F6F40 (scena15) */
/* The retail function starts 8 bytes earlier, with `lui v0,0x1F80; lw v0,0x44(v0)` (g_Task) ahead of the
 * prologue; each image's split leaves those two words in the bin row before this unit and nothing calls this
 * address, so `entity` is the v0 that load sets. A `(u8* entity)` parameter reads a0 and fails. With the c
 * row and the symbol moved back 8 bytes, `g_SceneEntityDispatch[TASK_BYTES[1]]();` matches all 13 images. */
MATCH void Scene_DispatchEntity(void) {
    u8* entity;

    g_SceneEntityDispatch[entity[1]]();
}
