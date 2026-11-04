/* Remove Momo from the party and restage the party palettes. One definition
 * shared by the scenario programs; every change here must verify every member. */
/* func_801FD530 (scena05), func_801FE364 (scena06), func_801FE30C (scena09), func_801FE614 (scena10), func_801FAE70 (scena11), func_801FD128 (scena12) */
MATCH void Scene_RemoveMomo(void) {
    func_801C1ABC(CHAR_ID_MOMO);
    func_801C1630();
}
