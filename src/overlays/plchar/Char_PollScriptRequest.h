/* Answers the character's script request once ready. */
MATCH void Char_PollScriptRequest(void) {
    if (g_Task->option_flags != 0) {
        if (Actor_StepAnimOnce() & BYTE_MASK) {
            Actor_RequestScript(g_Task->direction_08);
            g_Task->option_flags = 0;
        }
    } else if ((Actor_StepAnimOnce() & BYTE_MASK) && (g_SpawnedActors[g_Task->param.actor_slot].header.flags == 0)) {
        g_Task->unk_2B                            = 0;
        g_Game.current->u.field.mode_12B.s8_value = 0;
    }
}
