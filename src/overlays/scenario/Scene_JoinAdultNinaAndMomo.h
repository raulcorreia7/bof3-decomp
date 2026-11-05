/* Stream in the party resources, rebuild the battlers, add adult Nina and Momo
 * to the party and restage the party palettes. One definition shared by the
 * scenario programs; every change here must verify every member. */
/* func_801FCDE0 (scena12), func_801FCEB4 (scena12), func_801FAB74 (scena11), func_801FDD7C (scena09) */
#define SCENE_JOIN_ADULT_NINA_AND_MOMO()    \
    EMI_LoaderStreamFamily(7U, 8U, 5U, 0U); \
    Party_BuildBattlers(0);                 \
    Party_JoinMember(CHAR_ID_NINA_ADULT);   \
    Party_JoinMember(CHAR_ID_MOMO);         \
    func_801C1630()

MATCH void Scene_JoinAdultNinaAndMomo(void) {
    SCENE_JOIN_ADULT_NINA_AND_MOMO();
}
