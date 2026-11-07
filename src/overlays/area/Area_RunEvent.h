/* Runs the area event the work state byte selects. One definition
 * shared by the world04 area overlays; every change here must verify every
 * member. */
/* func_801F2C04 */
MATCH void Area_RunEvent(void) {
    SYS_DISPATCH_BYTE(D_801F3418, g_Task->header.step);
}
