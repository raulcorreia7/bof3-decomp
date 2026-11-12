#ifndef SHARED_SCENE_TRAIL_H
#define SHARED_SCENE_TRAIL_H

#include "common/vector.h"

/* One row of the scene trail the overlays project from the work position: the world position, its screen point, the
 * segment angle and the ribbon size at the row. */
typedef struct SceneTrailRow {
    WorldPos pos;      /* 0x00 */
    u32      unk_0C;   /* 0x0C */
    u16      screen_x; /* 0x10 */
    u16      screen_y; /* 0x12 */
    u16      angle;    /* 0x14 */
    s16      size;     /* 0x16 */
} SceneTrailRow;

ASSERT_SIZE(SceneTrailRow, 0x18);
ASSERT_OFFSET(SceneTrailRow, pos, 0x00);
ASSERT_OFFSET(SceneTrailRow, screen_x, 0x10);
ASSERT_OFFSET(SceneTrailRow, screen_y, 0x12);
ASSERT_OFFSET(SceneTrailRow, angle, 0x14);
ASSERT_OFFSET(SceneTrailRow, size, 0x16);

/* The trail the scene and area overlays keep at 0x800E48E0: 32 projected rows, the angle of each projected segment
 * and the projection size all rows share. */
typedef struct SceneTrail {
    SceneTrailRow rows[32];  /* 0x000 */
    u16           angle[31]; /* 0x300 */
    u16           size;      /* 0x33E */
} SceneTrail;

ASSERT_SIZE(SceneTrail, 0x340);
ASSERT_OFFSET(SceneTrail, rows, 0x000);
ASSERT_OFFSET(SceneTrail, angle, 0x300);
ASSERT_OFFSET(SceneTrail, size, 0x33E);

#endif
