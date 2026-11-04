/* Copies the character id of every party member into D_80144908 and a local
 * list, then removes each listed member except adult Ryu from the party and
 * runs func_801C1630. Scene_RebuildRyuGarrParty reads D_80144908 afterwards.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801FE234 (scena09), func_801FE6F4 (scena10) */
MATCH void Scene_StashPartyExceptRyuAdult(void) {
    u8 ids[3];
    u8 slot;

    for (slot = 0; slot < g_PartySize; slot++) {
        ids[slot] = D_80144908[slot] = g_BattlePartyBattlers[slot].stats.character_id;
    }
    for (slot = 0; slot < 3; slot++) {
        if (ids[slot] != CHAR_ID_RYU_ADULT) {
            func_801C1ABC(ids[slot]);
        }
    }
    func_801C1630();
}
