/* Stream in the party resources, empty the party, join adult Ryu, Garr and
 * adult Nina and restage the party palettes. One definition shared by the
 * scenario programs; every change here must verify every member. */
/* func_801FE7AC (scena08), func_801FC074 (scena14) */
MATCH void Scene_SetPartyRyuAdultGarrNinaAdult(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_NINA_ADULT, 0);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_GARR);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    func_801C1630();
}
