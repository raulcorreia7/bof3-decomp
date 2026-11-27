/* When the effect ticker runs down, advances the active battler's script step (Battle_SelectActiveBattlerScript), clears the battler's flag bit 0x40 and steps the handler. */
/* func_801EEF68 (magic017), func_801EEF38 (magic021) */
MATCH void Effect_ReleaseActiveBattlerOnTickerZero(void) {
    if (SELF(PartyMember)->param.unk_0B == 0) {
        Battle_SelectActiveBattlerScript(4, 0);
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        SELF(PartyMember)->header.mode += 1;
    }
}
