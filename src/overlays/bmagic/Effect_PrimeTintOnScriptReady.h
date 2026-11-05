/* Once the script stream reports ready (func_8014DAEC), sets the work flag
 * 0x20, starts the tint at zero and steps the handler. Every change here must
 * verify every member.
 */
/* func_801EFF28 (magic001), func_801F0024 (magic056) */
MATCH void Effect_PrimeTintOnScriptReady(void) {
    if (func_8014DAEC() & 0xFF) {
        g_SpadWork->flags_00 |= 0x20;
        g_SpadWork->unk_5C = 1;
        g_SpadWork->unk_5D = 0;
        g_SpadWork->unk_5E = 0;
        g_SpadWork->unk_5F = 0;
        g_SpadWork->unk_02 += 1;
    }
}
