/* Remove Rei from the party and restage the party palettes. One definition
 * shared by the scenario programs; every change here must verify every member. */
/* func_801FE244 (scena01), func_801FE198 (scena02), func_801FE12C (scena09), func_801FADF8 (scena11), func_801FD0B0 (scena12) */
MATCH void Scene_RemoveRei(void) {
    func_801C1ABC(CHAR_ID_REI);
    func_801C1630();
}
