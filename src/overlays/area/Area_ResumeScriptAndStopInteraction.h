/* Reactivates the script, stops the current actor's pending area interaction
 * and advances its counter at 0x7E. One body shared by the members below;
 * every change must verify every member.
 */
/* func_801F30DC (area191), func_801F2E44 (area192) */
MATCH void Area_ResumeScriptAndStopInteraction(void) {
    Game_SetScriptActive();
    g_CurrentActor->flags_74 &= ~ACTOR_FLAG_INTERACTION_PENDING;
    g_CurrentActor->unk_7E += 1;
}
