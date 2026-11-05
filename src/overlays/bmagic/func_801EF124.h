/* Raises the effect ticker, drops the effect counter by three and counts the
 * wait down by two; at zero it releases the battler's ticker and clears the
 * effect. Every change here must verify every member.
 */
/* func_801EF124 (magic055), func_801EF124 (magic091) */
MATCH void func_801EF124(void) {
    u8 temp_v0;

    g_Task->unk_0B += 1;
    g_Task->timer -= 3;
    temp_v0        = g_Task->unk_09 - 2;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        D_801EB4E0->unk_0B -= 1;
        func_801E5988();
    }
}
