/* Clear the party state's party order, battle order and party count, set the menu flags' low three bits, then run the effect callback. */
MATCH void Scene_ClearParty(void) {
    u8 flags;

    EMI_PartyLoadArchives(CHAR_ID_WHELP, CHAR_ID_BLANK, CHAR_ID_BLANK, 0);
    flags                            = PARTY_STATE_PTR->menu_flags;
    PARTY_STATE_PTR->field_order[0]  = 0xFFu;
    PARTY_STATE_PTR->field_order[1]  = 0xFFu;
    PARTY_STATE_PTR->field_order[2]  = 0xFFu;
    PARTY_STATE_PTR->battle_order[0] = 0xFFu;
    PARTY_STATE_PTR->battle_order[1] = 0xFFu;
    PARTY_STATE_PTR->battle_order[2] = 0xFFu;
    g_Game.party_size                = 0u;
    /* FAKE: statement boundary keeps a0=10 in the jal delay slot. */
    do {
        PARTY_STATE_PTR->menu_flags = (u8)(flags | 7u);
    } while (0);
    Party_MemberJoin(CHAR_ID_WHELP);
}
