/* Runs the area event the work state byte selects. */
/* func_801F2C04 */
MATCH void Area_UpdateEvent(void) {
    SYS_DISPATCH_BYTE(D_801F3418, g_Task->header.step);
}
