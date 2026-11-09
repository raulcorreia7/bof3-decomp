/* Zeroes the spad actor's velocity members vx, vy and vz. */
/* func_801C5798 (game), func_801F5F20 (area189) */
MATCH void Actor_ClearVelocity(void) {
    g_Task->vx = 0;
    g_Task->vy = 0;
    g_Task->vz = 0;
}
