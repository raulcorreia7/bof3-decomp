/* Stream in the party resources, rebuild the battlers, add Peco to the party
 * and restage the party palettes. One definition shared by the scenario
 * programs; every change here must verify every member. */
/* func_801FDECC (scena09), func_801FAD68 (scena11), func_801FCFD4 (scena12) */
MATCH void Scene_JoinPeco(void) {
    EMI_LoaderStreamFamily(7U, 6U, 5U, 0U);
    Party_BuildBattlers(0);
    Party_JoinMember(CHAR_ID_PECO);
    func_801C1630();
}
