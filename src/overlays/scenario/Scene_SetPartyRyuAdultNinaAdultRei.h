/* Stream in the party resources, empty the party, join adult Ryu, adult Nina
 * and Rei and restage the party palettes. One definition shared by the
 * scenario programs; every change here must verify every member. */
/* func_801FC22C (scena14), func_801FE520 (scena15) */
MATCH void Scene_SetPartyRyuAdultNinaAdultRei(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_REI, 0);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_JoinMember(CHAR_ID_REI);
    func_801C1630();
}
