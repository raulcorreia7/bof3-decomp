/* Stream in the party resources, rebuild the battlers, add Rei and Garr to the
 * party and restage the party palettes. One definition shared by the scenario
 * programs; every change here must verify every member. */
/* func_801FADAC (scena11), func_801FD018 (scena12) */
MATCH void Scene_JoinReiAndGarr(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_GARR, 0);
    Party_BuildBattlers(0);
    Party_JoinMember(CHAR_ID_REI);
    Party_JoinMember(CHAR_ID_GARR);
    func_801C1630();
}
