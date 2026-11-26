/* Probes the route cell the character stands in: builds the 16.16 position from the work origin and the route velocity table, asks the resident record probe for a nearby field record and checks the cell and its two +1 neighbours for map type 0xF2. Returns nonzero when any probe hits. */
MATCH s32 PlChar_ProbeFacingCell(void) {
    FAKE_REG(s32, found, "v0");
    FAKE_REG(s32, hit, "s1");
    s32 cx;
    s32 cy;

    cx    = SELF(Actor)->pos.x.fixed + g_FacingSteps[SELF(Actor)->direction].x * 2;
    cy    = SELF(Actor)->pos.y.fixed + g_FacingSteps[SELF(Actor)->direction].y * 2;
    found = Actor_FindInRange(cx, cy, 0) != -1;
    hit   = found;
    /* FAKE: retail writes the flag to $v0 and copies it to $s1; keeping the
     * probe result live stops gcc-2.7.2 from coalescing the copy. */
    FAKE_USE(found);
    if ((Area_CellGetCode(cx >> 16, cy >> 16) & BYTE_MASK) == 0xF2) {
        hit = 1;
    }
    if ((cx & HALF_MASK) != 0) {
        if ((Area_CellGetCode((s16)((cx >> 16) + 1), cy >> 16) & BYTE_MASK) == 0xF2) {
            hit = 1;
        }
    }
    if ((cy & HALF_MASK) != 0) {
        if ((Area_CellGetCode(cx >> 16, (s16)((cy >> 16) + 1)) & BYTE_MASK) == 0xF2) {
            hit = 1;
        }
    }
    return hit;
}
