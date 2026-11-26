/* Runs the personal action's target step: after the turn wait it marks the rock the character faces, or probes the cell ahead for a field actor and a map-cell spawn, then advances the work state. Check every including image after changes. */
/* Each image defines CHAR_CELL_PROBE as its map-cell probe and CHAR_PERSONAL_ACTION_HAS_CUE for its action's cue. */

MATCH void PlChar_RunPersonalAction(void) {
    s32 cell_x;
    s32 cell_y;
    s32 hit;
    s32 x;
    s32 y;
    /* FAKE: retail keeps the slot byte in $s0 and its sign-extended index in $s1; pure C swaps the pair (best 10 of 147 rows differ). */
    FAKE_REG(s8, slot, "s0");

    if (TASK(Actor)->unk_0A != 0) {
        TASK(Actor)->unk_0A--;
        if (TASK(Actor)->unk_0A == 0) {
            if (CHAR_PERSONAL_ACTION_HAS_CUE) {
                /* FAKE: retail reads SND_SEPlay as void(s32). */
                ((void (*)(s32))SND_SEPlay)(TASK(Actor)->unk_2C + 0x100);
            }
            slot = ((s8 (*)(void))Game_FindRockAhead)();
            if (slot != -1) {
                u8 direction;

                if (CHAR_PERSONAL_ACTION_HAS_CUE) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 11));
                }
                direction                    = TASK(Actor)->direction;
                g_SpawnedActors[slot].unk_0A = 1;
                g_SpawnedActors[slot].unk_08 = direction;
                if (!CHAR_PERSONAL_ACTION_HAS_CUE) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 11));
                }
                TASK(Actor)->unk_06 = slot;
                TASK(Actor)->unk_03++;
            } else {
                x   = TASK(Actor)->pos.x.fixed + g_FacingSteps[TASK(Actor)->direction].x * 2;
                y   = TASK(Actor)->pos.y.fixed + g_FacingSteps[TASK(Actor)->direction].y * 2;
                hit = Actor_FindInRange(x, y, 0);
                if (hit != slot) {
                    g_Actors[hit].interaction_flags |= ACTOR_INTERACTION_PENDING;
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 11));
                }
                cell_x = x >> 16;
                cell_y = y >> 16;
                hit    = CHAR_CELL_PROBE(cell_x, cell_y);
                if ((hit & BYTE_MASK) == 0) {
                    if ((x & HALF_MASK) != 0) {
                        hit = CHAR_CELL_PROBE((s16)(cell_x + 1), cell_y);
                    }
                }
                if ((hit & BYTE_MASK) == 0) {
                    if ((y & HALF_MASK) != 0) {
                        CHAR_CELL_PROBE(cell_x, (s16)(cell_y + 1));
                    }
                }
            }
            TASK(Actor)->unk_03++;
        }
    }
    Script_AnimStepOnce();
}
