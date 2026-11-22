/* Passes the work bytes at +0x04 and +0x03 to the battle queue writer func_800AEEC8, sets the effect ticker and steps the handler. */
/* func_801EF8FC (magic038), func_801F02E4 (magic067) */
MATCH void Effect_QueueEntry(void) {
    func_800AEEC8(BMAGIC_WORK->unk_04, BMAGIC_WORK->unk_03);
    BMAGIC_WORK->param.unk_0B = 1;
    BMAGIC_WORK->header.step += 1;
}
