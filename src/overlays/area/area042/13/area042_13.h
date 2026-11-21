#ifndef OVERLAY_WORLD01_AREA042_13_H
#define OVERLAY_WORLD01_AREA042_13_H

/* The world01/area042/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world01.h"
#include "area/spad.h"

void func_801F37A8(s32 depth, s32 color);

extern u8 D_801F2C04[];
/* One-byte views of the colour triplets in the payload table: the retail code names the second and
 * third channel by its own address. */
extern u8 D_801F52C4[];
extern u8 D_801F52C5[];
extern u8 D_801F52C6[];
extern u8 D_801F52D0[];
extern u8 D_801F52E0[];
extern u8 D_801F52E8[];

/* The cell each of the payload's eighteen quads is drawn at. */
extern AreaQuadCell D_801F52F4[];

/* The payload's eighteen quad cells, three bytes each. */
#define AREA_PAYLOAD_QUAD_COUNT 18

/* The packed part word the payload quads are queued with: the tag in the high half, the first
 * tile of the bundle's tile table in the low half. The row colour is ORed in. */
#define AREA_QUAD_PART_TAG      (0xB600u << 16)
#define AREA_QUAD_PART_TILE     0xB100u
#define AREA_QUAD_PART_WORD     (AREA_QUAD_PART_TAG | AREA_QUAD_PART_TILE)
extern u8 D_801F532C[];

void func_801F3D18(s32);

/* One bit per spawn-gate flag byte. */
extern u8  D_80144FC4[];
extern u8  D_801F5334[];
extern u8  D_801F534C[];
extern u8  D_801F5350[];
extern u8  D_801F5354[];
extern u8  D_801F5358[];
extern u16 D_801F56C4[];

/* The spawn records the event queues, 13 bytes each, one per phase. */
extern u8 D_801F56D0[];

/* The event phase the countdown picks, added to 0x5C to index the spawn-gate flags. */
extern u8 D_801F56F8;

void func_801F2DC4(void);
void func_801F2E78(s32* first, s32* second);
void func_801F30C0(s32 x, s32 y, s16 radius, u16 angle);
void func_801F3280(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2);

/* func_801F4188 */
s32  Scene_EventBegin(void);
void func_801F4B0C(s32, s32, s32, s32, s32);

#endif
