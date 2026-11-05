/* Copies the overlay three-entry step table D_800C1804 and calls the entry the scratchpad step index selects. One
 * definition shared by the boss overlays; each includes this file where the function sits. */
/* func_800C1D98 (boss052), func_800C1EE4 (boss036) */
MATCH void Boss_RunSubStep(void) {
    Callback steps[3];

    memcpy(steps, D_800C1804, sizeof(steps));
    steps[SPAD_WORK_BYTES[2]]();
}
