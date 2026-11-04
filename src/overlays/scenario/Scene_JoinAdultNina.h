/* Stream in the party resources, rebuild the battlers, add adult Nina to the
 * party and restage the party palettes. One definition shared by the scenario
 * programs; every change here must verify every member. */
/* func_801FDE0C (scena09), func_801FABC0 (scena11), func_801FCE2C (scena12) */
MATCH void Scene_JoinAdultNina(void) {
    EMI_LoaderStreamFamily(7U, 8U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    func_801C1630();
}
