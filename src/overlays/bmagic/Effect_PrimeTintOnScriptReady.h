/* Once the script stream reports ready (Actor_StepAnimOnce), sets the work flag
 * 0x20, starts the tint at zero and steps the handler. Every change here must
 * verify every member.
 */
/* func_801EFF28 (magic001), func_801F0024 (magic056) */
MATCH void Effect_PrimeTintOnScriptReady(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 1;
        g_Task->unk_5D = 0;
        g_Task->unk_5E = 0;
        g_Task->unk_5F = 0;
        g_Task->header.step += 1;
    }
}
