/* Raises the work counter at byte 0x09 and the timer at byte 0x0A each frame and, when the counter reaches 0x19, sets the high bit of the active battler's effect ticker byte and advances the effect state. */
/* func_801EF6A4 (magic144), func_801EF990 (magic092) */
MATCH void Effect_CountUpAndMarkBattler(void) {
    BMAGIC_WORK->unk_09 += 1;
    BMAGIC_WORK->timer += 1;
    if (BMAGIC_WORK->unk_09 == 0x19) {
        BATTLE_ACTIVE_WORK->param.unk_0B |= 0x80;
        BMAGIC_WORK->header.step += 1;
    }
}
