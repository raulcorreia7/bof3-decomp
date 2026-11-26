#ifndef OVERLAY_WORLD03_AREA135_14_H
#define OVERLAY_WORLD03_AREA135_14_H

/* The world03/area135/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "sys/actor.h"
#include "overlays/area/worlds/world03.h"
#include "scenario/party.h"

/* The fixed work record the dispatch compares the work pointer against. */
extern Actor D_80143F48;
/* The area flag byte the request step sets. */
extern u8    D_80143FBC;
/* The four party work rows, and the shadow record each party row owns: 0x10
 * bytes, its flag byte first. */

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The shared flag word the close path clears a bit of. */

/* The battle-step selector and the pan word the callers step. */
/* The shared message buffer the setup publishes and its frame extent. */
/* The battle-step selector the close path clears. */
/* The shared flag word the cancel path clears a bit of. */

/* The shared flag byte the request path sets a bit of. */
/* The request selector and the bytes the cancel path sets. */
/* The field mode bytes the height steps test. */
/* The shared camera-position words the view step copies. */
/* The camera seed halfword the request step stores. */

extern char D_801F2C04[];
/* D_80149340 */

/* The state handler tables the dispatchers index. */
extern u8       D_801F61F8[];
extern Callback D_801F6200[];

/* The panel box words UI_WindowDrawPanelBox draws: x, y, width and height. */
extern u16 D_801F6210;
extern u16 D_801F6212;
extern u16 D_801F6214;
extern u16 D_801F6216;
extern u8  D_801F69AF;
/* D_801F6BC0 */
extern u8  g_SceneActorSlot;

/* Places the task at the area focus point and reads the height there. */
void func_801F32A0(s32 value);
/* Draws the cross of lines at a world point, tinted by the task red. */
void func_801F3308(s32 x, s32 y, s32 z, s32 semitrans);
/* Whether a party member stands at the cell. */
bool func_801F60E0(void);

extern Callback D_801F6218[];

extern RECT D_801F6230[];
extern u8   D_801F6248[][4];

extern Callback D_801F6258[];
extern u8       D_801F626C[];
/* The part words the box run's floor and wall quads are queued with: the tag in the high half and
 * the first tile of each face in the low. */
#define AREA135_FLOOR_PART_WORD ((0x2350u << 16) | 0x0125u)
#define AREA135_WALL_PART_WORD  ((0x2380u << 16) | 0x0126u)

/* The x and y entry coordinates the request step indexes. */
extern u8 D_801F6AAC[];
extern u8 D_801F6AAD[];
extern u8 D_801F6AB4[];
extern u8 D_801F6AB5[];
/* The x/y byte pairs the step compares the position against. */
extern u8 D_801F6B2C[];
extern u8 D_801F6B2D[];

/* One authored camera-pan row: the cell the watched actor stands on, the cell
 * the scroll moves to and the direction the actor turns. */
typedef struct Area135CameraPan {
    u8 x;         /* 0x00 */
    u8 y;         /* 0x01 */
    u8 x_half;    /* 0x02 the target x lands half a cell on */
    u8 target_x;  /* 0x03 */
    u8 y_half;    /* 0x04 */
    u8 target_y;  /* 0x05 */
    u8 direction; /* 0x06 */
} Area135CameraPan;

ASSERT_OFFSET(Area135CameraPan, target_x, 0x03);
ASSERT_OFFSET(Area135CameraPan, direction, 0x06);
ASSERT_SIZE(Area135CameraPan, 0x7);

extern Area135CameraPan D_801F6ABC[];

extern Callback D_801F6B34[];
extern Callback D_801F6B40[];
/* Sets a texture window rectangle and adds it to the area cell. */
void            func_801F3004(s32 x, s32 y, s32 width, s32 height);
void            func_801F37C4(void);
void            func_801F3830(s32 texture, s32 cell);
void            func_801F3CA8(void);
s32             func_801F5208(s32 x, s32 y);
s32             func_801F5BCC(s16 height);
u8              func_801F5C60(s32 x, s32 y);
u8              func_801F5D1C(void);
/* The overlay's companion steps the wrappers enter. */
void            func_801F5D98(void);
void            func_801F5F28(void);
s32             func_801F603C(s32 x, s32 y);

extern u8       D_801F6B3C[];
extern Callback D_801F6B48[];
extern Callback D_801F6B6C[];
extern u8       D_801F6B74[][13];

/* func_80159B9C */
/* No prototype: the retail callers pass the words unnarrowed. */
void UI_WindowDrawPanelBox();
/* func_80159FA0; no prototype, as above. */
void UI_WindowDrawBoxOutline();
/* The engine places a work row from a spawn record. */
/* The owner is src/engine/game/00/game_00.h; that header is not visible to this
 * overlay. */

extern SceneTrigger D_801F6BA8[];
/* The party spawn record Actor_SpawnPartyFromDefRow places when the area request returns. */
extern u8           D_801F6BB0[];

#endif
