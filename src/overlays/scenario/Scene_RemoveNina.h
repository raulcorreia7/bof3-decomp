/* Remove Nina from the party and restage the party palettes. One definition
 * shared by the scenario programs; every change here must verify every member. */
/* func_801FCEFC (scena03), func_801FD508 (scena05) */
MATCH void Scene_RemoveNina(void) {
    func_801C1ABC(CHAR_ID_NINA_YOUNG);
    func_801C1630();
}
