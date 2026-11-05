/* Stream in the party resources, empty the party and join young Ryu, young
 * Nina and Momo. One definition shared by the scenario programs; every change
 * here must verify every member. */
/* func_801FA12C (scena04), func_801FDB34 (scena07) */
MATCH void Scene_SetPartyRyuYoungNinaYoungMomo(void) {
    SCENE_SET_PARTY_NO_RESTAGE(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO);
}
