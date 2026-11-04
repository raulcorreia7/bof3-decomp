/* Stream in the party resources, empty the party and join young Ryu, Teepo and
 * Rei. One definition shared by the scenario programs; every change here must
 * verify every member. */
/* func_801F96D4 (scena17), func_801F6D04 (scena18), func_801F6D68 (scena19) */
MATCH void Scene_SetPartyRyuTeepoRei(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_YOUNG, CHAR_ID_TEEPO, CHAR_ID_REI, 0);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_YOUNG);
    Party_JoinMember(CHAR_ID_TEEPO);
    Party_JoinMember(CHAR_ID_REI);
}
