/* Stream in the party resources, rebuild the battlers, add Momo and Peco to
 * the party and restage the party palettes. One definition shared by the
 * scenario programs; every change here must verify every member. */
/* func_801FCF88 (scena12), func_801FAD1C (scena11), func_801FDE80 (scena09) */
#define SCENE_JOIN_MOMO_AND_PECO()                                             \
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_PECO, CHAR_ID_MOMO, 0U); \
    Party_BuildBattlers(0);                                                    \
    Party_JoinMember(CHAR_ID_MOMO);                                            \
    Party_JoinMember(CHAR_ID_PECO);                                            \
    Party_StagePalettes()

MATCH void Scene_JoinMomoAndPeco(void) {
    SCENE_JOIN_MOMO_AND_PECO();
}
