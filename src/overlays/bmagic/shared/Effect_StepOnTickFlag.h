/* Advances the effect step (work byte 0x02) while bit 0x80 of the other battler's effect ticker (work byte 0x0B of g_BattleEffectBattler) is set. */
/* func_801F03DC (magic092), func_801F00F0 (magic144) */
MATCH void Effect_StepOnTickFlag(void) {
    PartyMember* work;

    work = (PartyMember*)g_BattleEffectBattler;
    if ((work->param.unk_0B & 0x80) != 0) {
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}
