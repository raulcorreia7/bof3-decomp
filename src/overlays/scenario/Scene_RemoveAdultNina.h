/* Remove adult Nina from the party and restage the party palettes. One
 * definition shared by the scenario programs; every change here must verify
 * every member. */
/* func_801FE20C (scena09), func_801FAE98 (scena11), func_801FD150 (scena12) */
MATCH void Scene_RemoveAdultNina(void) {
    func_801C1ABC(CHAR_ID_NINA_ADULT);
    func_801C1630();
}
