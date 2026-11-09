/* When the effect ticker runs down, marks the selected battlers as damaged
 * (func_800A9820 with g_Battle.target_selector) and steps the handler. Every
 * change here must verify every member.
 */
/* func_801EF05C (magic054), func_801EEE38 (magic103) */
MATCH void Effect_Hit(void) {
    if (g_Task->param.unk_0B == 0) {
        func_800A9820(g_Battle.target_selector);
        g_Task->header.mode += 1;
    }
}
