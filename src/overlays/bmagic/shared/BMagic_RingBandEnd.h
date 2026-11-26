/* Ring band mode 2: raises the phase by 1 and lowers the wave height by 3 per frame while the radius step falls by 2; at zero lowers the live ring count of the task and resets the effect. */
/* func_801EF124 (magic055), func_801EF124 (magic091) */
MATCH void BMagic_RingBandEnd(void) {
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
