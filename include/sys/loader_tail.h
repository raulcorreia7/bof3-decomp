#ifndef SYS_LOADER_TAIL_H
#define SYS_LOADER_TAIL_H

#include "types.h"

#define SCENE_FLAG_COUNT 798 /* scene ids with a flag pair */

/* Two flag bytes per scene id, indexed by the scene id (@source: wiki:data/records). */
typedef struct SceneFlagPair {
    u8 unk_00; /* 0x00 */
    u8 unk_01; /* 0x01 */
} SceneFlagPair;

ASSERT_SIZE(SceneFlagPair, 2);

/* The records behind the main executable's loader pointer lists. */
typedef struct ScriptRef {
    u16 unk_00;
    u8  unk_02;
    u8  unk_03;
} ScriptRef;

ASSERT_SIZE(ScriptRef, 0x04);

/* Entry of D_80181E40: a record list inside D_80181D98 and a count. */
typedef struct Rec8_80181E40 {
    const u8* list;
    u32       count;
} Rec8_80181E40;

ASSERT_SIZE(Rec8_80181E40, 0x08);

#endif
