/* Starts the work at the entry cell its x index names in the payload's coordinate pairs, then lifts the HUD
 * banner and starts the away step when the party already stands in that cell. */
/* func_801F2C48 (area158), func_801F2C48 (area160), func_801F2C48 (area161), func_801F2C48 (area162),
 * func_801F2C48 (area163), func_801F2C48 (area164), func_801F2C48 (area165), func_801F2C48 (area166) */
#define AREA_START_WORK_AT_ENTRY_CELL_BODY(payload, screen_y_value)                                                   \
    Actor* work;                                                                                                      \
    Actor* cell;                                                                                                      \
    Actor* row;                                                                                                       \
    s32    entry;                                                                                                     \
    s32    pair;                                                                                                      \
    s16    screen_y;                                                                                                  \
    work                     = g_Task;                                                                                \
    entry                    = work->pos.x.part.integer;                                                              \
    pair                     = entry * 2;                                                                             \
    work->direction_08       = work->pos.y.part.integer == 0;                                                         \
    cell                     = g_Task;                                                                                \
    cell->pos.x.part.integer = WORLD04_ENTRY_TABLE(payload, u8, 0x14, pair);                                          \
    cell->pos.y.part.integer = WORLD04_ENTRY_TABLE(payload, u8, 0x15, pair);                                          \
    cell->screen_y           = 0;                                                                                     \
    cell->header.step += 1;                                                                                           \
    row = g_Task;                                                                                                     \
    if (row->direction_08 != 0) {                                                                                     \
        if (abs(g_Game.members[0].pos.y.fixed - ((((s32)COORD_INT(row->pos.y) + 1) << 16) | 0x8000)) <= COORD_HALF) { \
            if (abs(g_Game.members[0].pos.x.fixed - ((s32)COORD_INT(row->pos.x) << 16)) <= TO_COORD(1) ||             \
                abs(g_Game.members[0].pos.x.fixed - (((s32)COORD_INT(row->pos.x) + 1) << 16)) <= TO_COORD(1)) {       \
                screen_y         = screen_y_value;                                                                    \
                row->screen_y    = screen_y;                                                                          \
                row->header.step = 3;                                                                                 \
            }                                                                                                         \
        }                                                                                                             \
    } else {                                                                                                          \
        if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(row->pos.x) + 1) << 16) | 0x8000)) <= COORD_HALF) { \
            if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(row->pos.y) << 16)) <= TO_COORD(1) ||             \
                abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(row->pos.y) + 1) << 16)) <= TO_COORD(1)) {       \
                screen_y         = screen_y_value;                                                                    \
                row->screen_y    = screen_y;                                                                          \
                row->header.step = 3;                                                                                 \
            }                                                                                                         \
        }                                                                                                             \
    }                                                                                                                 \
    Area_Update()
