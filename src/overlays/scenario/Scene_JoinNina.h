/* Stream in the party resources and rebuild the battlers, then add Nina to the
 * party. One definition shared by the scenario programs; every change here must
 * verify every member. */
/* func_801FD460 (scena05), func_801FD49C (scena05), func_801FE15C (scena06), func_801FE1D4 (scena06) */
#define SCENE_JOIN_NINA()                   \
    EMI_LoaderStreamFamily(0U, 1U, 2U, 0U); \
    Party_BuildBattlers(0);                 \
    Party_JoinMember(CHAR_ID_NINA_YOUNG)

MATCH void Scene_JoinNina(void) {
    SCENE_JOIN_NINA();
}
