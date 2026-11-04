/* Rebuilds the three-member party around the fixed members 7 and 2: clears the
 * three D_80144908 party slots, keeps the last id that is neither 7 nor 2 (8
 * when none is), streams the EMI family for the trio and joins it.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* Scene_RebuildTrioParty (scena09), Scene_RebuildTrioParty (scena10) */
MATCH void Scene_RebuildTrioParty(void) {
    s32 slot;
    u8  character;
    u8  id;

    slot      = 0;
    character = 8;
    for (; (u32)(slot & BYTE_MASK) < 3U; slot++) {
        id = D_80144908[slot & BYTE_MASK];
        if (id != 7 && id != 2) {
            character = id;
        }
        D_80144908[slot & BYTE_MASK] = 0;
    }
    EMI_LoaderStreamFamily(7, 2, character & BYTE_MASK, 0);
    g_PartySize = 0;
    Party_JoinMember(7);
    Party_JoinMember(2);
    Party_JoinMember(character & BYTE_MASK);
    func_801C1630();
}
