/* Returns the index of the trigger box that contains the party member, or 0xFF. */
/* func_801F2D00 (area049), func_801F4110 (area117), func_801F4C08 (area118), func_801F355C (area169), func_801F379C (area171) */

#define AREA_FIND_TRIGGER_BOX_WHILE(member, table, count)                                                                                                   \
    s32 i = 0;                                                                                                                                              \
    s32 j = 0;                                                                                                                                              \
    s32 x = g_Game.members[member].pos.x.fixed;                                                                                                             \
    s32 y = g_Game.members[member].pos.y.fixed;                                                                                                             \
                                                                                                                                                            \
    while (i < (count)) {                                                                                                                                   \
        if (x >= ((s32)(table)[j + 0] << 16) && x <= ((s32)(table)[j + 2] << 16) && y >= ((s32)(table)[j + 1] << 16) && y <= ((s32)(table)[j + 3] << 16)) { \
            return i & 0xFF;                                                                                                                                \
        }                                                                                                                                                   \
        i++;                                                                                                                                                \
        j += 6;                                                                                                                                             \
    }                                                                                                                                                       \
                                                                                                                                                            \
    return 0xFF

#define AREA_FIND_TRIGGER_BOX_DO(member, table, last)                                                                                       \
    s32 x;                                                                                                                                  \
    s32 y;                                                                                                                                  \
    s32 i;                                                                                                                                  \
    s32 off;                                                                                                                                \
                                                                                                                                            \
    i   = 0;                                                                                                                                \
    off = 0;                                                                                                                                \
    x   = g_Game.members[member].pos.x.fixed;                                                                                               \
    y   = g_Game.members[member].pos.y.fixed;                                                                                               \
    do {                                                                                                                                    \
        if (x >= ((table)[off] << 16) && ((table)[off + 2] << 16) >= x && y >= ((table)[off + 1] << 16) && ((table)[off + 3] << 16) >= y) { \
            return i;                                                                                                                       \
        }                                                                                                                                   \
        i++;                                                                                                                                \
        off += 6;                                                                                                                           \
    } while (i <= (last));                                                                                                                  \
    return 0xFF

#define AREA_FIND_TRIGGER_BOX_FOR(member, boxes, count)                                                                         \
    s32 i;                                                                                                                      \
    s32 x = g_Game.members[(member)].pos.x.fixed;                                                                               \
    s32 y = g_Game.members[(member)].pos.y.fixed;                                                                               \
    for (i = 0; i < (count); i++) {                                                                                             \
        if (x < ((boxes)[i].x0 << 16) || x > ((boxes)[i].x1 << 16) || y < ((boxes)[i].y0 << 16) || y > ((boxes)[i].y1 << 16)) { \
            continue;                                                                                                           \
        }                                                                                                                       \
        return i;                                                                                                               \
    }                                                                                                                           \
    return 0xFF
