#ifndef SYS_LOADER_TAIL_H
#define SYS_LOADER_TAIL_H

#include "types.h"

#define SCENE_FLAG_COUNT 798 /* scene ids with a flag pair */

/* Two flag bytes per scene id, indexed by the scene id (@source: wiki:data/records). */
typedef struct SceneFlagPair {
    u8 flags[2]; /* 0x00 */
} SceneFlagPair;

ASSERT_SIZE(SceneFlagPair, 2);

/* The records behind the main executable's loader pointer lists: a halfword
 * key with two bytes, and a record list with its count. func_8014D6DC passes
 * the halfword to func_8014DD3C and stores the byte at +2 in the work
 * record. */
typedef struct ScriptEntry {
    u16 unk_00;
    u8  unk_02;
    u8  unk_03;
} ScriptEntry;

ASSERT_SIZE(ScriptEntry, 0x04);

/* Entry of D_80181E40: a record list inside s_LoaderRecordBytes and a count. */
typedef struct ScriptList {
    const u8* list;
    u32       count;
} ScriptList;

ASSERT_SIZE(ScriptList, 0x08);

#endif
