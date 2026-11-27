/* Counts down the work timer at +0x0A; at zero it marks the field actor one facing step ahead and probes that route cell, then its right and lower neighbours when the position is off the cell grid, with PlChar_ProbeCellSpawn, and advances the step. A statement macro: each image names its function. */
#define CHAR_RUN_FACING_PROBE()                                                               \
    {                                                                                         \
        s32 x;                                                                                \
        s32 y;                                                                                \
        s32 hit;                                                                              \
        s32 cell_x;                                                                           \
        s32 cell_y;                                                                           \
        s32 y_ahead;                                                                          \
                                                                                              \
        SELF(Actor)->unk_0A--;                                                                \
        if (SELF(Actor)->unk_0A == 0) {                                                       \
            x       = SELF(Actor)->pos.x.fixed + g_FacingSteps[SELF(Actor)->direction].x * 2; \
            /* FAKE: retail keeps a second copy of the row for the edge test. */              \
            y_ahead = SELF(Actor)->pos.y.fixed + g_FacingSteps[SELF(Actor)->direction].y * 2; \
            y       = y_ahead;                                                                \
            hit     = Actor_FindInRange(x, y, 0);                                             \
            if (hit != -1) {                                                                  \
                g_Actors[hit].interaction_flags |= ACTOR_INTERACTION_PENDING;                 \
            }                                                                                 \
            cell_x = x >> 16;                                                                 \
            cell_y = y >> 16;                                                                 \
            hit    = PlChar_ProbeCellSpawn(cell_x, cell_y);                                   \
            if ((hit & BYTE_MASK) == 0) {                                                     \
                if ((x & HALF_MASK) != 0) {                                                   \
                    hit = PlChar_ProbeCellSpawn((s16)(cell_x + 1), cell_y);                   \
                }                                                                             \
            }                                                                                 \
            if ((hit & BYTE_MASK) == 0) {                                                     \
                if ((y & HALF_MASK) != 0) {                                                   \
                    PlChar_ProbeCellSpawn(cell_x, (s16)(cell_y + 1));                         \
                }                                                                             \
            }                                                                                 \
            SELF(Actor)->header.step++;                                                       \
        }                                                                                     \
        Script_AnimStepOnce();                                                                \
    }
