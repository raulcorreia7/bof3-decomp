#ifndef OVERLAY_SCENARIO_SCENA10_00_H
#define OVERLAY_SCENARIO_SCENA10_00_H

/* The scenario/scena10/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"

/* FAKE: the callers pass the arguments as s32, the width the real prototype (u8) lacks. */
#define Item_Count ((s32 (*)(s32, s32, s32))Item_Count)

extern u8   D_80144908[];
extern s16  D_801492DA;
extern u8   D_80181BD7;
extern u32  D_801F6C00;
extern char D_801F6C04[];
extern char D_801F6C08[];
extern char D_801F6C10[];

/* A scene rectangle the panel draws: position and size. */
typedef struct Scena10Rect {
    s16 x;      /* 0x00 */
    s16 y;      /* 0x02 */
    u16 width;  /* 0x04 */
    u16 height; /* 0x06 */
} Scena10Rect;

ASSERT_OFFSET(Scena10Rect, x, 0x00);
ASSERT_OFFSET(Scena10Rect, y, 0x02);
ASSERT_OFFSET(Scena10Rect, width, 0x04);
ASSERT_OFFSET(Scena10Rect, height, 0x06);
ASSERT_SIZE(Scena10Rect, 8);

/* The panel draws entry 2. */
extern Scena10Rect D_801FE7CC[];
extern u8          D_801FE804[2];
extern u8          D_801FE808[2];
extern u8          D_801FE830[8][3];
extern Pos2        D_801FE848[];
extern u8          D_801FE874[];

/* The g_SceneFlags bit the scene trigger row flags count from. */
#define SCENE_TRIGGER_FLAG_BASE 0x20

/* The scene trigger rows func_801FD5C0 and func_801FD734 search by cell: the scene flag bit
 * that marks the row used, the script it starts, and the cell it covers. Sixteen rows fill the
 * span up to D_801FE8F4. */
typedef struct SceneTriggerRow {
    u8  flag;   /* +0x0 - flag bit index, offset by SCENE_TRIGGER_FLAG_BASE, in g_SceneFlags */
    u8  script; /* +0x1 - Actor_SelectScript selector */
    u16 x;      /* +0x2 - cell x, compared with the work record's pos.x integer */
    u16 y;      /* +0x4 - cell y, compared with the work record's pos.y integer */
} SceneTriggerRow;

ASSERT_OFFSET(SceneTriggerRow, script, 0x01);
ASSERT_OFFSET(SceneTriggerRow, x, 0x02);
ASSERT_OFFSET(SceneTriggerRow, y, 0x04);
ASSERT_SIZE(SceneTriggerRow, 6);

/* D_801FE80C */
extern Callback        D_801FE820[];
extern SceneTriggerRow D_801FE894[16];
extern Callback        D_801FE8F4[];

extern Callback D_801FE900[];
extern u8       D_801FE938[];

extern s8  D_801FE94C[4];
extern u8  D_801FE950[4];
extern u16 D_801FE954[4];
extern u8  D_801FE95C[5];
extern u16 D_801FE964[5];
extern u8  D_801FE970[3];
extern u16 D_801FE974[3];
extern u8  D_801FE9D8;
extern u8  D_801FE9DC;
/* D_801FE97C */

/* The two end-of-pan actors of func_801FC900: spawn a type 0x13 actor on layer 0x40 with the given x and z scene rotation and the current y. */
#define SCENA10_SPAWN_ANGLED_ACTOR(angle_x, angle_z)                                  \
    do {                                                                              \
        u8 slot;                                                                      \
                                                                                      \
        slot                        = Actor_FindFreeSpawned();                        \
        g_ScratchPad.cells.bytes[0] = slot;                                           \
        if (slot != GAME_NONE) {                                                      \
            g_SpawnedActors[slot].header.flags                          = 1;          \
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;       \
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = (angle_x);  \
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = D_801492DA; \
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = (angle_z);  \
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x40;       \
        }                                                                             \
    } while (0)

/* The actor-start members of 3D8C.c: start the actor, then raise a scene flag. They differ only in the three constants. */
#define SCENA10_ACTOR_START(scene, step, flag) \
    do {                                       \
        SCENE_START_ACTOR(actor, scene, step); \
        SYS_SetFlag(g_SceneFlags, (flag));     \
    } while (0)

/* The party lookups of 3D8C.c: return the value paired with the first id in `ids` that a party member holds, else `none`. The members differ only in table and count. */
#define SCENA10_PARTY_LOOKUP(count, ids, values, none)                        \
    do {                                                                      \
        u8 slot;                                                              \
        u8 member;                                                            \
                                                                              \
        for (slot = 0; slot < (count); slot++) {                              \
            for (member = 0; member < g_Game.party_size; member++) {          \
                if (g_Game.members[member].chr.character_id == (ids)[slot]) { \
                    return (values)[slot];                                    \
                }                                                             \
            }                                                                 \
        }                                                                     \
        return (none);                                                        \
    } while (0)

void func_801F6FAC(void);
void func_801F781C(u16 x, u16 y, u16 width, u16 height);
void func_801F79E8(u16 x, u16 y);
u16  func_801FD278(void);

#endif
