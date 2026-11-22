/* Turns the task facing by the held pad direction: down reverses it, right steps it forward and left steps it back, then it is kept to the eight facings. Returns 0 when no direction is held. */
/* func_801F5140 (area104/14), func_801F5684 (area121/14) */
MATCH bool Actor_TurnByPad(void) {
    if (g_PadStates[0].held & PADLdown) {
        TASK(Actor)->direction ^= 4;
    } else if (g_PadStates[0].held & PADLright) {
        TASK(Actor)->direction++;
    } else if (g_PadStates[0].held & PADLleft) {
        TASK(Actor)->direction--;
    } else if (!(g_PadStates[0].held & PADLup)) {
        return 0;
    }
    TASK(Actor)->direction &= 7;
    return 1;
}
