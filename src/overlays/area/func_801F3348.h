/* One definition shared by the ten world04 area request overlays
 * (emi/world04/area176/13 through emi/world04/area185/13) at 0x801F3348;
 * every change here must verify every member address. */
MATCH void func_801F3348(void) {
    if (g_AreaScrollTargetX <= TO_COORD(46)) {
        g_Task->pos.x.fixed = g_AreaScrollTargetX;
    }
}
