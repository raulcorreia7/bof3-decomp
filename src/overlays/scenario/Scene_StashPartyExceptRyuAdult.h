/* Copies the character id of every party member into D_80144908 and a local list, then removes each listed member except adult Ryu from the party and runs Party_LoadPalettes. Scene_RebuildRyuGarrParty reads D_80144908 afterwards. */
/* func_801FE234 (scena09), func_801FE6F4 (scena10) */
MATCH void Scene_StashPartyExceptRyuAdult(void) {
    u8 ids[3];
    u8 slot;

    for (slot = 0; slot < g_PartySize; slot++) {
        ids[slot] = D_80144908[slot] = g_Game.members[slot].chr.character_id;
    }
    for (slot = 0; slot < 3; slot++) {
        if (ids[slot] != CHAR_ID_RYU_ADULT) {
            Party_RemoveMember(ids[slot]);
        }
    }
    Party_LoadPalettes();
}
