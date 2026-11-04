#include "engine/slus/slus.h"

/* One band: the cue fires when the work record's x and y both lie within `radius` of the target point
 * (D_8014930A, D_8014930E); `table` is the cue table the band stores. */
#define SND_PROXIMITY_BAND(radius, table)         \
    work   = g_SpadWork;                          \
    x      = work->x.part.integer;                \
    target = D_8014930A;                          \
    edge   = x + (radius);                        \
    if (edge >= target) {                         \
        edge = x - (radius);                      \
        if (target >= edge) {                     \
            y      = work->y.part.integer;        \
            target = D_8014930E;                  \
            edge   = y + (radius);                \
            if (edge >= target) {                 \
                edge = y - (radius);              \
                if (target >= edge) {             \
                    D_8018B3D8 = (table);         \
                    D_8018B3DC = (table);         \
                    SND_PlayCue(cue & HALF_MASK); \
                }                                 \
            }                                     \
        }                                         \
    }

/* raises the proximity cue selected by the active work area's
 * distance from the target point, testing the six nested radii from widest to
 * tightest and only the first matching band fires.
 */
MATCH void SND_QueueProximityCue(s32 cue_id) {
    Actor* work;
    /* FAKE: the axis value stays in a0 across both range tests. */
    MATCH_REG(s32, x, "a0");
    s32 y;
    s32 target;
    s32 edge;
    s32 cue;

    cue = cue_id | 0x8000;
    SND_PROXIMITY_BAND(0x16, D_80182308[0])
    SND_PROXIMITY_BAND(0x12, D_80182308[0])
    SND_PROXIMITY_BAND(0xc, D_801822EA)
    SND_PROXIMITY_BAND(8, D_801822CA)
    SND_PROXIMITY_BAND(6, D_801822AA)
    SND_PROXIMITY_BAND(2, D_80182290[0])
}
