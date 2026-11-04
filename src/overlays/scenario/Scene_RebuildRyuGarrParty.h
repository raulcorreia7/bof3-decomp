/* Rebuilds the three-member party around the fixed members Ryu (adult) and Garr: clears the
 * three D_80144908 party slots, keeps the last id that is neither of them (adult
 * Nina when none is), streams the EMI family for the trio and joins it.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801FDF54 (scena09), func_801FE4F0 (scena10) */
MATCH void Scene_RebuildRyuGarrParty(void) {
    s32 slot;
    u8  character;
    u8  id;

    slot      = 0;
    character = CHAR_ID_NINA_ADULT;
    for (; (u32)(slot & BYTE_MASK) < 3U; slot++) {
        id = D_80144908[slot & BYTE_MASK];
        if (id != CHAR_ID_RYU_ADULT && id != CHAR_ID_GARR) {
            character = id;
        }
        D_80144908[slot & BYTE_MASK] = 0;
    }
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, character & BYTE_MASK, 0);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_GARR);
    Party_JoinMember(character & BYTE_MASK);
    func_801C1630();
}
