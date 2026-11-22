#ifndef OVERLAY_SCENARIO_SCENA04_00_H
#define OVERLAY_SCENARIO_SCENA04_00_H

/* The scenario/scena04/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"

#define SCRATCH_ROW_STRIDE 0x28
#define SCRATCH_ROW_OFFSET 0x25

/* One 0x28-byte row of the particle table at AREA_WORK; a row is free while life is 0. */
typedef struct SceneParticle {
    VECTOR pos;      /* +0x00 */
    VECTOR velocity; /* +0x10 */
    s32    unk_20;   /* +0x20 */
    u8     unk_24;   /* +0x24 */
    u8     life;     /* +0x25 */
    u8     pad[2];   /* +0x26 */
} SceneParticle;

ASSERT_OFFSET(SceneParticle, velocity, 0x10);
ASSERT_OFFSET(SceneParticle, life, 0x25);
ASSERT_SIZE(SceneParticle, 0x28);

/* One 0x18-byte cross-section of the vertical box the scene's step draws: its corner point, a
 * spare word, then the two half extents the four corners add to the point's y and z. */
typedef struct SceneBoxEdge {
    VECTOR pos;    /* 0x00 */
    s32    half_y; /* 0x10 */
    s32    half_z; /* 0x14 */
} SceneBoxEdge;

/* The box func_801F7084 stamps the eight corners of: one cross-section at the actor's velocity
 * words and one at the actor's words from 0x24. */
typedef struct SceneBox {
    SceneBoxEdge near; /* 0x00 */
    SceneBoxEdge far;  /* 0x18 */
} SceneBox;

ASSERT_SIZE(SceneBoxEdge, 0x18);
ASSERT_OFFSET(SceneBoxEdge, half_y, 0x10);
ASSERT_OFFSET(SceneBoxEdge, half_z, 0x14);
ASSERT_SIZE(SceneBox, 0x30);
ASSERT_OFFSET(SceneBox, far, 0x18);

/* One point of the path func_801F77EC builds in the area work memory. */
typedef VECTOR ScenePathPoint;

/* The work area: the area focus point, then the path points. */
typedef struct ScenePath {
    VECTOR         focus; /* 0x00 */
    ScenePathPoint points[8];
} ScenePath;

ASSERT_SIZE(ScenePathPoint, 0x10);
ASSERT_OFFSET(ScenePathPoint, vy, 0x04);
ASSERT_OFFSET(ScenePathPoint, vz, 0x08);
ASSERT_SIZE(ScenePath, 0x90);
ASSERT_OFFSET(ScenePath, points, 0x10);
extern s8 D_80144EA8;

/* The eight 16-byte path points the scene's quad draws from: func_801F7084 stamps the box's eight
 * corners into D_801FA240 and func_801F732C draws them. */
extern ScenePathPoint D_801FA240[];

/* The five 0x20-byte segment keys func_801F75BC draws: a start and an end 16.16 point with a spare
 * word after each. func_801F747C seeds the start x through the D_801FA2C0 pointer and every other
 * word through its own absolute name; retail does the same, so a record view would not reproduce
 * the bytes (needs: scena04 owner). */
extern s32 D_801FA2C0[];
extern s32 D_801FA2C4;
extern s32 D_801FA2C8;
extern s32 D_801FA2D0;
extern s32 D_801FA2D4;
extern s32 D_801FA2D8;
extern s32 D_801FA2E4;
extern s32 D_801FA2E8;
extern s32 D_801FA2F0;
extern s32 D_801FA2F4;
extern s32 D_801FA2F8;
extern s32 D_801FA304;
extern s32 D_801FA308;
extern s32 D_801FA310;
extern s32 D_801FA314;
extern s32 D_801FA318;
extern s32 D_801FA324;
extern s32 D_801FA328;
extern s32 D_801FA330;
extern s32 D_801FA334;
extern s32 D_801FA338;
extern s32 D_801FA344;
extern s32 D_801FA348;
extern s32 D_801FA350;
extern s32 D_801FA354;

extern s32 D_801FA358;
extern u8  g_PartyFieldOrder;
extern u8  D_80144F5B;
extern u8  D_80144F5C;
extern u8  D_80144F5E;
extern u8  D_80144F5F;
/* kept: the four script-variable bytes as one word; the byte view makes a store reload the area id, and the
 * g_ScriptVarsWord global of game/script.h shifts the image. */
#define g_ScriptVarsWord (*(s32*)&g_ScriptVars)

extern u8  D_80143F1D;
/* The spawned-actor row fields func_801F817C stamps: the flag byte, the type byte, the camera
 * angle and the layer, one record each 0x74 bytes apart. */
extern u8  D_80143FC8[];
extern u8  D_80143FCD[];
extern u8  D_80143FD1[];
extern u8  D_8014402C[];
extern u8  D_80144030[];
extern u8  D_80144034[];
extern u8  D_80145FF4;
extern u8  D_80146134;
extern s32 D_80146954;
extern s32 D_80146958;
extern s32 D_8014695C;
/* The start-menu panel: its value, its request flag and its step byte. */
extern s8  D_8014865C;
extern u8  D_80148698;
extern u8  D_80148699;
extern s16 D_801492DA;

extern s16 D_801492DC;

extern s32 g_AreaFocusY;

extern u32      D_801F6C00;
/* D_801FA180 */
extern Callback D_801FA198[];
extern s32      D_801FA1A4[];
extern s32      D_801FA1C4[];
void            func_80196070(void);
void            func_801F7084(SceneBox* box);
void            func_801F732C(u8 v0, u8 v1, u8 v2, u8 v3, s32 shade0, s32 shade1);
void            func_801F747C(void);
void            func_801F75BC(u8 weight, u8 shade);
extern Callback D_801FA1E4[];

extern Callback D_801FA204[];
extern Callback D_801FA210[];
extern s8       D_801FA21C[];
extern s8       D_801FA220[];
/* D_801FA224 */
/* D_801FA228 */
extern u8       g_ScenePositions;
/* D_801FA230 */
extern Callback g_ScenePositionDispatch[];

/* The eight 16-byte path points the scene's quad draws from; func_801F7084 stamps the box's
 * eight corners into D_801FA240 and func_801F732C draws them. */
extern ScenePathPoint D_801FA240[];

void func_801F7EC0();

void func_801F7CF0(SceneParticle* particle);

void func_801F7FCC(void);

u8* func_801F7FF8(void);

s8 func_801F9DF4(s32 x, s32 y);

#endif
