/* Raises the effect ticker, drops the effect counter by three and counts the wait down by two; at zero it releases the battler's ticker and clears the effect. */
/* func_801EF124 (magic055), func_801EF124 (magic091) */
MATCH void func_801EF124(void) {
    u8 count;

    TASK(PartyMember)->param.unk_0B += 1;
    TASK(PartyMember)->timer -= 3;
    count                     = TASK(PartyMember)->unk_09 - 2;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}
