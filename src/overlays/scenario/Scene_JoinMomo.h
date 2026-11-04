/* Stream in the party resources, rebuild the battlers, add Momo to the party and
 * restage the party palettes. One definition shared by the scenario programs;
 * every change here must verify every member. */
/* func_801FDDC8 (scena09), func_801FAC04 (scena11), func_801FACD8 (scena11), func_801FCE70 (scena12), func_801FCF44 (scena12) */
#define SCENE_JOIN_MOMO()                   \
    EMI_LoaderStreamFamily(7U, 8U, 5U, 0U); \
    Party_BuildBattlers(0);                 \
    Party_JoinMember(CHAR_ID_MOMO);         \
    func_801C1630()

MATCH void Scene_JoinMomo(void) {
    SCENE_JOIN_MOMO();
}
