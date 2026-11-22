/* Answers the character's script request once ready. */
MATCH void PlChar_PollScriptRequest(void) {
    if (TASK(Actor)->option_flags != 0) {
        if (Script_AnimStepOnce() & BYTE_MASK) {
            Script_Request(TASK(Actor)->direction);
            TASK(Actor)->option_flags = 0;
        }
    } else if ((Script_AnimStepOnce() & BYTE_MASK) && (g_SpawnedActors[TASK(Actor)->param.actor_slot].header.flags == 0)) {
        TASK(Actor)->unk_2B                = 0;
        g_Game.current->u.field.mode.value = 0;
    }
}
