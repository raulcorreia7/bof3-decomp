/* Keeps the actor slot referenced at the work byte 0x0B hidden while the timer at byte 0x09 counts down. */
/* func_801F3480 (area032), func_801F78E0 (scena03) */
MATCH void Actor_Reveal(void) {
    u8* work;

    work = (u8*)g_Task;
    if (work[9] != 0) {
        g_Actors[work[11]].header.flags |= ACTOR_FLAG_HIDDEN;
        g_Task->timer -= 1;
    } else {
        g_Actors[work[11]].header.flags &= ~ACTOR_FLAG_HIDDEN;
        g_Actors[g_Task->unk_03].header.flags = 0;
        g_Actors[g_Task->unk_04].header.flags = 0;
        g_Task->header.mode                   = 2;
    }
}
