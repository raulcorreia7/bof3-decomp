/* Turns the task facing by the held pad direction: down reverses it, right steps it
 * forward and left steps it back, then it is kept to the eight facings. Returns 0 when
 * no direction is held. One definition shared by the area overlays. Every change here
 * must verify every member address. */
/* func_801F5140 (area104/14), func_801F5684 (area121/14) */
MATCH bool Actor_TurnByPad(void) {
    if (g_InputHeld & 0x4000) {
        g_Task->direction_08 ^= 4;
    } else if (g_InputHeld & 0x2000) {
        g_Task->direction_08++;
    } else if (g_InputHeld & 0x8000) {
        g_Task->direction_08--;
    } else if (!(g_InputHeld & 0x1000)) {
        return 0;
    }
    g_Task->direction_08 &= 7;
    return 1;
}
