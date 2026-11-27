/* Facing clearance body shared by plp016, plp026, plp034, plp056, plp267, plp349, plp467, plp567 and plp678. */
#define CHAR_DEFINE_PROBE_FACING_BLOCKED(NAME)                          \
    MATCH s32 NAME(void) {                                              \
        Actor* task;                                                    \
        u8     direction;                                               \
        s32    x;                                                       \
        s32    y;                                                       \
        u8     blocked;                                                 \
        s32    cell;                                                    \
                                                                        \
        task      = SELF(Actor);                                        \
        direction = task->direction;                                    \
        x         = task->pos.x.fixed + g_FacingSteps[direction].x * 2; \
        y         = task->pos.y.fixed + g_FacingSteps[direction].y * 2; \
        blocked   = Actor_FindInRange(x, y, 0) != -1;                   \
        if (((s8 (*)(void))Game_FindRockAhead)() != -1) {               \
            blocked = 1;                                                \
        }                                                               \
                                                                        \
        cell = Area_CellGetCode(x >> 16, y >> 16);                      \
        if (CHAR_CELL_CODE_BLOCKS_CHARACTER(cell)) {                    \
            blocked = 1;                                                \
        }                                                               \
        if ((x & HALF_MASK) != 0) {                                     \
            cell = Area_CellGetCode((s16)((x >> 16) + 1), y >> 16);     \
            if (CHAR_CELL_CODE_BLOCKS_CHARACTER(cell)) {                \
                blocked = 1;                                            \
            }                                                           \
        }                                                               \
        if ((y & HALF_MASK) != 0) {                                     \
            cell = Area_CellGetCode(x >> 16, (s16)((y >> 16) + 1));     \
            if (CHAR_CELL_CODE_BLOCKS_CHARACTER(cell)) {                \
                blocked = 1;                                            \
            }                                                           \
        }                                                               \
        return blocked;                                                 \
    }
