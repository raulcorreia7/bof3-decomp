/* Copies the overlay three-entry step table D_800C1804 and calls the entry the scratchpad step index selects. */
/* func_800C1D98 (boss052), func_800C1EE4 (boss036) */
MATCH void Boss_RunSubStep(void) {
    Callback steps[3];

    memcpy(steps, D_800C1804, sizeof(steps));
    steps[g_Task->header.step]();
}
