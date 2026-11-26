/* Probes the route cell the character stands in: builds the 16.16 position from the work origin and the route velocity table, asks the resident record probe for a nearby field record and checks the cell and its two +1 neighbours for map type 0xF2. Returns nonzero when any probe hits. */
MATCH s32 PlChar_ProbeFacingCell(void) {
    s32 cx;
    s32 cy;
    u8  hit;

    cx  = SELF(Actor)->pos.x.fixed + g_FacingSteps[SELF(Actor)->direction].x * 2;
    cy  = SELF(Actor)->pos.y.fixed + g_FacingSteps[SELF(Actor)->direction].y * 2;
    hit = Actor_FindInRange(cx, cy, 0) != -1;
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
