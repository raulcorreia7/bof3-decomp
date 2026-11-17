/* Turns the task facing by the held pad direction: down reverses it, right steps it forward and left steps it back, then it is kept to the eight facings. Returns 0 when no direction is held. */
/* func_801F5140 (area104/14), func_801F5684 (area121/14) */
MATCH bool Actor_TurnByPad(void) {
    if (g_InputHeld & PADLdown) {
        g_Task->direction ^= 4;
    } else if (g_InputHeld & PADLright) {
        g_Task->direction++;
    } else if (g_InputHeld & PADLleft) {
        g_Task->direction--;
    } else if (!(g_InputHeld & PADLup)) {
        return 0;
    }
    g_Task->direction &= 7;
    return 1;
}
