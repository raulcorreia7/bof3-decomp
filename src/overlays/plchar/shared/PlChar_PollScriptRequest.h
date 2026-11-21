/* Answers the character's script request once ready. */
MATCH void PlChar_PollScriptRequest(void) {
    if (g_Task->option_flags != 0) {
        if (Actor_StepAnimOnce() & BYTE_MASK) {
            Script_Request(g_Task->direction);
            g_Task->option_flags = 0;
        }
    } else if ((Actor_StepAnimOnce() & BYTE_MASK) && (g_SpawnedActors[g_Task->param.actor_slot].header.flags == 0)) {
        g_Task->unk_2B                     = 0;
        g_Game.current->u.field.mode.value = 0;
    }
}
