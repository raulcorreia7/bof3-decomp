/* Stream in the party resources, empty the party, join adult Ryu, adult Nina
 * and Rei and restage the party palettes. One definition shared by the
 * scenario programs; every change here must verify every member. */
/* func_801FC22C (scena14), func_801FE520 (scena15) */
MATCH void Scene_SetPartyRyuAdultNinaAdultRei(void) {
    SCENE_SET_PARTY(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_REI);
}
