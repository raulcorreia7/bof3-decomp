/* Facing clearance body shared by plp016, plp026, plp034, plp056, plp267, plp349, plp467, plp567 and plp678. */
#define CHAR_DEFINE_PROBE_FACING_BLOCKED(NAME) \
MATCH s32 NAME(void) { \
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail loads the work pointer before the frame. */ \
    FAKE_REG(Actor*, task, "a1"); \
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail keeps the facing index in v1. */ \
    FAKE_REG(u8, direction, "v1"); \
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail reuses v0 for steps, actor flag, and rock index. */ \
    FAKE_REG(s32, value, "v0"); \
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail keeps the x coordinate in s1. */ \
    FAKE_REG(s32, x, "s1"); \
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail keeps the y coordinate in s0. */ \
    FAKE_REG(s32, y, "s0"); \
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail loads the y base into v1. */ \
    FAKE_REG(s32, pos_y, "v1"); \
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail keeps the blocked flag in s2. */ \
    FAKE_REG(s32, blocked, "s2"); \
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail passes x in a0 before the y probe. */ \
    FAKE_REG(s32, pos_x, "a0"); \
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail sets the range mode in a2. */ \
    FAKE_REG(s32, range_mode, "a2"); \
    /* FAKE: pure C is 0x1A0 vs 0x1A4; retail compares the rock result with -1 in v1. */ \
    FAKE_REG(s32, sentinel, "v1"); \
    s32 cell; \
 \
    task = g_Task; \
    FAKE_USE(task); /* FAKE: pure C is 0x1A0; the work pointer load follows the prologue. */ \
    direction = task->direction_08; \
    FAKE_USE(direction); /* FAKE: pure C is 0x1A0; the facing index uses v0. */ \
    range_mode = 0; \
    value      = g_FacingSteps[direction].x; \
    pos_x      = task->pos.x.fixed; \
    value *= 2; \
    FAKE_USE(value); /* FAKE: pure C is 0x1A0; x absorbs the doubled step in s1. */ \
    x     = pos_x + value; \
    pos_x = x; \
    FAKE_USE(pos_x); /* FAKE: pure C is 0x1A0; the x argument moves before the y probe. */ \
    value = g_FacingStepY[direction * 2]; \
    FAKE_USE(value); /* FAKE: pure C is 0x1A0; the y step stays in s0. */ \
    pos_y = task->pos.y.fixed; \
    FAKE_USE(pos_y); /* FAKE: pure C is 0x1A0; the y base loads into s0. */ \
    y     = pos_y + value * 2; \
    value = Actor_FindInRange(pos_x, y, range_mode) != -1; \
    FAKE_USE(value); /* FAKE: pure C is 0x1A0; the flag compare moves into the call slot. */ \
    blocked  = value; \
    value    = ((s8 (*)(void))Game_FindRockAhead)(); \
    sentinel = -1; \
    if ((s8)value != sentinel) { \
        blocked = 1; \
    } \
 \
    cell = Area_GetCellCode(x >> 16, y >> 16); \
    if ((u8)(cell + 0x10) < 2 || (u8)cell == 0xF4 || (u8)(cell + 0xA) < 2) { \
        blocked = 1; \
    } \
    if ((x & HALF_MASK) != 0) { \
        cell = Area_GetCellCode((s16)((x >> 16) + 1), y >> 16); \
        if ((u8)(cell + 0x10) < 2 || (u8)cell == 0xF4 || (u8)(cell + 0xA) < 2) { \
            blocked = 1; \
        } \
    } \
    if ((y & HALF_MASK) != 0) { \
        cell = Area_GetCellCode(x >> 16, (s16)((y >> 16) + 1)); \
        if ((u8)(cell + 0x10) < 2 || (u8)cell == 0xF4 || (u8)(cell + 0xA) < 2) { \
            blocked = 1; \
        } \
    } \
    return blocked; \
}
