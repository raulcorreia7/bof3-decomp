#include "engine/slus/slus.h"

/* One band: the marked_id fires when the work record's x and y both lie within `radius` of the target point
 * (g_AreaTargetCellX, g_AreaTargetCellY); `table` is the marked_id table the band stores. */
#define SND_PROXIMITY_BAND(radius, table)              \
    work   = g_Self;                                   \
    x      = COORD_INT(work->pos.x);                   \
    target = g_AreaTargetCellX;                        \
    edge   = x + (radius);                             \
    if (edge >= target) {                              \
        edge = x - (radius);                           \
        if (target >= edge) {                          \
            y      = COORD_INT(work->pos.y);           \
            target = g_AreaTargetCellY;                \
            edge   = y + (radius);                     \
            if (edge >= target) {                      \
                edge = y - (radius);                   \
                if (target >= edge) {                  \
                    g_SndSeVolumeL = (table);          \
                    g_SndSeVolumeR = (table);          \
                    SND_SEPlay(marked_id & HALF_MASK); \
                }                                      \
            }                                          \
        }                                              \
    }

/* raises the proximity marked_id selected by the active work area's
 * distance from the target point, testing the six nested radii from widest to
 * tightest and only the first matching band fires.
 */
MATCH void SND_SEQueueProximity(s32 se_id) {
    Actor* work;
    /* FAKE: the axis value stays in a0 across both range tests. */
    FAKE_REG(s32, x, "a0");
    s32 y;
    s32 target;
    s32 edge;
    s32 marked_id;

    marked_id = se_id | 0x8000;
    SND_PROXIMITY_BAND(0x16, g_SndVolumeLevels[64])
    SND_PROXIMITY_BAND(0x12, g_SndVolumeLevels[64])
    SND_PROXIMITY_BAND(0xc, g_SndVolumeLevels[49])
    SND_PROXIMITY_BAND(8, g_SndVolumeLevels[33])
    SND_PROXIMITY_BAND(6, g_SndVolumeLevels[17])
    SND_PROXIMITY_BAND(2, g_SndVolumeLevels[4])
}
