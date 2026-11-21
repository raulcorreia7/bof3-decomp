/* Probes facing clearance for the free-direction choice; verify every image after a change. */
MATCH void PlChar_ProbeFacingClearance(void) {
    s16 dist;
    s32 x;
    s32 y;

    CHAR_PROBE_FACING_CLEARANCE(dist, x, y)
}
