#ifndef OVERLAY_SCENARIO_SCENA04_00_H
#define OVERLAY_SCENARIO_SCENA04_00_H

/* The scenario/scena04/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"

#define SCRATCH_ROW_STRIDE 0x28
#define SCRATCH_ROW_OFFSET 0x25

/* One point of the path func_801F77EC builds in the area work memory. */
typedef struct ScenePathPoint {
    s32 x;   /* 0x00 */
    s32 y;   /* 0x04 */
    s32 z;   /* 0x08 */
    s32 pad; /* 0x0C */
} ScenePathPoint;

/* The work area: the area focus point, then the path points. */
typedef struct ScenePathWork {
    s32            x;      /* 0x00 */
    s32            y;      /* 0x04 */
    s32            z;      /* 0x08 */
    s32            unk_0C; /* 0x0C */
    ScenePathPoint points[8];
} ScenePathWork;

ASSERT_SIZE(ScenePathPoint, 0x10);
ASSERT_OFFSET(ScenePathPoint, y, 0x04);
ASSERT_OFFSET(ScenePathPoint, z, 0x08);
ASSERT_SIZE(ScenePathWork, 0x90);
ASSERT_OFFSET(ScenePathWork, points, 0x10);

extern s8  D_80144EA8;
extern u8  g_PartyFieldOrder;
extern u8  D_80144F5B;
extern u8  D_80144F5C;
extern u8  D_80144F5E;
extern u8  D_80144F5F;
extern s32 D_80146954;
extern s32 D_80146958;

extern s32 D_8014695C;

extern s32 g_AreaFocusY;

extern u32      D_801F6C00;
/* D_801FA180 */
extern Callback g_SceneEntityDispatch[];
extern Callback D_801FA198[];
extern s32      D_801FA1A4[];
extern s32      D_801FA1C4[];
void            func_80196070(void);
s8              func_801A7AD8(u8* entry, u8 count, u16 x, u16 y);
void            func_801F7084(s32* step);
void            func_801F747C(void);
void            func_801F75BC(s32 arg0, s32 arg1);

extern Callback  D_801FA1E4[];
extern Callback  D_801FA204[];
extern Callback  D_801FA210[];
extern s8        D_801FA220[];
/* D_801FA224 */
extern SceneFunc g_SceneActorDispatch[];
/* D_801FA228 */
extern u8        g_ScenePositionTable;
/* D_801FA230 */
extern Callback  g_ScenePositionDispatch[];

void func_801F7EC0();

void func_801F7FCC(void);

u8* func_801F7FF8(void);

s8 func_801F9DF4();

#endif
