/* Lowers the counter and raises the ticker and timer; when the timer reaches 0x10, sets the battler's ticker to 0xFF and runs the effect step. */
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
