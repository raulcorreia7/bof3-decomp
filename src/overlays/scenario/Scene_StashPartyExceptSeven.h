/* Copies the character id of every party member into D_80144908 and a local
 * list, then removes each listed member except 7 from the party and
 * runs func_801C1630. Scene_RebuildTrioParty reads D_80144908 afterwards.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* Scene_StashPartyExceptSeven (scena09), Scene_StashPartyExceptSeven (scena10) */
MATCH void Scene_StashPartyExceptSeven(void) {
    u8 ids[3];
    u8 slot;

    for (slot = 0; slot < g_PartySize; slot++) {
        ids[slot] = D_80144908[slot] = g_BattlePartyBattlers[slot].stats.character_id;
    }
    for (slot = 0; slot < 3; slot++) {
        if (ids[slot] != 7) {
            func_801C1ABC(ids[slot]);
        }
    }
    func_801C1630();
}
