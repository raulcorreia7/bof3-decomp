/* Counts the active rows of the 60-row fairy roster. */
/* func_801D7E64 (commu02), func_801F02E4 (commu00) */
MATCH u8 Fairy_CountFairies(void) {
    s32 count = 0;
    s32 index;

    for (index = 0; index < 60; index++) {
        if (g_FairyJobs[index].active != 0) {
            count++;
        }
    }

    return count;
}
