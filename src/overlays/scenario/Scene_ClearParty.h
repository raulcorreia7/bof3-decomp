/* Clear the effect bank's party order, battle order and party count, set the
 * menu flags' low three bits, then run the effect callback. One definition
 * shared by the scena00 and scena16 programs; each program includes this file
 * where the function sits.
 */
MATCH void Scene_ClearParty(void) {
    u8 flags;

    EMI_LoaderStreamFamily(CHAR_ID_WHELP, CHAR_ID_BLANK, CHAR_ID_BLANK, 0);
    flags                                 = EFFECT_BANK_80140000->menu_flags;
    EFFECT_BANK_80140000->field_order[0]  = 0xFFu;
    EFFECT_BANK_80140000->field_order[1]  = 0xFFu;
    EFFECT_BANK_80140000->field_order[2]  = 0xFFu;
    EFFECT_BANK_80140000->battle_order[0] = 0xFFu;
    EFFECT_BANK_80140000->battle_order[1] = 0xFFu;
    EFFECT_BANK_80140000->battle_order[2] = 0xFFu;
    g_Game.party_size                     = 0u;
    /* FAKE: statement boundary keeps a0=10 in the jal delay slot. */
    ORDER_LOCK(EFFECT_BANK_80140000->menu_flags = (u8)(flags | 7u));
    Party_JoinMember(CHAR_ID_WHELP);
}
