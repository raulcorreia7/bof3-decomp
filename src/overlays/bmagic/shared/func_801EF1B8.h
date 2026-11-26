/* Ring band mode that no mode reaches: lowers the radius step by 1 and raises the phase by 2 and the wave height by 1 per frame; at wave height 0x10 sets the live ring count of the task to 0xFF and resets the effect. */
/* func_801EF1B8 (magic055), func_801EF1B8 (magic091) */
MATCH void func_801EF1B8(void) {
    u8 timer;

    TASK(PartyMember)->unk_09 -= 1;
    TASK(PartyMember)->param.unk_0B += 2;
    timer                    = TASK(PartyMember)->timer + 1;
    TASK(PartyMember)->timer = timer;
    if ((timer & BYTE_MASK) == 0x10) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        Effect_Reset();
    }
}
