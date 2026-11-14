/* Runs the personal action's target step: after the turn wait it marks the rock the character faces, or probes the cell ahead for a field actor and a map-cell spawn, then advances the work state. Check every including image after changes. */
/* Each image defines CHAR_CELL_PROBE as its map-cell probe and CHAR_PERSONAL_ACTION_HAS_CUE for its action's cue. */

MATCH void Char_RunPersonalAction(void) {
    s32 cell_x;
    s32 cell_y;
    s32 hit;
    s32 x;
    s32 y;
    /* FAKE: retail keeps the slot byte in $s0 and its sign-extended index in $s1; pure C swaps the pair (best 10 of 147 rows differ). */
    FAKE_REG(s8, slot, "s0");

    if (g_Task->unk_0A != 0) {
        g_Task->unk_0A--;
        if (g_Task->unk_0A == 0) {
            if (CHAR_PERSONAL_ACTION_HAS_CUE) {
                /* FAKE: retail reads SND_PlayCue as void(s32). */
                ((void (*)(s32))SND_PlayCue)(g_Task->unk_2C + 0x100);
            }
            slot = ((s8 (*)(void))Game_FindRockAhead)();
            if (slot != -1) {
                u8 direction;

                if (CHAR_PERSONAL_ACTION_HAS_CUE) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 11));
                }
                direction                 = g_Task->direction_08;
                g_SpawnedActors[slot].unk_0A = 1;
                g_SpawnedActors[slot].unk_08 = direction;
                if (!CHAR_PERSONAL_ACTION_HAS_CUE) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 11));
                }
                g_Task->unk_06 = slot;
                g_Task->unk_03++;
            } else {
                x   = g_Task->pos.x.fixed + g_FacingSteps[g_Task->direction_08].x * 2;
                y   = g_Task->pos.y.fixed + g_FacingStepY[g_Task->direction_08 * 2] * 2;
                hit = Actor_FindInRange(x, y, 0);
                if (hit != slot) {
                    g_Actors[hit].interaction_flags |= ACTOR_FLAG_INTERACTION_PENDING;
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 11));
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
            g_Task->unk_03++;
        }
    }
    Actor_StepAnimOnce();
}
