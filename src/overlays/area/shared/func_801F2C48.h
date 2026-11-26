/* Lifts the HUD banner and starts the away step when the party already stands in the work's entry cell; `edge`
 * is the cell offset of the far side. The caller declares `actor` and `screen_y`. */
#define AREA_ENTRY_CELL_AWAY_STEP(screen_y_value, edge)                                                                      \
    actor = g_Self;                                                                                                          \
    if (actor->direction != 0) {                                                                                             \
        if (abs(g_Game.members[0].pos.y.fixed - ((((s32)COORD_INT(actor->pos.y) + (edge)) << 16) | 0x8000)) <= COORD_HALF) { \
            if (abs(g_Game.members[0].pos.x.fixed - ((s32)COORD_INT(actor->pos.x) << 16)) <= TO_COORD(1) ||                  \
                abs(g_Game.members[0].pos.x.fixed - (((s32)COORD_INT(actor->pos.x) + 1) << 16)) <= TO_COORD(1)) {            \
                screen_y           = screen_y_value;                                                                         \
                actor->screen_y    = screen_y;                                                                               \
                actor->header.step = 3;                                                                                      \
            }                                                                                                                \
        }                                                                                                                    \
    } else {                                                                                                                 \
        if (abs(g_Game.members[0].pos.x.fixed - ((((s32)COORD_INT(actor->pos.x) + (edge)) << 16) | 0x8000)) <= COORD_HALF) { \
            if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(actor->pos.y) << 16)) <= TO_COORD(1) ||                  \
                abs(g_Game.members[0].pos.y.fixed - (((s32)COORD_INT(actor->pos.y) + 1) << 16)) <= TO_COORD(1)) {            \
                screen_y           = screen_y_value;                                                                         \
                actor->screen_y    = screen_y;                                                                               \
                actor->header.step = 3;                                                                                      \
            }                                                                                                                \
        }                                                                                                                    \
    }

/* Starts the work at the entry cell its x index names in the payload's coordinate pairs, then lifts the HUD
 * banner and starts the away step when the party already stands in that cell. The BODY form also runs the area update. */
/* func_801F2C48 (area158), func_801F2C48 (area160), func_801F2C48 (area161), func_801F2C48 (area162),
 * func_801F2C48 (area163), func_801F2C48 (area164), func_801F2C48 (area165), func_801F2C48 (area166), func_801F3484 (area157) */
#define AREA_START_ENTRY_CELL(payload, screen_y_value, edge)                \
    Actor* work;                                                            \
    Actor* cell;                                                            \
    Actor* actor;                                                           \
    s32    entry;                                                           \
    s32    pair;                                                            \
    s16    screen_y;                                                        \
    work                     = g_Self;                                      \
    entry                    = work->pos.x.part.integer;                    \
    pair                     = entry * 2;                                   \
    work->direction          = work->pos.y.part.integer == 0;               \
    cell                     = g_Self;                                      \
    cell->pos.x.part.integer = AREA_PAYLOAD_FIELD(payload, u8, 0x14, pair); \
    cell->pos.y.part.integer = AREA_PAYLOAD_FIELD(payload, u8, 0x15, pair); \
    cell->screen_y           = 0;                                           \
    cell->header.step += 1;                                                 \
    AREA_ENTRY_CELL_AWAY_STEP(screen_y_value, edge)

#define AREA_START_WORK_AT_ENTRY_CELL_BODY(payload, screen_y_value) \
    AREA_START_ENTRY_CELL(payload, screen_y_value, 1);              \
    Area_Update()
