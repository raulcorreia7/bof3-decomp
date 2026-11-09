/* Stream in the party resources and rebuild the battlers, then add Nina to the party. */
/* func_801FD460 (scena05), func_801FD49C (scena05), func_801FE15C (scena06), func_801FE1D4 (scena06) */
#define SCENE_JOIN_NINA()                                                           \
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_GARR, 0U); \
    Party_BuildBattlers(PARTY_ORDER_FIELD);                                         \
    Party_JoinMember(CHAR_ID_NINA_YOUNG)

MATCH void Scene_JoinNina(void) {
    SCENE_JOIN_NINA();
}
