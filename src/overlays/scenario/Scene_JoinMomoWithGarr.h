/* Adds Momo to the party with Garr. Every change must verify every member. */
MATCH void Scene_JoinMomoWithGarr(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_LoadPalettes();
}
