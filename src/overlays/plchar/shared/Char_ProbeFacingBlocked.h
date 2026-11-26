/* Facing clearance body shared by plp016, plp026, plp034, plp056, plp267, plp349, plp467, plp567 and plp678. */
#define CHAR_DEFINE_PROBE_FACING_BLOCKED(NAME)                      \
    MATCH s32 NAME(void) {                                          \
        /* FAKE: retains the retail register allocation. */         \
        FAKE_REG(Actor*, task, "a1");                               \
        FAKE_REG(u8, direction, "v1");                              \
        FAKE_REG(s32, value, "v0");                                 \
        FAKE_REG(s32, x, "s1");                                     \
        FAKE_REG(s32, y, "s0");                                     \
        FAKE_REG(s32, pos_y, "v1");                                 \
        FAKE_REG(s32, blocked, "s2");                               \
        FAKE_REG(s32, pos_x, "a0");                                 \
        FAKE_REG(s32, range_mode, "a2");                            \
        FAKE_REG(s32, sentinel, "v1");                              \
        s32 cell;                                                   \
                                                                    \
        task = g_Task;                                              \
        FAKE_USE(task);                                             \
        direction = task->direction;                                \
        FAKE_USE(direction);                                        \
        range_mode = 0;                                             \
        value      = g_FacingSteps[direction].x;                    \
        pos_x      = task->pos.x.fixed;                             \
        value *= 2;                                                 \
        FAKE_USE(value);                                            \
        x     = pos_x + value;                                      \
        pos_x = x;                                                  \
        FAKE_USE(pos_x);                                            \
        value = g_FacingSteps[direction].y;                         \
        FAKE_USE(value);                                            \
        pos_y = task->pos.y.fixed;                                  \
        FAKE_USE(pos_y);                                            \
        y     = pos_y + value * 2;                                  \
        value = Actor_FindInRange(pos_x, y, range_mode) != -1;      \
        FAKE_USE(value);                                            \
        blocked  = value;                                           \
        value    = ((s8 (*)(void))Game_FindRockAhead)();            \
        sentinel = -1;                                              \
        if ((s8)value != sentinel) {                                \
            blocked = 1;                                            \
        }                                                           \
                                                                    \
        cell = Area_CellGetCode(x >> 16, y >> 16);                  \
        if (CHAR_CELL_CODE_BLOCKS_CHARACTER(cell)) {                \
            blocked = 1;                                            \
        }                                                           \
        if ((x & HALF_MASK) != 0) {                                 \
            cell = Area_CellGetCode((s16)((x >> 16) + 1), y >> 16); \
            if (CHAR_CELL_CODE_BLOCKS_CHARACTER(cell)) {            \
                blocked = 1;                                        \
            }                                                       \
        }                                                           \
        if ((y & HALF_MASK) != 0) {                                 \
            cell = Area_CellGetCode(x >> 16, (s16)((y >> 16) + 1)); \
            if (CHAR_CELL_CODE_BLOCKS_CHARACTER(cell)) {            \
                blocked = 1;                                        \
            }                                                       \
        }                                                           \
        return blocked;                                             \
    }
