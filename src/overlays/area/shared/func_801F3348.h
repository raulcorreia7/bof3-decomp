MATCH void func_801F3348(void) {
    if (g_AreaScrollTargetX <= TO_COORD(46)) {
        SELF(Actor)->pos.x.fixed = g_AreaScrollTargetX;
    }
}
