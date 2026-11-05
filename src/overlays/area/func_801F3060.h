/* One definition shared by the area overlays; every change here must verify every member. */
/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */
MATCH void func_801F3060(void) {
    g_SpadWork->flags_24 = 0x80;
    Area_FindSceneRecord(AREA_SCENE_RECORD);
    g_SpadWork->unk_29 = 5;
    g_SpadWork->unk_2A = 0;
    g_SpadWork->tint.bytes.unk_5D = 0;
    g_SpadWork->tint.bytes.unk_5E = 0;
    g_SpadWork->tint.bytes.unk_5F = 0;
    g_SpadWork->unk_01 = 1;
}
