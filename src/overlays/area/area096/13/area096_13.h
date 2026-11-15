#ifndef OVERLAY_WORLD02_AREA096_13_H
#define OVERLAY_WORLD02_AREA096_13_H

/* The world02/area096/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

extern u8 D_801F3614[];

void func_801F2ECC(s32 arg0, s32 arg1);

/* One spawned-actor row field the spawn step stamps, as a column over the
 * g_SpawnedActors rows: a field and the rest of its row as padding. */
typedef struct SpawnActorByteColumn {
    u8 value;
    u8 pad[ACTOR_SLOT_SIZE - 1];
} SpawnActorByteColumn;

typedef struct SpawnActorHalfColumn {
    u16 value;
    u8  pad[ACTOR_SLOT_SIZE - 2];
} SpawnActorHalfColumn;

typedef struct SpawnActorWordColumn {
    s32 value;
    u8  pad[ACTOR_SLOT_SIZE - 4];
} SpawnActorWordColumn;

ASSERT_SIZE(SpawnActorByteColumn, ACTOR_SLOT_SIZE);
ASSERT_SIZE(SpawnActorHalfColumn, ACTOR_SLOT_SIZE);
ASSERT_SIZE(SpawnActorWordColumn, ACTOR_SLOT_SIZE);

extern SpawnActorByteColumn D_80143FC8[];
extern SpawnActorByteColumn D_80143FCD[];
extern SpawnActorByteColumn D_80143FCE[];
extern SpawnActorByteColumn D_80143FCF[];
extern SpawnActorByteColumn D_80143FD1[];
extern SpawnActorByteColumn D_80143FF1[];
extern SpawnActorHalfColumn D_80143FF4[];
extern SpawnActorWordColumn D_80143FFC[];
extern SpawnActorWordColumn D_80144000[];
extern SpawnActorWordColumn D_80144004[];

#endif
