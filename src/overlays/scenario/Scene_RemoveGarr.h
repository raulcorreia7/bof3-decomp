/* Remove Garr from the party and restage the party palettes. One definition
 * shared by the scenario programs; every change here must verify every member. */
/* func_801FE2E4 (scena06), func_801FE184 (scena09), func_801FAE20 (scena11), func_801FD0D8 (scena12) */
MATCH void Scene_RemoveGarr(void) {
    func_801C1ABC(CHAR_ID_GARR);
    func_801C1630();
}
