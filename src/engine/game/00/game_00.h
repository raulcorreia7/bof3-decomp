#ifndef OVERLAY_ETC_GAME_00_H
#define OVERLAY_ETC_GAME_00_H

/* The etc/game/00 overlay's local declarations: the frontend state, the resource,
 * area and handler tables, and the prototypes its units share. Only this image
 * includes the file; the data tables are in data.h. */

#define GRAPHICS_PALETTE_PENDING_VOLATILE
#define GAME_REQUEST_FLAGS_VOLATILE
#include "shared/etc.h"

#include "shared.h"

#include "game/character.h"
#include "common/vector.h"
#include <string.h>

#include "data.h"
#include <stdio.h>

#define TILE_RUN_SIZE          0x8

/* Fixed retail addresses the units dereference. */
#define ENCOUNTER_TABLE_BASE   0x800E4000u /* formations and enemy records (@source: wiki:formats/area) */
#define GAME_AREA_ID_ADDR      0x80143F00  /* the u16 world id; MEM reads it non-volatile to match retail */
#define AREA_MESSAGE_REQUEST   0xD8        /* the message Message_RunAreaMessage starts */

#define SCRATCH_WORK           SP_REF(volatile Actor*, 0x44u)
#define GAME_ENTITY_COUNTER    SP_REF(s16, 0x0u)
#define GAME_ENTITY_ENTRY_DATA SP_REF(u16, 0x2u)
#define ENTITY_MAX             30
#define GAME_WORK_AREA_PTR     (*(volatile Actor**)&g_CurrentActor)

/* NOTE: retail reads the window style byte at 0x80144952 signed (`lb`) in func_8019986C and
 * func_801AEBA0 and unsigned (`lbu`) in func_801999F8 and UI_DrawWindowOutline, so exports.h keeps u8 and only
 * the signed readers view it as s8. */
#define GAME_WINDOW_STYLE      (*(s8*)&g_WindowStyle)

/* FAKE: the game images call Area_GetCellCode as s32(s16, s16) and truncate at the call; the area images pass
 * s32 coordinates untruncated, so one prototype cannot serve both (an s16 prototype changes 11 area images). */
#define AREA_CELL_CODE_S16     ((s32 (*)(s16, s16))Area_GetCellCode)
#define GAME_TILE_RUN(index)   ((TileRunSet*)g_AreaLoads[(index)])
#define g_AreaLoads            ((void**)g_AreaLoads)
#define g_RouteSpeedScale      ((u8*)g_RouteSpeedScale)

/* Start an EMI stream slot and stage the palette advance. A bare statement
 * macro: the member declares `ent` and `ev`. Kept: tested as an inline, the
 * slot argument and the member's locals change the frame and register use; the
 * do/while form moves bytes. */
#define GAME_START_STREAM_AND_STAGE_PALETTE(slot) \
    UI_SetMode(2u);                               \
    if (WINDOW_EFFECT_BUSY()) {                   \
        do {                                      \
            func_801992B8();                      \
            CallbackWait(1u);                     \
        } while (WINDOW_EFFECT_BUSY());           \
    }                                             \
    CallbackWait(1u);                             \
    CallbackWait(1u);                             \
    EMI_LoadArchive(slot);                        \
    while (EMI_IsReady() == 0) {                  \
        CallbackWait(1u);                         \
    }                                             \
    GFX_CopyPalette(1u);                          \
    GFX_CopyPalette(2u);                          \
    ent = (u16*)&g_GameEntrySubstate;             \
    ev  = *ent;                                   \
    ev += 1u;                                     \
    g_GfxPalettePending = 1u;                     \
    *ent                = ev

/* Run the scenario dispatch entry. A bare statement macro: the member declares
 * `saved` and `result`, runs its fallback when `result` is 0 and restores
 * g_Task. Kept: `entry` is a member name of the scene table record, so it
 * cannot be an argument without an indirect call; the do/while form moves
 * bytes. */
#define GAME_RUN_SCENARIO_ENTRY(entry)                                                 \
    saved  = g_Task;                                                                   \
    result = g_SceneScenes[(s32)g_SceneState.scenario_id]->entry(handler_x, handler_y)

/* Run the gated cell test and arm the work record on a hit. Kept: it returns
 * from the member and takes the flag value after a branch; tested as an inline,
 * the bytes move. */
#define GAME_ARM_WORK_ON_CELL_HIT(code, new_step)                                                                         \
    if ((g_Game.flags & 0x400) == 0) {                                                                                    \
        if ((func_801C39D8(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, code, 0) & BYTE_MASK) != 0) { \
            g_Task->header.mode = 2;                                                                                      \
            g_Task->header.step = new_step;                                                                               \
            g_Task->unk_03      = 0;                                                                                      \
            g_Task->unk_04      = 0;                                                                                      \
            return 1;                                                                                                     \
        }                                                                                                                 \
    }                                                                                                                     \
    return 0;

/* Test the map cells around a 16.16 point for the wanted code. Kept: the two
 * callee names differ per member and the body returns from the member; a callee
 * argument would be an indirect call. */
#define GAME_TEST_MAP_CELLS(flagged_test, unflagged_test, pos_x, pos_y, flag, wanted_code, mask_cells) \
    do {                                                                                               \
        u8 value;                                                                                      \
                                                                                                       \
        if (flag != 0) {                                                                               \
            value = flagged_test(pos_x, pos_y, (u8)(wanted_code & BYTE_MASK), mask_cells);             \
        } else {                                                                                       \
            value = unflagged_test(pos_x, pos_y, (u8)(wanted_code & BYTE_MASK), mask_cells);           \
        }                                                                                              \
        return value;                                                                                  \
    } while (0)

/* The work record the shared scene-timer body reads. */

typedef enum TileRunFlags {
    TILE_RUN_VERTICAL = 1 << 7,
} TileRunFlags;

/* `GameCursorState.flags` bit 7 marks a cursor still moving between cells. */
typedef enum GameCursorFlags {
    GAME_CURSOR_FLAG_MOVING = 1 << 7,
} GameCursorFlags;

typedef struct GameResetRecord {
    u8  unk_00;
    u8  unk_01;
    u8  unk_02;
    u8  unk_03;
    u8  unk_04;
    u8  unk_05;
    u8  unk_06;
    u8  unk_07;
    u8  unk_08[2];
    s16 unk_0A;
} GameResetRecord;

typedef struct {
    u8  cx;    /* 0x00 */
    u8  cy;    /* 0x01 */
    u16 key;   /* 0x02 */
    u16 index; /* 0x04 */
    u16 alt;   /* 0x06 */
    u8  mode;  /* 0x08 */
    u8  span;  /* 0x09 */
    u8  kind;  /* 0x0A */
    u8  pad;   /* 0x0B */
} GameLocale;

ASSERT_SIZE(GameLocale, 0x0C);

typedef struct {
    u8          pad_00[0x20]; /* 0x00-0x1F */
    GameLocale* entries;      /* 0x20 */
    u32*        keys;         /* 0x24 */
    u8*         counts;       /* 0x28 */
    u8          pad_2C[4];    /* 0x2C-0x2F */
    u8          outer;        /* 0x30 */
} GameLocaleBank;

typedef struct TileRun {
    u8 x;
    u8 y;
    u8 flags; /* TileRunFlags */
    u8 len;
    u8 unk_04[4];
} TileRun;

ASSERT_SIZE(TileRun, TILE_RUN_SIZE);

typedef struct TileRunSet {
    u8       pad_00[0x2C];
    TileRun* runs; /* 0x2C */
    u8       pad_30;
    u8       last_run; /* 0x31 */
} TileRunSet;

ASSERT_OFFSET(TileRunSet, runs, 0x2C);
ASSERT_OFFSET(TileRunSet, last_run, 0x31);

/* A field search spot: a one-time random zenny find, flagged in the actor so it pays once. The
 * Alt table differs only in the reaction effect its roll starts. */
typedef enum FieldSearchSpotState {
    FIELD_SEARCH_SPOT_STATE_ROLL,
    FIELD_SEARCH_SPOT_STATE_SMALL_FIND,
    FIELD_SEARCH_SPOT_STATE_LARGE_FIND,
    FIELD_SEARCH_SPOT_STATE_EMPTY,
    FIELD_SEARCH_SPOT_STATE_MESSAGE,
    FIELD_SEARCH_SPOT_STATE_COUNT
} FieldSearchSpotState;

typedef struct FieldSearchSpotStates {
    Callback states[FIELD_SEARCH_SPOT_STATE_COUNT];
} FieldSearchSpotStates;

typedef struct FieldSearchSpotAltStates {
    Callback states[FIELD_SEARCH_SPOT_STATE_COUNT];
} FieldSearchSpotAltStates;

/* The variant that fades the actor's tint back after the find. */
typedef enum FieldSearchSpotFadeState {
    FIELD_SEARCH_SPOT_FADE_STATE_ROLL,
    FIELD_SEARCH_SPOT_FADE_STATE_EMPTY,
    FIELD_SEARCH_SPOT_FADE_STATE_SMALL_FIND,
    FIELD_SEARCH_SPOT_FADE_STATE_LARGE_FIND,
    FIELD_SEARCH_SPOT_FADE_STATE_MESSAGE,
    FIELD_SEARCH_SPOT_FADE_STATE_FADE,
    FIELD_SEARCH_SPOT_FADE_STATE_COUNT
} FieldSearchSpotFadeState;

typedef struct FieldSearchSpotFadeStates {
    Callback states[FIELD_SEARCH_SPOT_FADE_STATE_COUNT];
} FieldSearchSpotFadeStates;

/* A spinning quad at 0x800E4800 + n * 0x38: a centre, a random rotation and four corner offsets that
 * func_8019D8C0 rotates and writes out as screen vertices. */
typedef struct SpinQuad {
    Point3D pos;
    u8      unk_06[0x0A];
    SVECTOR rotation; /* 0x10 */
    SVECTOR corners[4];
} SpinQuad;

ASSERT_OFFSET(SpinQuad, rotation, 0x10);
ASSERT_OFFSET(SpinQuad, corners, 0x18);
ASSERT_SIZE(SpinQuad, 0x38);

/* Per-slot column views over the 0x98-byte work records: the trailing padding
 * carries the record stride so each column keeps its own field base. */
typedef struct GameSlotWordColumn {
    u16 value;
    u8  pad[0x96];
} GameSlotWordColumn;

ASSERT_SIZE(GameSlotWordColumn, ACTOR_SIZE);

typedef struct GameSlotByteColumn {
    u8 value;
    u8 pad[0x97];
} GameSlotByteColumn;

ASSERT_SIZE(GameSlotByteColumn, ACTOR_SIZE);

/* Route step handler: advances one script cursor and reports a byte result. */
typedef s32 (*TailFunc)(u8* pc);

typedef struct GameSlots {
    u8 cells[9];
} GameSlots;

typedef struct GameMenuSlot {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} GameMenuSlot;

typedef struct GameMenuSlots {
    GameMenuSlot entries[9];
} GameMenuSlots;

typedef struct GameSeed {
    u16 cells[4];
} GameSeed;

typedef struct GameCursorState {
    u8  flags; /* GameCursorFlags */
    u8  pad_01[2];
    u8  unk_03;
    u8  unk_04;
    u8  pad_05[2];
    u8  unk_07;
    u8  pad_08[2];
    u16 index_0A;
} GameCursorState;

ASSERT_OFFSET(GameCursorState, unk_04, 0x04);
ASSERT_SIZE(GameCursorState, 0x0C);

extern u16                       D_1F800002; /* 0x1F800002; packed spawn record staging halfword */
extern u8                        D_1F800003;
extern u16                       D_1F800004; /* 0x1F800004 */
extern s16                       D_1F800008; /* 0x1F800008 */
extern u16                       D_1F80000A; /* 0x1F80000A */
extern s16                       D_1F80000C; /* 0x1F80000C */
extern u16                       D_1F80000E; /* 0x1F80000E */
extern s8                        D_800E4D40; /* 0x800E4D40 */
extern s16                       D_800E4D42; /* 0x800E4D42 */
extern u8                        D_80143BB1;
extern volatile u16              g_GameAreaId;
extern volatile u8               D_80143F06; /* 0x80143F06 */
extern volatile u32              D_80143F08; /* 0x80143F08 */
extern volatile u32              D_80143F0C; /* 0x80143F0C */
extern s16                       D_80143F16; /* 0x80143F16; signed high halfword of the context bundle */
extern s16                       D_80143F1A; /* 0x80143F1A */
extern volatile u8               g_GameRequestKind;
extern s16                       D_80143F26; /* integer half of g_EncounterOriginX */
extern s16                       D_80143F2A; /* integer half of g_EncounterOriginY */
/* Scene step byte, countdown halfword and the slot index cached in the
 * scratchpad byte at 0x1F800000. The read-modify-write sites go through a
 * pointer, which is the shape this target's exact siblings use; plain stores
 * keep the scalar spelling.
 */
extern u8                        D_80143F49;
extern volatile u8               D_80143F4A;
extern volatile u8               D_80143F4B; /* 0x80143F4B */
extern s8                        D_80143F4E; /* 0x80143F4E */
extern u8                        D_80143F51;
extern s32                       D_80143F5C;
extern s32                       D_80143F84;
extern s16                       g_ScrollHeight;
extern u8                        D_80143FBC;
extern u8                        D_80143FBD;
extern u8                        D_80143FBF;
extern u8                        D_80143FC1;
extern u8                        D_80143FC3;
extern s8                        D_801448E8; /* 0x801448E8 */
extern s16                       D_801448EE; /* 0x801448EE */
extern s16                       D_801448F0; /* 0x801448F0 */
extern u8                        D_80144EE2;
extern u8                        D_80144F5E[]; /* 0x80144F5E */
extern u8                        D_80144FC4[]; /* 0x80144FC4; per-slot spawn-gate flag bytes */
extern u8                        D_80145004[]; /* 0x80145004 */
extern s32                       D_8014503C;   /* 0x8014503C */
extern s8                        D_8014504B;   /* 0x8014504B */
extern u8                        D_801457AB;
extern u8                        D_80145E9B;
extern u16                       D_80145EBC; /* 0x80145EBC */
extern u32                       D_80145EDC; /* 0x80145EDC */
extern u8                        D_80145F00; /* 0x80145F00 */
extern u8                        D_80145FB4[];
extern u16                       D_80145FB8; /* 0x80145FB8 */
extern u8                        D_80145FD1;
extern u8                        D_80145FD6;
extern u8                        D_80145FDB;
extern u8                        D_80146111;
extern u8                        D_80146119;
extern u8                        D_8014611B;
extern s32                       D_8014611C;
extern s32                       D_80146120;
extern s32                       D_80146144;
extern s32                       D_80146148;
extern volatile u8               D_80146256;
extern u8                        D_80146260;
extern u8                        D_80146261;
extern u8                        D_80146262;
extern s32                       D_80146264; /* 0x80146264 */
extern s16                       D_80146266; /* 0x80146266 */
extern s32                       D_80146268; /* 0x80146268 */
extern s16                       D_8014626A; /* 0x8014626A */
extern u8                        D_8014626C;
extern u8                        D_8014626E;
extern u8                        D_8014626F;
extern u8                        D_80146270;
extern u8                        D_80146855;
extern u8                        D_80146856;
extern u16                       D_80146878;
extern u8                        D_8014688F;
extern u8                        D_80146893[]; /* 0x80146893 */
extern GameSlotByteColumn        D_801468B1[];
extern GameSlotWordColumn        D_801468B6[];
extern GameSlotWordColumn        D_801468B8[];
extern u8                        D_801468BE[]; /* 0x801468BE */
extern u8                        D_801468C2[]; /* 0x801468C2 */
extern s32                       D_801468C4;
/* FAKE: column views of g_Actors for the spawn functions (+0x77 unk_77, +0x78 unk_78, +0x8C ext, +0x94 unk_94).
 * The member form shares one slot offset between the stores and shortens each function by 0x34 bytes. */
extern u8                        D_801468FF;
extern u8                        D_80146900[ENTITY_MAX][ACTOR_SIZE]; /* 0x80146900 */
/* FAKE: column views of g_Actors for func_801A65A0 and func_801A68C0, the only forms that match them. */
extern u16                       D_80146904[ENTITY_MAX][ACTOR_SIZE / 2];       /* Actor.unk_7C */
extern s32                       g_ActorWalkDestX[ENTITY_MAX][ACTOR_SIZE / 4]; /* Actor.walk_dest_x */
extern s32                       g_ActorWalkDestY[ENTITY_MAX][ACTOR_SIZE / 4]; /* Actor.walk_dest_y */
extern s32                       D_80146910[ENTITY_MAX][ACTOR_SIZE / 4];       /* Actor.unk_88 */
extern u16                       D_80146914;
extern u16                       D_80146918[][ACTOR_SIZE / 2];
extern u8                        D_8014691C[ENTITY_MAX][ACTOR_SIZE]; /* 0x8014691C */
extern Actor                     D_80147A58[];
extern u8                        D_80147CB8[]; /* 0x80147CB8 */
extern s8                        D_80147CB9[]; /* 0x80147CB9 */
extern s8                        D_80147CBA[]; /* 0x80147CBA */
extern u8                        D_80147CBB[]; /* 0x80147CBB */
extern s32                       D_80147CBC[];
extern s32                       D_80147CC0[];
extern s32                       D_80147CC4[];
extern u16                       D_801481D8;
extern Point3DL                  D_801481E8;   /* scene angle, 16.16 fixed point */
extern Point3DL                  D_801481F8;   /* per-frame step of D_801481E8 */
extern s16                       D_8014820C;   /* 0x8014820C */
extern s8                        D_80148654;   /* 0x80148654 */
extern s8                        D_80148656;   /* 0x80148656 */
extern s8                        D_801490E0;   /* 0x801490E0 */
extern u8                        D_801581E0[]; /* 0x801581E0 */
extern u8*                       g_EncounterZones[];
extern Point2DL                  g_FacingOffsets[]; /* 0x80181AC0 */
extern s8                        D_80181B00[];
extern s8                        D_80181B01[];
extern u8                        D_80181B1C[];   /* 0x80181B1C */
extern u8                        D_80181B28[];   /* 0x80181B28 */
extern s16                       D_80181B70[];   /* 0x80181B70 */
extern u32                       D_80181CA8[60]; /* 0x80181CA8 - the 60-word table the exe defines at src/engine/slus/data_80181CA8.c */
extern s32                       D_80181CAC;
extern u8                        D_80181E40[];          /* 0x80181E40 */
extern u8                        D_80181E44[];          /* 0x80181E44 */
extern u8                        D_8018214C[];          /* 0x8018214C */
extern u8                        s_ScriptCopyBlock[16]; /* 0x8018216C */
/* D_8018217C */
extern u8                        g_AreaScriptTests; /* 0x8018217C */
extern TailFunc                  D_801821C0[];
extern u8                        D_8018E268[];
extern char                      D_80195858[]; /* 0x80195858 */
extern char                      D_80195860[]; /* 0x80195860 */
extern FieldSearchSpotStates     D_80195ED4;   /* 0x80195ED4 */
extern char                      D_80195F0C[]; /* 0x80195F0C */
extern FieldSearchSpotAltStates  D_80195F10;   /* 0x80195F10 */
extern FieldSearchSpotFadeStates D_80195F44;   /* 0x80195F44 */
extern char                      D_80195F90[];
extern char                      D_80195F98[]; /* 0x80195F98 */
extern char                      D_80195FBC[]; /* 0x80195FBC */
extern GameSlots                 D_80195FEC;
extern GameMenuSlots             D_80195FF8;
extern GameSeed                  D_80196014;
extern u8                        D_801F1294; /* 0x801F1294 */
extern u8                        D_801F12C8; /* 0x801F12C8 */
extern u8                        D_801F1318; /* 0x801F1318 */
extern u8                        D_801F13B8; /* 0x801F13B8 */
extern u8                        D_801F1444; /* 0x801F1444 */
extern u8                        D_801F1484; /* 0x801F1484 */
extern u8                        D_801F14C4; /* 0x801F14C4 */
extern u8                        D_801F14F8; /* 0x801F14F8 */
extern u8                        D_801F1538; /* 0x801F1538 */
extern u8                        D_801F1578; /* 0x801F1578 */
extern u8                        D_801F15B8; /* 0x801F15B8 */
extern u8                        D_801F15F8; /* 0x801F15F8 */
extern u8                        D_801F2C68; /* 0x801F2C68 */
extern u8                        D_801F2D28; /* 0x801F2D28 */
extern u8                        D_801F2D38; /* 0x801F2D38 */
extern u8                        D_801F2D48; /* 0x801F2D48 */
extern u8                        D_801F2D50; /* 0x801F2D50 */
extern u8                        D_801F2D70; /* 0x801F2D70 */
extern u8                        D_801F2DA0; /* 0x801F2DA0 */
extern u8                        D_801F2DA8; /* 0x801F2DA8 */
extern u8                        D_801F2DC4; /* 0x801F2DC4 */
extern u8                        D_801F2DE0; /* 0x801F2DE0 */
extern u8                        D_801F2E68; /* 0x801F2E68 */
extern u8                        D_801F2E94; /* 0x801F2E94 */
extern u8                        D_801F2F08; /* 0x801F2F08 */
extern u8                        D_801F2F34; /* 0x801F2F34 */
extern u8                        D_801F3140; /* 0x801F3140 */
extern u8                        D_801F3184; /* 0x801F3184 */
extern u8                        D_801F346C; /* 0x801F346C */
extern u8                        D_801F35BC; /* 0x801F35BC */
extern u8                        D_801F3A34; /* 0x801F3A34 */
extern u8                        D_801F3AA4; /* 0x801F3AA4 */
extern u8                        D_801F3ADC; /* 0x801F3ADC */
extern u8                        D_801F3B20; /* 0x801F3B20 */
extern u8                        D_801F3B9C; /* 0x801F3B9C */
extern u8                        D_801F3BEC; /* 0x801F3BEC */
extern u8                        D_801F3C9C; /* 0x801F3C9C */
extern u8                        D_801F3E00; /* 0x801F3E00 */
extern u8                        D_801F3F24; /* 0x801F3F24 */
extern u8                        D_801F3F48; /* 0x801F3F48 */
extern u8                        D_801F3F70; /* 0x801F3F70 */
extern u8                        D_801F3FF4; /* 0x801F3FF4 */
extern u8                        D_801F4168; /* 0x801F4168 */
extern u8                        D_801F4230; /* 0x801F4230 */
extern u8                        D_801F4250; /* 0x801F4250 */
extern u8                        D_801F4288; /* 0x801F4288 */
extern u8                        D_801F439C; /* 0x801F439C */
extern u8                        D_801F4594; /* 0x801F4594 */
extern u8                        D_801F45E4; /* 0x801F45E4 */
extern u8                        D_801F4674; /* 0x801F4674 */
extern u8                        D_801F4C48; /* 0x801F4C48 */
extern u8                        D_801F4CC8; /* 0x801F4CC8 */
extern u8                        D_801F4D04; /* 0x801F4D04 */
extern u8                        D_801F4D90; /* 0x801F4D90 */
extern u8                        D_801F4DA0; /* 0x801F4DA0 */
extern u8                        D_801F4DA4; /* 0x801F4DA4 */
extern u8                        D_801F4DD4; /* 0x801F4DD4 */
extern u8                        D_801F4DE0; /* 0x801F4DE0 */
extern u8                        D_801F5698; /* 0x801F5698 */
extern u8                        D_801F56E0; /* 0x801F56E0 */
extern u8                        D_801F5708; /* 0x801F5708 */
extern u8                        D_801F58F4; /* 0x801F58F4 */
extern u8                        D_801F591C; /* 0x801F591C */
extern u8                        D_801F599C; /* 0x801F599C */
extern u8                        D_801F5EBC; /* 0x801F5EBC */
extern u8                        D_801F64E8; /* 0x801F64E8 */
extern u8                        D_801F6D58; /* 0x801F6D58 */
extern u8                        D_801F6D80; /* 0x801F6D80 */
extern u8                        D_801F6D84; /* 0x801F6D84 */
extern u8                        D_801F6DBC; /* 0x801F6DBC */
extern u8                        D_801F6DE4; /* 0x801F6DE4 */
extern u8                        D_801F6DE8; /* 0x801F6DE8 */
extern u8                        D_801F8538; /* 0x801F8538 */
extern u8                        D_801F8570; /* 0x801F8570 */
extern u8                        D_801F8574; /* 0x801F8574 */
extern u8                        D_801F9728; /* 0x801F9728 */
extern u8                        D_801F9DC8; /* 0x801F9DC8 */
extern u8                        D_801F9DCC; /* 0x801F9DCC */
extern u8                        D_801FA1F0; /* 0x801FA1F0 */
extern u8                        D_801FA234; /* 0x801FA234 */
extern u8                        D_801FA23C; /* 0x801FA23C */
extern u8                        D_801FAEDC; /* 0x801FAEDC */
extern u8                        D_801FAF60; /* 0x801FAF60 */
extern u8                        D_801FAF84; /* 0x801FAF84 */
extern u8                        D_801FBF34; /* 0x801FBF34 */
extern u8                        D_801FBFC8; /* 0x801FBFC8 */
extern u8                        D_801FBFE8; /* 0x801FBFE8 */
extern u8                        D_801FC404; /* 0x801FC404 */
extern u8                        D_801FC488; /* 0x801FC488 */
extern u8                        D_801FC4BC; /* 0x801FC4BC */
extern u8                        D_801FC9FC; /* 0x801FC9FC */
extern u8                        D_801FCA88; /* 0x801FCA88 */
extern u8                        D_801FCFC0; /* 0x801FCFC0 */
extern u8                        D_801FD03C; /* 0x801FD03C */
extern u8                        D_801FD044; /* 0x801FD044 */
extern u8                        D_801FD1A4; /* 0x801FD1A4 */
extern u8                        D_801FD24C; /* 0x801FD24C */
extern u8                        D_801FD274; /* 0x801FD274 */
extern u8                        D_801FD5C8; /* 0x801FD5C8 */
extern u8                        D_801FD67C; /* 0x801FD67C */
extern u8                        D_801FD6A8; /* 0x801FD6A8 */
extern u8                        D_801FDDFC; /* 0x801FDDFC */
extern u8                        D_801FDFAC; /* 0x801FDFAC */
extern u8                        D_801FDFB4; /* 0x801FDFB4 */
extern u8                        D_801FE274; /* 0x801FE274 */
extern u8                        D_801FE288; /* 0x801FE288 */
extern u8                        D_801FE364; /* 0x801FE364 */
extern u8                        D_801FE370; /* 0x801FE370 */
extern u8                        D_801FE374; /* 0x801FE374 */
extern u8                        D_801FE3C4; /* 0x801FE3C4 */
extern u8                        D_801FE3CC; /* 0x801FE3CC */
extern u8                        D_801FE49C; /* 0x801FE49C */
extern u8                        D_801FE4C4; /* 0x801FE4C4 */
extern u8                        D_801FE4F4; /* 0x801FE4F4 */
extern u8                        D_801FE52C; /* 0x801FE52C */
extern u8                        D_801FE5F4; /* 0x801FE5F4 */
extern u8                        D_801FE724; /* 0x801FE724 */
extern u8                        D_801FE734; /* 0x801FE734 */
extern u8                        D_801FE880; /* 0x801FE880 */
extern u8                        D_801FE950; /* 0x801FE950 */
extern u8                        D_801FE9B0; /* 0x801FE9B0 */
extern u8                        D_801FE9C8; /* 0x801FE9C8 */
extern u8                        D_801FE9CC; /* 0x801FE9CC */
extern u8                        D_801FE9E8; /* 0x801FE9E8 */

void func_80117004(void);
void func_80117610(void);
void func_80117A30(void);
void func_80117BF4(void);
void Actor_BeginScript(u8 raw_selector, u8 raw_code);
void Area_ClearCell(s32 x, s32 y);
void func_8015A7E8(void);
s32  func_8015B870(u8 value);
void Party_ShowBattlers(void);
s8   Actor_RunHandler(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags);
s32  func_8015CC00(s32 id, s32 step, s32 selection, s32 x, s32 y, s32 z);
void func_8015D820(u16 cue_id, u8 index);
void func_80164020(u32 arg0, u32 arg1);
bool Item_Add(s32 category, u8 item, u8 amount, s32 unused);
s32  Item_Count(u8 category, u8 item, u8 mode);
u8   Char_GetAbilityCost(u8 character_index, u8 ability_kind, u8 mode);
void Party_ResetBattlers(void);
void Party_ClearActiveBattlers(void);
void func_80167910(void);

void    func_80167E00(void);
void    GFX_CopyPaletteAnimationColors(GraphicsPaletteAnimation* slot);
void    Game_UpdateAreaLoad(void);
void    Game_UpdateField(void);
void    Game_UpdateMenu(void);
void    Game_LoadMenuOverlay(void);
void    Game_ReturnFromMenu(void);
void    func_801979D4(void);
void    Game_UpdateBattle(void);
void    func_80197A60(void);
void    Battle_LoadPartySprites(void);
void    func_80197C1C(void);
void    Battle_LoadBattleArchive(void);
void    func_80197E54(void);
void    func_80197EFC(void);
void    func_80197F48(void);
void    Game_UpdateCameraLook(void);
void    func_801981B4(void);
/* func_801981D4 */
void    Game_FinishCameraLook(void);
void    Game_UpdateShop(void);
void    Game_LoadShopOverlay(void);
void    Game_ReturnFromShop(void);
void    Game_UpdateFishing(void);
void    func_801984E8(void);
void    func_801985C8(void);
void    Game_UpdateAbilityMenu(void);
void    Game_LoadAbilityMenu(void);
void    Game_ReturnFromAbilityMenu(void);
void    Game_UpdateStatusMenu(void);
void    Game_LoadStatusMenu(void);
void    Game_ReturnFromStatusMenu(void);
void    Game_UpdateSceneCamera(void);
void    func_80198B00(void);
void    func_80198B44(void);
void    func_80198B6C(void);
void    func_80198BC4(u32 wait_steps);
void    func_80198C38(u8 wait_steps);
/* func_80198CAC */
void    Game_UpdateClock(void);
void    func_80198F1C(void);
void    func_801990D0(void);
void    Area_RunFrame(void);
void    func_80199230(void);
void    func_801992B8(void);
void    func_80199308(void);
/* func_80199368 */
void    Game_UpdateMenuFrame(void);
void    func_80199398(void);
/* func_801993F0 */
void    Game_UpdateAbilityMenuFrame(void);
/* func_80199418 */
void    Game_UpdateStatusMenuFrame(void);
void    func_8019959C(void);
void    func_801995A4(void);
void    func_801995F8(void);
void    func_80199638(void);
void    func_801996A8(void);
void    func_801996FC(void);
void    func_8019977C(void);
void    func_801997EC(void);
void    func_8019982C(void);
void    func_8019986C(void);
void    func_80199938(void);
void    func_80199978(void);
void    func_801999B8(void);
void    func_801999F8(MenuPanelTask* task);
/* func_8019A1D4 */
u8*     Game_GetAreaMapPoints(void);
void    func_8019A210(void);
void    func_8019A258(void);
void    func_8019A2A0(void);
void    func_8019A2E8(void);
void    func_8019A330(void);
void    func_8019A370(void);
void    func_8019A3B8(void);
void    func_8019A3FC(void);
void    func_8019A53C(void);
void    func_8019A580(void);
void    func_8019A630(void);
void    func_8019A6AC(void);
void    func_8019A7D4(void);
void    func_8019A804(void);
void    func_8019A848(void);
void    func_8019A8B4(void);
void    func_8019A904(void);
void    func_8019AA44(void);
void    func_8019AAFC(void);
void    func_8019AB5C(void);
void    func_8019AC34(void);
void    func_8019AC84(void);
void    func_8019ACF4(void);
void    func_8019AD70(void);
void    func_8019ADA4(void);
void    func_8019ADE8(void);
void    func_8019AF1C(void);
void    func_8019B024(void);
void    func_8019B0EC(void);
void    func_8019B10C(void);
void    func_8019B150(void);
void    func_8019B1E8(void);
void    func_8019B284(void);
void    func_8019B364(void);
void    func_8019B3A8(void);
void    func_8019B4A0(void);
void    func_8019B704(void);
void    func_8019BBA4(void);
void    func_8019BE28(void);
void    func_8019BEFC(void);
void    func_8019BF78(void);
void    func_8019BFD4(void);
bool    func_8019C028(void);
void    func_8019C124(s32 step_byte);
s32     func_8019C1E4(void);
s32     func_8019C344(s32 x, s32 y);
s32     func_8019C4F0();
void    func_8019C620(void);
void    func_8019C664(void);
void    func_8019C794(void);
void    func_8019C910(void);
void    func_8019C954(void);
u8      func_8019CAB4(void);
void    func_8019CB94(void);
void    func_8019CBD8(void);
void    func_8019CCB8(void);
void    func_8019CEDC(void);
void    func_8019CFCC(void);
bool    func_8019D054(s32 point_x, s32 point_y);
s32     func_8019D20C(s16 map_x, s16 map_y);
void    func_8019D270(void);
void    func_8019D4BC(void);
void    func_8019D648(void);
void    func_8019D800(void);
void    func_8019D8C0(SpinQuad* quad, s16* out);
void    func_8019D9C0(void);
s32     func_8019DAA0(s32* spawn_record, s16 spawn_offset, u8 spawn_count);
void    func_8019DC6C(void);
void    func_8019DDCC(void);
void    func_8019DE10(void);
void    func_8019DE54(void);
void    func_8019DF8C(void);
void    func_8019DFB4(void);
void    func_8019E1A0(void);
void    func_8019E264(void);
void    func_8019E2A8(void);
void    func_8019E36C(void);
void    func_8019E424(void);
void    func_8019E468(void);
void    func_8019E4A8(void);
void    func_8019E5D4(void);
void    func_8019E6F8(void);
void    func_8019E780(void);
void    func_8019E7C4(void);
void    func_8019E884(void);
void    func_8019E918(void);
void    func_8019E95C(void);
void    func_8019EA60(void);
void    func_8019EAD4(void);
void    func_8019EAF4(void);
void    func_8019EB38(void);
void    func_8019EC20(void);
void    func_8019ED40(void);
void    func_8019EE10(void);
u8      func_8019EEE4(void);
void    func_8019F2CC(void);
void    func_8019F310(void);
void    func_8019F384(void);
void    func_8019F430(void);
void    func_8019F4F8(void);
void    func_8019F5B8(s16 x, s16 y, u8 unused, u8 palette);
void    func_8019F840(void);
void    func_8019F98C(void);
void    func_8019F9D0(void);
void    func_8019FAA0(u16 area_id, u32 entry_x, u32 entry_y, u8 entry_facing);
void    func_8019FF88(s32 entry_mode, s32 entry_index, s32 entry_flags);
void    func_801A02E8(void);
u8      func_801A0348(s16 map_x, s16 map_y);
void    func_801A0380(s16 x, s16 y, u16 kind);
u8*     func_801A0490(s32 map_x, s32 map_y, s32 table_index);
u32     func_801A06D8(void);
void    func_801A0AE4(Actor* record);
void    func_801A0CFC(Actor* entity);
void    func_801A0F24(Actor* record);
void    func_801A114C(Actor* record);
void    func_801A1384(void* entity);
s32     func_801A17A0(u8* entry_record);
void    func_801A1A24(u8* record);
bool    func_801A1A58(Actor* actor);
s32     func_801A1BC0(Actor* record);
s32     func_801A1C5C(s32 x, s32 y, s32 route, s32 unused);
s32     func_801A1ED8(s32 x, s32 y, s32 route, s32 unused);
s32     func_801A21EC(s32 x, s32 y);
s32     func_801A223C(s32 x, s32 y);
s32     func_801A225C(s32 unused, s32 divisor, s32 flag_bits);
s32     func_801A22CC(Actor* value_a, s32 value_b, u8 flag_bits);
s32     func_801A239C(Actor* value_a, s32 value_b, u8 flag_bits);
s32     func_801A246C(s32 value_a, s32 value_b, s32 flag_bits);
void    func_801A253C(Actor* entity);
void    func_801A271C(void* record);
/* Kept (): retail callers load $a0 in the jal delay slot (`addiu a0,s0,116`) and the callee never reads it; with (void)
 * that instruction is dropped (func_801A253C) or the frame shrinks by 8 bytes (func_801A1384). */
void    func_801A275C(void* unused);
void    func_801A2788(s32 handler_index);
void    func_801A27C4(Actor* entity);
u8      func_801A2A04(Actor* entity);
void    func_801A2AE4(Actor* entity, u8 route_flag);
u8      func_801A2C10(void* record);
u8      func_801A2C94(Actor* actor);
u8      func_801A2DB4(Actor* entity);
u8      func_801A2ED4(Actor* entity, u8 route_step);
void    func_801A3080(Actor* actor, s32 facing);
void    func_801A3410(void* work_index);
void    func_801A3594(void);
/* func_801A35D8 */
void    Game_StartFadeWhite(void);
void    func_801A3648(void);
void    func_801A37D4(void);
/* func_801A3818 */
void    Game_StartFadeBlack(void);
void    func_801A386C(void);
bool    func_801A3AC8(Actor* record);
void    func_801A3B7C(Actor* entity);
void    func_801A3F3C(u8* script);
void    func_801A3FC0(u8* cursor);
void    func_801A4158(u8* cursor);
u8*     func_801A42F0(u8* cursor, s8* flag, u8* counter);
u8*     func_801A4374(u8* cursor, s8* flag, u8* counter);
u8*     func_801A4400(u8* script);
u8*     func_801A44A4(u8* script);
u8*     func_801A4518(u8* script);
u8*     func_801A4640(u8* cursor);
u8*     func_801A46E8(u8* cursor);
u8*     func_801A4798(u8* script);
u8*     func_801A4844(u8* script);
void    func_801A4914(void);
void    func_801A4990(u8* script);
void    func_801A4AA8(void);
void    func_801A4B80(s32 index);
u8*     func_801A4BF8(u8* script);
void    func_801A50C0(u8* script);
void    func_801A5400(u8* script);
void    func_801A57F0(u8* script);
void    func_801A5B78(u8* script);
void    func_801A5EFC(u8* script);
void    func_801A623C(u8* script);
void    func_801A65A0(u8* script);
void    func_801A68C0(u8* script);
void    func_801A6C98(u8* record);
void    func_801A6F58(u8* script);
void    func_801A72B0(void* packed_selector);
void    func_801A72E8(void* selector);
s8      Area_IsStepBlocked(s32 handler_x, s32 handler_y);
s8      func_801A79A4(s32 handler_x, s32 handler_y);
void    func_801A7CE8(void);
void    Menu_OpenMaster(void);
void    Message_RunAreaMessage(void);
void    func_801A7E54(void);
void    Scene_StartShopSave(void);
void    func_801A839C(void);
void    func_801A83DC(void);
void    func_801A852C(void);
s32     func_801A8714(void);
s8      func_801A8728(s32 entry_x, s32 entry_y);
bool    func_801A8A98(s32 candidate_x, s32 candidate_y);
s8      func_801A8B84(s32 handler_x, s32 handler_y);
/* func_801A8CB4 */
s8      Game_CallAreaHandler(s32 handler_x, s32 handler_y);
u8      func_801A8D38(void* sub, s32 target);
u8      func_801A8F94(ScriptState* state, u8* base, s32 seed);
void    func_801A96E4(ScriptState* state, u8* base);
u8      func_801A9944(void* sub, s32 target, u8 value);
u8      func_801A9DE8(GameCursorState* state, const u8* table, u8 value);
u8      func_801AA470(void* sub, s32 target, u8 value);
u8      func_801AAB00(void* sub, s32 target, u8 value);
u8      func_801AB458(GameCursorState* state, const u8* table, u8 value);
s32     func_801AB8B0(GameCursorState* state, u8* table, s32 value);
u8      func_801ABA24(void* sub, s32 target, u8 value);
u8      func_801ABD68(s32 pos_x, s32 pos_y, s32 step_count, void* deltas);
void    func_801ABEE0(void);
VECTOR* func_801ABF30(VECTOR* out, s32 sel, s32 selector_kind);
void    func_801AC0A0(s8 tuning_delta);
bool    func_801AC33C(s32 ease_in, s32 distance);
void    func_801AC768(GameCursorState* cursor_state, s32 mode_byte, s32 value_18, s32 value_1C, s32 extra_value);
u16     func_801AC8F0(ScriptState* state, u8 wanted_id, u8* base);
void    func_801AC9D0(void);
void    func_801ACA14(void);
void    func_801ACAC0(void);
void    func_801ACBC4(void);
void    func_801ACC08(void);
void    func_801ACCD8(void);
void    func_801ACE10(s32 handler_index);
void    func_801ACEBC(void);
void    func_801ACF2C(void);
void    func_801AD0EC(void);
void    func_801AD184(void);
void    func_801AD218(void);
void    func_801AD2CC(void);
void    func_801AD35C(void);
void    func_801AD3B4(void);
void    func_801AD44C(void);
void    func_801AD46C(void);
void    func_801AD4DC(void);
void    func_801AD69C(void);
void    func_801AD6BC(void);
void    func_801AD734(void);
void    func_801AD90C(void);
void    func_801AD9C4(void);
void    func_801AD9F0(void);
void    func_801ADAC0(s8 actor_slot);
s8      func_801ADC98(void);
void    func_801ADCF4(u8 actor_slot);
void    GFX_DrawLine(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b, s32 blend);
/* func_801AF270 */
u8*     UI_GetSpriteRect(u8 sprite_id, u8 flags);
void    UI_DrawSpriteRun(s16 base_x, s16 base_y, const u8* record_table, u8 flags);
bool    func_801AF494(u8 test, u8 character_id, u8 category, u8 item_id);
void    func_801AF800(s16 record_x, s32 record_y, u8 text_shade, u8 category, s32 item_id, s32 quantity, s32 sprite_flag);

void  func_801AFA1C(u8* arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);
void  func_801B00F8(void);
void  func_801B016C(void);
void  func_801B0320(void);
void  func_801B036C(void);
void  func_801B0568(void);
void  func_801B0C88(void);
void  func_801B0DA0(void);
void  func_801B13BC(void);
void  func_801B146C(void);
/* func_801B1AE8 */
void  Game_RunLeaderSwitch(void);
void  func_801B1E24(void);
void  func_801B207C(void);
void  func_801B21E8(void);
void  func_801B26E0(void);
/* func_801B2950 */
void  Game_EndLeaderSwitch(void);
void  func_801B29BC(void);
void  func_801B2A00(void);
void  func_801B2A20(void);
void  func_801B2A70(void);
void  func_801B2AB4(void);
void  func_801B2B6C(void);
void  func_801B2C38(void);
void  func_801B2D90(void);
void  func_801B2DDC(void);
void  func_801B2FC8(void);
void  func_801B315C(void);
void  func_801B31F0(void);
/* func_801B3260 */
void  Area_Climb(void);
void  func_801B32A4(void);
/* func_801B32D0 */
void  Area_ClimbMount(void);
void  func_801B3314(void);
void  func_801B3388(void);
void  func_801B33C4(void);
void  func_801B3400(void);
void  func_801B343C(void);
void  func_801B3488(void);
/* func_801B3540 */
void  Area_ClimbDismount(void);
void  func_801B3584(void);
void  func_801B35B0(void);
void  func_801B35EC(void);
void  func_801B3670(void);
void  func_801B3690(void);
void  func_801B371C(void);
void  func_801B3768(void);
void  func_801B3A3C(void);
void  func_801B3BFC(void);
u8*   func_801B3C3C(s32 bounds_x, s32 bounds_y);
void  Area_RollEncounterThreshold(u32 keep_armed);
s32   Area_CanStartEncounter(void);
s32   func_801B4150(void);
s32   func_801B43D0(s32 x, s32 y, s32 dir);
u8    func_801B4494(u8 wanted_code);
u8    func_801B44DC(u8 wanted_code);
u8    func_801B4D7C(u8 wanted_code);
bool  func_801B544C(void);
/* func_801B55C0 */
bool  Party_CanSwitchLeader(void);
/* func_801B5684 */
bool  Game_RequestLeaderSwitch(void);
bool  func_801B5758(void);
bool  func_801B5884(void);
bool  func_801B5910(void);
/* func_801B5AE4 */
s8    Game_FindRockAhead(s32 route_index, s32 route_flags);
void  func_801B5BDC(u8 route_index);
void* func_801B5C54(void);
/* func_801B5EBC */
bool  Game_RequestPersonalAction(void);
/* func_801B5F68 */
bool  Game_RequestRockKick(s32 walk_speed);
/* func_801B6044 */
bool  Game_RequestGarrPush(void);
void  func_801B60DC(s32 actor_index);
bool  func_801B6258(void);
void  func_801B6418(void);
bool  func_801B6674(void);
void  func_801B69C0(void);
void  func_801B6A04(void);
void  func_801B6AB0(void);
void  func_801B6BC8(void);
void  func_801B6F1C(void);
void  func_801B6FDC(void);
void  func_801B7024(void);
void  func_801B707C(void);
void  func_801B70D4(void);
void  func_801B726C(void);
void  func_801B72B0(void);
void  func_801B7344(void);
void  func_801B73B0(void);
void  func_801B73F4(void);
void  func_801B744C(void);
void  func_801B7658(void);
void  func_801B76F4(void);
void  func_801B781C(void);
void  func_801B78B4(void);
void  func_801B790C(void);
void  func_801B7950(void);
void  func_801B7988(void);
void  func_801B79F8(void);
void  func_801B7B54(void);
void  func_801B7C10(void);
void  func_801B7C58(void);
void  func_801B7CA0(void);
void  func_801B7D00(void);
void  func_801B7D44(void);
void  func_801B7D84(void);
void  func_801B7DC0(void);
void  func_801B7DFC(void);
void  func_801B7E38(void);
void  func_801B7E74(void);
void  func_801B7EF0(void);
void  func_801B7FE0(void);
void  func_801B80B4(void);
void  func_801B81EC(void);
void  func_801B8234(void);
void  func_801B828C(void);
void  func_801B830C(void);
void  func_801B8394(void);
void  func_801B8578(void);
void  func_801B85C0(void);
void  func_801B870C(void);
void  func_801B876C(void);
void  func_801B87B8(void);
void  func_801B8A0C(void);
void  func_801B8A9C(void);
bool  func_801B8C64(s32 pos_x, s32 pos_y, s16* distance_out, s32 probe_mode);
bool  func_801B8D18(void);
void  func_801B9048(void);
void  func_801B90A0(void);
void  func_801B9100(void);
void  func_801B91CC(void);
void  func_801B9210(void);
void  func_801B9478(void);
s32   func_801B9598(void);
s32   func_801B95E0(void);
u8    func_801B9F08(u8 arg0, u8 arg1, s8 arg2);
s32   func_801BA678(void);
s32   func_801BB2B8(s32 x0, s32 y0, s32 x1, s32 y1);
bool  func_801BB6F0(s32 command);
s32   func_801BB760(s32 x, s32 y);
s32   func_801BB7B0(s32 selector);
s32   func_801BB86C(s16 from_x0, s16 from_x1, s16 from_y0, s16 from_y1, u8 probe_mode);
void  func_801BB8E8(u8 arg_a, u8 arg_b, u8 arg_c);
bool  func_801BB934(s32 first_index, s32 second_index, s8 route_value, s32 expected_value);
void  func_801BBBC8(s16 from_x, s16 from_y);
void  func_801BBE48(void);
void  func_801BBE98(void);
void  func_801BBFB4(void);
void  func_801BC000(void);
s32   func_801BC4D0(void);
s32   func_801BC760(void);
void  func_801BCD60(s32 target_x, s32 target_y);
void  func_801BD290(s32 pos_x, s32 pos_y, s8* direction_out);
void  func_801BD32C(void);
void  func_801BD35C(void);
void  func_801BD38C(void);
void  func_801BD394(void);
void  func_801BD5A4(void);
void  func_801BD7F8(void);
void  func_801BD83C(void);
bool  func_801BD938(void);
void  func_801BDBC4(void);
s16   func_801BDCF8(s32 x, s32 y);
s32   func_801BDF08(void);
void  func_801BE574(s32 count, u8* ids);
void  func_801BE710(GameResetRecord* record);
void  Party_SwapMembers(u32 slot_a, u32 slot_b, u32 skip_state);
void  Party_SwapBattlerRows(s32 slot_a, s32 slot_b, s32 skip_state);
void  func_801BEBB0(void);
void  func_801BEDD0(void);
/* func_801BEE5C */
bool  Battle_LoadPartyScripts(void);
bool  func_801BF11C(void);
/* func_801BF448 */
void  Battle_PlaceMembers(void);
void  func_801BF5A8(s32 x, s32 y, s32 party_slot);
bool  func_801BF78C(void);
void  func_801BF8E0(void);
void  func_801BFAC4(void);
void  func_801BFB34(void);
void  func_801BFF9C(u32 work_kind, u32 work_index, u32 work_mode);
void  func_801C05AC(void);
void  func_801C0758(s32 x, s32 y, u8 kind);
s32   func_801C090C(s32 anchor_x, s32 anchor_y, s32 anchor_index);
void  func_801C0A68(void);
void  func_801C0AB4(void);
void  func_801C0CDC(void);
void  func_801C0D34(void);
void  func_801C0D54(void);
s32   func_801C0E48(void);
s32   func_801C0F9C(u8 source_row);
/* func_801C1254 */
void  Party_LoadMemberSprite(s32 character_id, s32 party_slot);
void  func_801C16B8(void);
void  func_801C1840(void);
void  func_801C1E88(s32 key, s32* counter);
void  func_801C1F4C(s32 key);
void  func_801C2018(void);
void  func_801C22D8(void);
void  func_801C2538(void);
void  func_801C2710(void);
bool  func_801C27E0(s8 tuning_delta);
bool  func_801C2894(s8 tuning_delta);
s32   func_801C2AAC(void);
s32   func_801C2B4C(void);
void  func_801C2E34(u8 index);
void  func_801C308C(s32 arg);
void  func_801C3154(void);
void  func_801C3204(void);
s32   func_801C364C(s32 wanted_code, s32 cell_code, s32 find_facing);
bool  func_801C3790(s32 mode_byte);
bool  func_801C37DC(s32 mode_byte);
void  func_801C3828(void);
s32   func_801C38F4(s32 record_index, s32 field_mode, s32 wanted_id);
u8    func_801C39D8(s32 pos_x, s32 pos_y, s32 flag, s32 wanted_code, u8 mask_cells);
u8    func_801C3A18(s32 pos_x, s32 pos_y, u8 wanted_code, u8 mask_cells);
s32   func_801C3B78(s32 pos_x, s32 pos_y, s32 wanted_code, s32 mask_cells);
s32   func_801C3E40(s32 pos_x, s32 pos_y, s32 probe_flag, s16 probe_range);
bool  func_801C3E80(s32 pos_x, s32 pos_y, s32 probe_flag);
s32   func_801C4040(s32 pos_x, s32 pos_y, s16 probe_range);
s32   func_801C41D0(s32 pos_x, s32 pos_y, s16 probe_range);
u8    func_801C472C(s32 pos_x, s32 pos_y, s32 flag, s32 wanted_code, u8 mask_cells);
u8    func_801C476C(s32 pos_x, s32 pos_y, u8 wanted_code, u8 mask_cells);
u8    func_801C48FC(s32 pos_x, s32 pos_y, u8 wanted_code, u8 mask_cells);
void  func_801C4D1C(void);
void  func_801C4D58(void);
s32   func_801C4E14(void);
bool  func_801C4EC4(void);
bool  func_801C4F88(void);
s32   func_801C4FE0(void);
void  func_801C51B0(void);
void  Actor_ClearVelocity(void);
s32   func_801C520C(void);
bool  func_801C539C(void);
s32   func_801C5474(void);
void  func_801C5558(void);
void  func_801C5620(void);
void  func_801C56E4(void);
/* func_801C57B4 */
void  Actor_Move(void);
void  func_801C57F4(void);
void  func_801C5830(void);
void  func_801C5838(void);
void  func_801C5874(void);
void  func_801C5BB8(void);
void  func_801C5C7C(void);
void  func_801C5CB4(void);
void  func_801C5D68(void);
/* func_801C63B0 */
bool  Area_PlaceEncounterParty(void);
bool  func_801C6658(s32 table_index, s32 table_slot, s32 entry_index, s32 selection);
s32   func_801C6888(s32 entity_index);
s32   func_801C69C8(s32 record_index);
/* func_801C6A7C */
s32   Area_PickEncounter(void);
/* func_801C6AEC */
s32   Area_RollEncounterEnemies(s32 candidate_id);
/* func_801C6BB4 */
bool  Area_PlaceEncounterEnemies(void);
bool  func_801C6DCC(void);
bool  func_801C6EE0(s32 entry_count, s32 pos_x, s32 pos_y, s32 reach);
u32   func_801C6FD4(s32 map_column, s32 map_row);
bool  func_801C7064(s32 x, s32 y, s32 reach, s32 height);
s16   func_801C7188(s16 value);
s32   func_801C71AC(s32 delta);
u16*  func_801C71C4(u16* out, s32 pos_x, s32 pos_y, s32 view_height);
/* func_801C7244 */
void  Area_SetEncounterCamera(s32 mode);
bool  func_801C7498(s32 from_x, s32 from_y, s32 to_x, s32 to_y, u8 reach, u8 other_reach);
s32   func_801C7518(s32 pos_x, s32 pos_y, s32 reach);
bool  func_801C7608(s16 x0, s16 y0, s16 x1, s16 y1);
s32   func_801C7824(s16 from_x, s16 from_y, s16 to_x, s16 to_y);
void  func_801CF564(void);
void  func_801CF5A8(void);
void  func_801CF650(void);
void  func_801CF694(void);
void  func_801CF878(void);
void  func_801CF8BC(void);
void  func_801CFA30(void);
void  func_801CFA74(void);
void  func_801CFAB8(void);
void  func_801CFAFC(void);
void  func_801CFB40(void);
void  func_801CFC2C(void);
void  func_801CFC70(void);
void  func_801CFCF8(void);
void  func_801CFD3C(void);
void  func_801CFE54(void);
void  func_801CFE98(void);
void  func_801CFF20(void);
void  func_801CFF64(void);
void  func_801D026C(void);
void  func_801D02B0(void);
void  func_801D0324(void);
void  func_801D0368(void);
void  func_801D04DC(void);
void  func_801D0520(void);
void  func_801D05A8(void);
void  func_801D05EC(void);
void  func_801D0704(void);
void  func_801D0748(void);
void  func_801D07D0(void);
void  func_801D0814(void);
void  func_801D0900(void);
void  func_801D0944(void);
void  func_801D09CC(void);
void  func_801D0A10(void);
s32   func_801D0C18();
void  func_801D0C98(void);
void  func_801D0D38(void);
void  func_801D0DA4(void);
void  Shop_DispatchStep(void);
void  func_801D0EAC(void);
void  func_801D0EF8(void);
void  func_801D1014(void);
void  func_801D1068(void);
void  func_801D10A4(void);
void  func_801D13DC(void);
void  func_801D1588(void);
void  Menu_DispatchStep(void);
void  func_801D1B10(void);
void  func_801D20C8(void);
void  func_801D2170(void);
s32   func_801D25D8();
/* func_801D2978 */
void  Fishing_ActorRun(void);
void  func_801D2BF0(void);
void  func_801D2DEC(void);
void  func_801D3358(void);
void  func_801D35CC(void);
void  func_801D42A0(void);
void  func_801D50E8(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4);
void  func_801D5634(s32 arg0, s16 arg1, s16 arg2, s32 arg3, u8 arg4, void* arg5);
void  func_801D7AD0(MenuPanelTask* task);
void  func_801D9B14(void);
void  func_801DE1C0(void);
void  func_801E0BD0(void);
void  func_801E0C20(void);
void  func_801E0C40(void);
void  func_801E3E88(void);
s32   func_801F2C04(void);
void  func_801F2C14(void);
void  func_801F2C18(void);
void  func_801F2C1C(void);
void  func_801F2C30(void);
void  func_801F2C34(void);
void  Fishing_ShowLocation(void);
void  func_801F2C3C(void);
void  func_801F2C40(void);
void  func_801F2C44(void);
void  func_801F2C48(void);
void  func_801F2C5C(void);
s32   func_801F2C64(s32, s32);
void  func_801F2C6C(void);
void  func_801F2C7C(void);
void  func_801F2C80(void);
void  func_801F2C88(void);
void  func_801F2C8C(void);
void  func_801F2C90(void);
s32   func_801F2C98(s32, s32);
s32   func_801F2C9C(s32, s32);
void  func_801F2CA0(void);
void  func_801F2CA8(void);
s32   func_801F2CC0(s32, s32);
void  func_801F2CC4(void);
void  func_801F2CDC(void);
s32   func_801F2CE4(s32 entry_x, s32 entry_y);
void  func_801F2CE8(void);
void  func_801F2CF0(void);
void  func_801F2CF8(void);
void  func_801F2D0C(void);
void  func_801F2D18(void);
void  func_801F2D78(void);
void  func_801F2D90(void);
void  func_801F2DA4(void);
void  func_801F2DB0(void);
s32   func_801F2DB4(s32, s32);
s32   func_801F2DCC();
void  func_801F2DE4(void);
void  func_801F2E10(void);
void  func_801F2E1C(void);
void  func_801F2E20(void);
void  func_801F2E5C(void);
s32   func_801F2E80(s32, s32);
void  func_801F2E88(void);
void  func_801F2E98(void);
void  func_801F2EA0(void);
void  func_801F2EEC(void);
void  func_801F2EF0(void);
void  func_801F2F04(void);
void  func_801F2F0C(void);
void  func_801F2F20(void);
void  func_801F2F24(void);
void  func_801F2F54(void);
s32   func_801F2F58(s32, s32);
void  func_801F2FB0(void);
void  func_801F2FD0(void);
void  func_801F2FF0(void);
void  func_801F3014(void);
void  func_801F3064(void);
void  func_801F3070(void);
void  func_801F307C(void);
void  func_801F309C(void);
void  func_801F30A8(void);
void  func_801F30BC(void);
void  func_801F30C8(void);
void  func_801F30EC(void);
s32   func_801F3118(s32, s32);
void  func_801F3120(void);
bool  func_801F315C(s32, s32);
void  func_801F3180(void);
void  func_801F3194(void);
void  func_801F3198(void);
void  func_801F31AC(void);
void  func_801F31B0(void);
void  func_801F31E4(void);
void  func_801F31E8(void);
void  func_801F31EC(void);
s32   func_801F3210(s32, s32);
void  func_801F3234(void);
void  func_801F3244(void);
void  func_801F3254(void);
void  func_801F3264(void);
void  func_801F32C0(void);
void  func_801F32DC(void);
void  func_801F32E0(void);
void  func_801F3304(void);
void  func_801F3350(void);
void  func_801F3378(void);
void  func_801F3380(void);
void  func_801F338C(void);
void  func_801F33A8(void);
void  func_801F33AC(void);
void  func_801F33B4(void);
void  func_801F33C8(void);
void  func_801F33D8(void);
void  func_801F33E0(void);
s32   func_801F33E4(s32, s32);
s32   func_801F3400(void);
void  func_801F3404(void);
void  func_801F3418(void);
void  func_801F341C(void);
void  func_801F3420(void);
void  func_801F3434(void);
void  func_801F343C(void);
void  func_801F3440(void);
void  func_801F3448(void);
void  func_801F344C(void);
void  func_801F3450(void);
void  func_801F3454(void);
void  func_801F3460(void);
void  func_801F3474(void);
void  func_801F34A0(void);
void  func_801F34E0(void);
void  func_801F34FC(void);
void  func_801F352C(void);
void  func_801F3560(void);
void  func_801F358C(void);
void  func_801F35D8(void);
void  func_801F35E0(void);
void  func_801F35F4(void);
void  func_801F35FC(void);
s32   func_801F3628();
s32   func_801F3658(s32, s32);
void  func_801F3678(void);
void  func_801F36A4(void);
void  func_801F36D4(void);
void  func_801F3740(void);
void  func_801F3764(void);
void  func_801F3798(void);
void  func_801F37B0(void);
void  func_801F37D0(void);
void  func_801F37E4(void);
void  func_801F37EC(void);
s32   func_801F3868();
void  func_801F389C(void);
void  func_801F38C0(void);
void  func_801F38D8(void);
void  func_801F38DC(void);
void  func_801F390C(void);
s32   func_801F3944(s32 entry_x, s32 entry_y);
void  func_801F394C(void);
void  func_801F39BC(void);
void  func_801F3A14(void);
void  func_801F3A24(void);
s32   func_801F3A28(void);
void  func_801F3A38(void);
void  func_801F3A50(void);
void  func_801F3A64(void);
s32   func_801F3A6C(s32, s32);
void  func_801F3A78(void);
void  func_801F3A8C(void);
void  func_801F3AFC(void);
void  func_801F3B4C(void);
void  func_801F3B5C(void);
void  func_801F3B94(void);
void  func_801F3BD0(void);
void  func_801F3BE0(void);
void  func_801F3BE8(void);
void  func_801F3C10(void);
void  func_801F3C24(void);
void  func_801F3C74(void);
void  func_801F3C98(void);
void  func_801F3CB0(void);
void  func_801F3CD0(void);
s32   func_801F3CD4(s32, s32);
s32   func_801F3CF0(s32, s32);
void  func_801F3D08(void);
void  func_801F3D28(void);
void  func_801F3D60(void);
void  func_801F3D6C(void);
s32   func_801F3D78(s32, s32);
void  func_801F3E04(void);
void  func_801F3E0C(void);
void  func_801F3E14(void);
void  func_801F3E20(void);
s32   func_801F3EBC(void);
void  func_801F3EE8(void);
void  func_801F3F04(void);
s32   func_801F3F2C(s32, s32);
void  func_801F3F34(void);
s32   func_801F3F68(s32, s32);
void  func_801F3F80(void);
void  func_801F3FF8(void);
void  func_801F4034(void);
void  func_801F4038(void);
void  func_801F40AC(void);
void  func_801F40C0(void);
void  func_801F40E4(void);
s32   func_801F4108(void);
void  func_801F410C(void);
s32   func_801F4140(void);
void  func_801F4158(void);
void  func_801F4164(void);
void  func_801F4178(void);
void  func_801F418C(void);
void  func_801F41A0(void);
void  func_801F41A8(void);
void  func_801F41B0(void);
void  func_801F41D0(void);
s32   func_801F41D8();
s32   func_801F41F4(s32 entry_x, s32 entry_y);
void  func_801F4238(void);
void  func_801F4254(void);
void  func_801F427C(void);
s32   func_801F42F4(s32, s32);
void  func_801F4344(void);
void  func_801F4364(void);
void  func_801F4378(void);
void  func_801F4380(void);
s32   func_801F43DC(s32 entry_x, s32 entry_y);
void  func_801F448C(void);
void  func_801F4494(void);
void  func_801F44B0(void);
void  func_801F44F8(void);
void  func_801F4500(void);
void  func_801F4504(void);
void  func_801F4528(void);
void  func_801F4534(void);
void  func_801F4538(void);
void  func_801F455C(void);
void  func_801F45BC(void);
void  func_801F45CC(void);
void  func_801F45E0(void);
void  func_801F45EC(void);
void  func_801F45FC(void);
void  func_801F4604(void);
void  func_801F4628(void);
void  func_801F469C(void);
void  func_801F46A0(void);
void  func_801F46D4(void);
void  func_801F4768(void);
void  func_801F477C(void);
void  func_801F4798(void);
void  func_801F47A0(void);
s32   func_801F48B4(void);
void  func_801F4914(void);
void  func_801F49D4(void);
void  func_801F4A0C(void);
s32   func_801F4A18(s32 entry_x, s32 entry_y);
void  func_801F4B00(void);
void  func_801F4B58(void);
void  func_801F4B60(void);
void  func_801F4B80(void);
void  func_801F4BC0(void);
s32   func_801F4C28(void);
void  func_801F4C84(void);
s32   func_801F4CC4(s32, s32);
s32   func_801F4CD0();
void  func_801F4CD8(void);
void  func_801F4CDC(void);
void  func_801F4D14(void);
void  func_801F4D80(void);
void  func_801F4D9C(void);
s32   func_801F4DF8(void);
void  func_801F4F00(void);
void  func_801F4F60(void);
void  func_801F4F9C(void);
s32   func_801F4FA4(s32, s32);
void  func_801F502C(void);
void  func_801F50F0(void);
void  func_801F512C(void);
void  func_801F5130(void);
s32   func_801F5208(s32, s32);
void  func_801F529C(void);
void  func_801F52C8(void);
void  func_801F52F8(void);
void  func_801F532C(void);
s32   func_801F53A4(s32, s32);
void  func_801F53D4(void);
void  func_801F5608(void);
void  func_801F5880(void);
void  func_801F5918(void);
void  func_801F5E1C(void);
void  func_801F5E4C(void);
void  func_801F60C0(void);
void  func_801F6390(void);
void  func_801F6D00(void);
void  func_801F6DC0(void);
void  func_801F6DCC(void);
void  func_801F6E70(void);
void  func_801F6EA4(void);
void  func_801F6F38(void);
void  func_801F6F48(void);
void  func_801F6F68(void);
void  func_801F707C(void);
void  func_801F70B4(void);
void  func_801F70F0(void);
void  func_801F7174(void);
void  func_801F7198(void);
void  func_801F71C0(void);
void  func_801F729C(void);
void  func_801F735C(void);
void  func_801F73B8(void);
void  func_801F73BC(void);
void  func_801F73F8(void);
void  func_801F7440(void);
void  func_801F74EC(void);
void  func_801F7508(void);
void  func_801F7518(void);
void  func_801F75F8(void);
void  func_801F77A8(void);
void  func_801F77F8(void);
void  func_801F7928(void);
void  func_801F7A18(void);
void  func_801F7A84(void);
void  func_801F7A9C(void);
void  func_801F7AA8(void);
void  func_801F7BA8(void);
void  func_801F7D04(void);
void  func_801F7DF0(void);
void  func_801F82E4(void);
void  func_801F844C(void);
void  func_801F8488(void);
void  func_801F85FC(void);
void  func_801F8748(void);
void  func_801F87B4(void);
void  func_801F8A5C(void);
void  func_801F8D70(void);
void  func_801F95D4(void);
void  func_801F986C(void);
void  func_801F9DBC(void);

/* Run the overlay map-load handshake: wait for the loader, switch the window
 * to mode 3, drain the effect loop and run the world/front update slice. */
static inline void GameRunMapLoadHandshake(void) {
    CallbackWait(1U);
    CallbackWait(1U);
    g_EmiStreamFlags = 0x20;
    EMI_GetArchiveId(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    while (EMI_IsReady() == 0) {
        CallbackWait(1U);
    }
    UI_SetMode(3U);
    if (WINDOW_EFFECT_BUSY()) {
        do {
            func_801992B8();
            CallbackWait(1U);
        } while (WINDOW_EFFECT_BUSY());
    }
    g_GameEntryState    = 2;
    g_GameEntrySubstate = 0;
    g_GameStateIndex    = GAME_REQUEST_IDLE;
    Area_RunFrame();
}

/* Add the flag-selected step to the shared counter byte. */
static inline s32 Game_AddStepByFlag(s32 step, Actor* actor, s32 value_b, u8 flag_bits) {
    s32 bit0;
    s32 flags;
    u8  value;
    u8* work;

    bit0 = flag_bits & 1;
    if (bit0 != 0) {
        if ((D_80146878 & 0x1) != (g_EncounterSteps & 0x1)) {
            value = actor->unk_7B;
            if (value < 0xFAu) {
                actor->unk_7B = (u8)(value + step);
            }
            return 1;
        }
    }
    flags = flag_bits & 0x2;
    if (flags != 0) {
        if (actor->unk_7B != 0u) {
            work      = (u8*)g_Task;
            work[9]   = (u8)(0x20 / (s32)(value_b & BYTE_MASK));
            work      = (u8*)g_Task;
            work[0xA] = (u8)(work[9] >> 1);
        }
    }
    return 0;
}

/* Roll the selector-chosen setup path. */
static inline void Game_RollAreaSetup(s32 actor_slot) {
    u32 choice;

    choice = (u32)RANDOM_MASK(0xF);
    if ((g_Task->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
        func_8015BAC4((u8)((g_Game.members[0].facing ^ 4) & 7));
    }
    g_Game.flags |= GAME_FLAG_SCRIPT_ACTIVE;
    if ((g_CurrentActor->unk_94 & 0x80) == 0) {
        g_CurrentActor->unk_94 |= 0x80;
        switch ((u8)choice) {
            case 0:
            case 1:
            case 2:
            case 3:
                func_801ADAC0(1);
                g_Task->unk_04 = 3;
                break;
            case 4:
            case 5:
            case 6:
                func_801ADAC0(1);
                Party_AddZenny(2, 0);
                func_801ADCF4((u8)((s32)(-(((s32)GAME_WORK_AREA_PTR - (s32)g_Actors) * 0xD79435E5)) >> 3));
                g_Task->unk_04 = 1;
                break;
            case 7:
                func_801ADAC0(1);
                Party_AddZenny(5, 0);
                func_801ADCF4((u8)((s32)(-(((s32)GAME_WORK_AREA_PTR - (s32)g_Actors) * 0xD79435E5)) >> 3));
                g_Task->unk_04 = 2;
                break;
            default:
                func_801ADAC0(actor_slot);
                g_Task->unk_04 = 3;
                break;
        }
    } else {
        if (choice >= 8) {
            func_801ADAC0(1);
        } else {
            func_801ADAC0(actor_slot);
        }
        g_Task->unk_04 = 3;
    }
}

s32 func_801A20F8(s16 cell_x, s16 cell_y);

s32 func_801B1B2C(s32 x, s32 y, s32 probe_kind, s32 flags);

s32 func_801B1C18(s32 x, s32 y, s32 mode);

u8 func_801B4BE4(u8 mode, u8 code);

void func_801B690C(void);

s32 func_801BA278(u8 cell0, u8 cell1, u8 cell2, u8 cell3, u8 cell4);

void func_801BB9B4(s16 probe_x, s16 probe_y);

void func_801BBCCC(s16 from_x, s16 from_y, s16 to_x, s16 to_y);

s32 Area_BuildEncounter(u8 work_mode, s32 work_index);

#endif
