/* Passes the work bytes at +0x04 and +0x03 to the battle queue writer
 * func_800AEEC8, sets the effect ticker and steps the handler. Every change
 * here must verify every member.
 */
/* func_801EF8FC (magic038), func_801F02E4 (magic067) */
MATCH void Effect_RequestQueueEntryAndArmTicker(void) {
    func_800AEEC8(g_Task->unk_04, g_Task->unk_03);
    g_Task->word_08.byte.unk_0B = 1;
    g_Task->step += 1;
}
