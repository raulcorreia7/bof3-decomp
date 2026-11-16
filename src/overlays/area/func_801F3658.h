/* One map cell marks each area's entry event: the body counts that cell at the
 * party's entry point and its three forward neighbours, starts the area's event
 * when any holds it, and returns whether it started. The function's parameters
 * are `x` and `y`. */
/* func_801F3658 (area191), func_801F3118 (area192) */
#define AREA_START_ENTRY_EVENT(event)                                                   \
    s32 cell_x;                                                                         \
    s32 cell_y;                                                                         \
    u8  hit;                                                                            \
    u8  count;                                                                          \
    s32 code;                                                                           \
    cell_x = x >> 16;                                                                   \
    cell_y = y >> 16;                                                                   \
    count = hit = (u8)Area_GetCellCode(cell_x, cell_y) == 0xA6;                         \
    code        = 0xA6;                                                                 \
    if ((x & HALF_MASK) != 0) {                                                         \
        if ((u8)Area_GetCellCode((s16)(cell_x + 1), cell_y) == code) {                  \
            count++;                                                                    \
        }                                                                               \
    }                                                                                   \
    if ((y & HALF_MASK) != 0) {                                                         \
        if ((u8)Area_GetCellCode(x >> 16, (s16)((y >> 16) + 1)) == 0xA6) {              \
            count++;                                                                    \
        }                                                                               \
    }                                                                                   \
    if ((x & HALF_MASK) != 0 && (y & HALF_MASK) != 0) {                                 \
        if ((u8)Area_GetCellCode((s16)((x >> 16) + 1), (s16)((y >> 16) + 1)) == 0xA6) { \
            count++;                                                                    \
        }                                                                               \
    }                                                                                   \
    if (count != 0) {                                                                   \
        Scene_StartEvent(event, 0);                                                     \
        return 1;                                                                       \
    }                                                                                   \
    return 0
