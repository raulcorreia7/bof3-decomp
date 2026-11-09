/* Reactivates the script, stops the current actor's pending area interaction and advances its counter at 0x7E. */
/* func_801F30DC (area191), func_801F2E44 (area192) */
MATCH void Area_CloseTalk(void) {
    Game_SetScriptActive();
    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    g_CurrentActor->unk_7E += 1;
}
