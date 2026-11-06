/* Starts the character script named by the work record's cue byte once
 * func_8014DAEC reports ready, then advances the work byte at +0x03. One
 * definition shared by the plchar character programs; each program includes
 * it where the function sits, and a change must keep every member matching.
 */
MATCH void Char_SelectScriptAndStep(void) {
    if (func_8014DAEC() & BYTE_MASK) {
        Actor_SelectScript(g_Task->direction_08);
        g_Task->unk_03++;
    }
}
