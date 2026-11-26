#ifndef OVERLAY_ETC_GAME_00_H
#define OVERLAY_ETC_GAME_00_H
#define ENGINE_LOCAL_DECLS

/* The etc/game/00 overlay's local declarations: the frontend state, the resource,
 * area and handler tables, and the prototypes its units share. Only this image
 * includes the file; the data tables are in data.h. */

#define FAKE_DECL_GRAPHICS_PALETTE_PENDING_VOLATILE
#define FAKE_DECL_GAME_REQUEST_FLAGS_VOLATILE
#include "shared/etc.h"

#include "shared.h"

#include "game/character.h"
#include "common/vector.h"
#include "menu/gameui.h"
#include <string.h>

#include "data.h"
#include <stdio.h>
#include "engine/state/battle/battle.h"
#include "engine/state/mode/mode.h"
#include "engine/state/scene/scene.h"
#include "engine/state/progress/progress.h"
#include "engine/area/collision/collision.h"
#include "engine/area/encounter/encounter.h"
#include "engine/worldmap/worldmap.h"
#include "engine/area/action/action.h"
#include "engine/actor/motion/motion.h"
#include "engine/actor/script/script.h"
#include "engine/actor/task/task.h"
#include "engine/actor/ops/ops.h"
#include "engine/party/party/party.h"
#include "engine/party/character/character.h"
#include "engine/ui/menu/menu.h"
#include "engine/area/map/map.h"
#include "engine/camera/camera.h"
#include "engine/gfx/palette/palette.h"
#include "engine/gfx/prim/prim.h"

#define TILE_RUN_SIZE          0x8

/* Fixed retail addresses the units dereference. */
#define ENCOUNTER_TABLE_BASE   0x800E4000u /* formations and enemy records (@source: wiki:formats/area) */
#define GAME_AREA_ID_ADDR      0x80143F00  /* the u16 world id; MEM reads it non-volatile to match retail */
#define AREA_MESSAGE_REQUEST   0xD8        /* the message UI_MessageRunArea starts */

#define SCRATCH_WORK           SP_REF(volatile Actor*, 0x44u)
#define GAME_ENTITY_COUNTER    SP_REF(s16, 0x0u)
#define GAME_ENTITY_ENTRY_DATA SP_REF(u16, 0x2u)
#define ENTITY_MAX             30
#define GAME_WORK_AREA_PTR     (*(volatile Actor**)&g_CurrentActor)

/* NOTE: retail reads the window style byte at 0x80144952 signed (`lb`) in UI_PanelRunTask and
 * UI_WindowDrawFrame and unsigned (`lbu`) in func_801999F8 and UI_WindowDrawOutline, so exports.h keeps u8 and only
 * the signed readers view it as s8. */
#define GAME_WINDOW_STYLE      (*(s8*)&g_WindowStyle)

/* FAKE: the game images call Area_CellGetCode as s32(s16, s16) and truncate at the call; the area images pass
 * s32 coordinates untruncated, so one prototype cannot serve both (an s16 prototype changes 11 area images). */
#define AREA_CELL_CODE_S16     ((s32 (*)(s16, s16))Area_CellGetCode)
#define GAME_TILE_RUN(index)   ((TileRuns*)g_AreaLoads[(index)])
#define g_AreaLoads            ((void**)g_AreaLoads)
#define g_RouteSpeedScale      ((u8*)g_RouteSpeedScale)

/* Start an EMI stream slot and stage the palette advance. A bare statement
 * macro: the member declares `ent` and `ev`. Kept: tested as an inline, the
 * slot argument and the member's locals change the frame and register use; the
 * do/while form moves bytes. */
#define GAME_START_STREAM_AND_STAGE_PALETTE(slot) \
    UI_ModeSet(2u);                               \
    if (WINDOW_EFFECT_BUSY()) {                   \
        do {                                      \
            Area_RunLoadingFrame();               \
            SYS_ThreadWait(1u);                   \
        } while (WINDOW_EFFECT_BUSY());           \
    }                                             \
    SYS_ThreadWait(1u);                           \
    SYS_ThreadWait(1u);                           \
    EMI_ArchiveLoad(slot);                        \
    while (EMI_IsReady() == 0) {                  \
        SYS_ThreadWait(1u);                       \
    }                                             \
    GFX_PaletteCopy(1u);                          \
    GFX_PaletteCopy(2u);                          \
    ent = (u16*)&g_GameEntrySubstate;             \
    ev  = *ent;                                   \
    ev += 1u;                                     \
    g_GfxPalettePending = 1u;                     \
    *ent                = ev

/* Run the scenario dispatch entry. A bare statement macro: the member declares
 * `saved` and `result`, runs its fallback when `result` is 0 and restores
 * g_Task. Kept: `entry` is a member name of the scenario handler record, so it
 * cannot be an argument without an indirect call; the do/while form moves
 * bytes. */
#define GAME_RUN_SCENARIO_ENTRY(entry)                                                         \
    saved  = g_Task;                                                                           \
    result = g_ScenarioHandlers[(s32)g_ScenarioState.scenario_id]->entry(handler_x, handler_y)

/* Run the gated cell test and arm the work record on a hit. Kept: it returns
 * from the member and takes the flag value after a branch; tested as an inline,
 * the bytes move. */
#define GAME_ARM_WORK_ON_CELL_HIT(code, new_step)                                                                                                     \
    if ((g_Game.flags & 0x400) == 0) {                                                                                                                \
        if ((Game_TestMapCells(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->voice_flags.scene_flag, code, 0) & BYTE_MASK) != 0) { \
            TASK(Actor)->header.mode = 2;                                                                                                             \
            TASK(Actor)->header.step = new_step;                                                                                                      \
            TASK(Actor)->unk_03      = 0;                                                                                                             \
            TASK(Actor)->unk_04      = 0;                                                                                                             \
            return 1;                                                                                                                                 \
        }                                                                                                                                             \
    }                                                                                                                                                 \
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
    TILE_RUN_FLAG_VERTICAL = 1 << 7,
} TileRunFlags;

/* `ScriptState.flags` bit 7 marks a cursor still moving between cells. */
typedef enum GameCursorFlags {
    GAME_CURSOR_FLAG_MOVING = 1 << 7,
} GameCursorFlags;

typedef struct GameReset {
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
} GameReset;

typedef struct {
    u8  cx;    /* 0x00 */
    u8  cy;    /* 0x01 */
    u16 key;   /* 0x02 */
    u16 index; /* 0x04 */
    u16 alt;   /* 0x06 */
    u8  mode;  /* 0x08 */
    u8  span;  /* 0x09 */
    u8  type;  /* 0x0A */
    u8  pad;   /* 0x0B */
} GameLocale;

ASSERT_SIZE(GameLocale, 0x0C);

/* One destination of an area link whose key is 0xFFFF: the first whose scene flag is set is taken. */
typedef struct {
    u16 area_id;    /* 0x00 */
    u16 x;          /* 0x02 */
    u16 y;          /* 0x04 */
    u8  flag_block; /* 0x06: the 8-byte block of g_SceneFlagWords */
    u8  flag_bit;   /* 0x07 */
    u8  facing;     /* 0x08 */
    u8  pad_09;
} GameLocaleChoice;

ASSERT_SIZE(GameLocaleChoice, 0x0A);

typedef struct {
    u8                 pad_00[0x20]; /* 0x00-0x1F */
    GameLocale*        entries;      /* 0x20 */
    GameLocaleChoice** keys;         /* 0x24 */
    u8*                counts;       /* 0x28 */
    u8                 pad_2C[4];    /* 0x2C-0x2F */
    u8                 outer;        /* 0x30 */
} GameLocaleBank;

typedef struct TileRun {
    u8 x;
    u8 y;
    u8 flags; /* TileRunFlags */
    u8 length;
    u8 unk_04[4];
} TileRun;

ASSERT_SIZE(TileRun, TILE_RUN_SIZE);

typedef struct TileRuns {
    u8       pad_00[0x2C];
    TileRun* runs; /* 0x2C */
    u8       pad_30;
    u8       last_run; /* 0x31 */
} TileRuns;

ASSERT_OFFSET(TileRuns, runs, 0x2C);
ASSERT_OFFSET(TileRuns, last_run, 0x31);

/* The party leader's field action on an actor: a one-time random zenny find, flagged in the actor so
 * it pays once. The Alt table differs only in the reaction effect its roll starts. */
typedef enum AreaActionStep {
    AREA_ACTION_STEP_ROLL,
    AREA_ACTION_STEP_SMALL_FIND,
    AREA_ACTION_STEP_LARGE_FIND,
    AREA_ACTION_STEP_NONE,
    AREA_ACTION_STEP_MESSAGE,
    AREA_ACTION_STEP_COUNT
} AreaActionStep;

/* The wrapper record stays: the dispatchers copy the whole table to the stack before they index
 * it, and a plain array gives no assignment that compiles to that copy. */
typedef struct AreaActionSteps {
    Callback steps[AREA_ACTION_STEP_COUNT];
} AreaActionSteps;

typedef struct AreaActionAltSteps {
    Callback steps[AREA_ACTION_STEP_COUNT];
} AreaActionAltSteps;

/* The variant that fades the actor's tint back after the find. */
typedef enum AreaActionFadeStep {
    AREA_ACTION_FADE_STEP_ROLL,
    AREA_ACTION_FADE_STEP_NONE,
    AREA_ACTION_FADE_STEP_SMALL_FIND,
    AREA_ACTION_FADE_STEP_LARGE_FIND,
    AREA_ACTION_FADE_STEP_MESSAGE,
    AREA_ACTION_FADE_STEP_FADE,
    AREA_ACTION_FADE_STEP_COUNT
} AreaActionFadeStep;

typedef struct AreaActionFadeSteps {
    Callback steps[AREA_ACTION_FADE_STEP_COUNT];
} AreaActionFadeSteps;

/* Route step handler: advances one script cursor and reports a byte result. */
typedef s32 (*RouteStepCallback)(u8* cursor);

/* An area script call: the area load record names the routine. */
typedef void (*AreaScriptCallback)(void* area);

typedef struct CellPaletteIndices {
    u8 cells[9];
} CellPaletteIndices;

typedef struct CellEffect {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} CellEffect;

typedef struct CellEffects {
    CellEffect entries[9];
} CellEffects;

typedef struct PaletteColors {
    u16 colors[4];
} PaletteColors;

extern u16 D_1F800002; /* 0x1F800002; packed spawn record staging halfword */
extern u16 D_1F800004; /* 0x1F800004 */
extern s16 D_1F800008; /* 0x1F800008 */
extern u16 D_1F80000A; /* 0x1F80000A */
extern s16 D_1F80000C; /* 0x1F80000C */
extern u16 D_1F80000E; /* 0x1F80000E */
extern s8  D_800E4D40; /* 0x800E4D40 */
extern s16 D_800E4D42; /* 0x800E4D42 */
extern u8  D_80143BB1;
/* A unit that must keep the read where it is written (Actor_SpawnFromDefRow) defines
 * FAKE_DECL_GAME_AREA_ID_VOLATILE before its first include. */
#ifdef FAKE_DECL_GAME_AREA_ID_VOLATILE
extern volatile u16 g_GameAreaId;
#endif
/* D_80143F06 */
extern u8                  g_GameLastCellType; /* 0x80143F06 */
/* D_80143F08 */
extern volatile u32        g_GameLastX; /* 0x80143F08 */
/* D_80143F0C */
extern volatile u32        g_GameLastY; /* 0x80143F0C */
extern s16                 D_80143F16;  /* 0x80143F16; signed high halfword of the context bundle */
extern s16                 D_80143F1A;  /* 0x80143F1A */
extern s16                 D_80143F2A;  /* integer half of g_EncounterOriginY */
/* Scene step byte, countdown halfword and the slot index cached in the
 * scratchpad byte at 0x1F800000. The read-modify-write sites go through a
 * pointer, which is the shape this target's exact siblings use; plain stores
 * keep the scalar spelling.
 */
extern u8                  D_80143F49;
extern volatile u8         D_80143F4A;
extern volatile u8         D_80143F4B; /* 0x80143F4B */
extern s8                  D_80143F4E; /* 0x80143F4E */
extern u8                  D_80143F51;
extern s32                 D_80143F5C;
extern s32                 D_80143F84;
extern s16                 g_ScrollHeight; /* the exe declares it as an array; the scalar keeps these bytes */
extern u8                  D_80143FBC;
extern u8                  D_80143FBD;
extern u8                  D_80143FBF;
extern u8                  D_80143FC1;
extern u8                  D_80143FC3;
extern s8                  D_801448E8; /* 0x801448E8 */
extern s16                 D_801448EE; /* 0x801448EE */
extern s16                 D_801448F0; /* 0x801448F0 */
extern u8                  D_80144EE2;
extern u8                  D_80144F5E[]; /* 0x80144F5E */
extern u8                  D_80144FC4[]; /* 0x80144FC4; per-slot spawn-gate flag bytes */
extern u8                  D_80145004[]; /* 0x80145004 */
extern s32                 D_8014503C;   /* 0x8014503C */
extern s8                  D_8014504B;   /* 0x8014504B */
extern u8                  D_801457AB;
extern u8                  D_80145E9B;
extern u32                 D_80145EDC; /* 0x80145EDC */
extern u8                  D_80145F00; /* 0x80145F00 */
extern u16                 D_80145FB8; /* 0x80145FB8 */
extern u8                  D_80145FD1;
extern u8                  D_80145FD6;
extern u8                  D_80145FDB;
extern u8                  D_80146111;
extern u8                  D_80146119;
extern u8                  D_8014611B;
extern s32                 D_8014611C;
extern s32                 D_80146120;
extern s32                 D_80146144;
extern s32                 D_80146148;
extern volatile u8         D_80146256;
extern u8                  D_80146260;
extern u8                  D_80146261;
extern u8                  D_80146262;
extern s32                 D_80146264; /* 0x80146264 */
extern s16                 D_80146266; /* 0x80146266 */
extern s32                 D_80146268; /* 0x80146268 */
extern s16                 D_8014626A; /* 0x8014626A */
extern u8                  D_8014626C;
extern u8                  D_8014626E;
extern u8                  D_8014626F;
extern u8                  D_80146270;
extern u8                  D_80146855;
extern u8                  D_80146856;
extern u8                  D_80146893[]; /* 0x80146893 */
extern u8                  D_801468BE[]; /* 0x801468BE */
extern u8                  D_801468C2[]; /* 0x801468C2 */
extern s32                 D_801468C4;
/* FAKE: column views of g_Actors for the spawn functions (+0x77 unk_77, +0x78 unk_78, +0x8C ext, +0x94 unk_94).
 * The member form shares one slot offset between the stores and shortens each function by 0x34 bytes. */
extern u8                  D_801468FF;
extern u8                  D_80146900[ENTITY_MAX][ACTOR_SIZE]; /* 0x80146900 */
/* FAKE: column views of g_Actors for Actor_SpawnPartyFromRecord and Actor_SpawnFromDefRow, the only forms that match them. */
extern u16                 D_80146904[ENTITY_MAX][ACTOR_SIZE / 2];       /* Actor.unk_7C */
extern s32                 g_ActorWalkDestX[ENTITY_MAX][ACTOR_SIZE / 4]; /* Actor.walk_dest_x */
extern s32                 g_ActorWalkDestY[ENTITY_MAX][ACTOR_SIZE / 4]; /* Actor.walk_dest_y */
extern s32                 D_80146910[ENTITY_MAX][ACTOR_SIZE / 4];       /* Actor.unk_88 */
extern u16                 D_80146914;
extern u16                 D_80146918[][ACTOR_SIZE / 2];
extern u8                  D_8014691C[ENTITY_MAX][ACTOR_SIZE]; /* 0x8014691C */
/* D_80147A58 */
extern u16                 D_801481D8;
extern u16                 D_801481E0;
extern Pos3                D_801481E8;         /* scene angle, 16.16 fixed point */
extern Pos3                D_801481F8;         /* per-frame step of D_801481E8 */
extern s16                 D_8014820C;         /* 0x8014820C */
extern s8                  D_80148654;         /* 0x80148654 */
extern s8                  D_80148656;         /* 0x80148656 */
extern s8                  D_801490E0;         /* 0x801490E0 */
extern u8*                 g_EncounterZones[]; /* the exe declares it as const EncounterZone lists; these units walk the bytes */
extern Offset2             g_FacingOffsets[];  /* 0x80181AC0 */
extern s8                  D_80181B00[];
extern s8                  D_80181B01[];
extern u8                  D_80181B1C[]; /* 0x80181B1C */
extern u8                  D_80181B28[]; /* 0x80181B28 */
/* D_80181B70 */
extern s16                 g_AreaClimbHeightOffsets[]; /* 0x80181B70 */
extern const s32           D_80181CA8[30][2];
extern u8                  D_80181E40[];          /* 0x80181E40 */
extern u8                  D_80181E44[];          /* 0x80181E44 */
extern u8                  D_8018214C[];          /* 0x8018214C */
extern u8                  s_ScriptCopyBlock[16]; /* 0x8018216C */
/* D_8018217C */
extern u8                  g_AreaScriptTests; /* 0x8018217C */
extern RouteStepCallback   D_801821C0[];
extern u8                  D_8018E268[];
extern char                D_80195858[]; /* 0x80195858 */
extern char                D_80195860[]; /* 0x80195860 */
/* D_80195ED4 */
extern AreaActionSteps     g_AreaActionSteps; /* 0x80195ED4 */
extern char                D_80195F0C[];      /* 0x80195F0C */
/* D_80195F10 */
extern AreaActionAltSteps  g_AreaActionAltSteps; /* 0x80195F10 */
/* D_80195F44 */
extern AreaActionFadeSteps g_AreaActionFadeSteps; /* 0x80195F44 */
extern char                D_80195F90[];
/* The format that prints an ability row's cost. */
/* D_80195F98 */
extern char                g_UiListAbilityRowFormat[]; /* 0x80195F98 */
/* The format that prints the zenny reward. */
/* D_80195FBC */
extern char                g_GameRewardZennyFormat[]; /* 0x80195FBC */
/* D_80195FEC */
extern CellPaletteIndices  g_PartyDamageCellColors;
extern CellEffects         D_80195FF8;
/* D_80196014 */
extern PaletteColors       g_PartyDamageColors;
extern u8                  D_801F1294; /* 0x801F1294 */
extern u8                  D_801F12C8; /* 0x801F12C8 */
extern u8                  D_801F1318; /* 0x801F1318 */
extern u8                  D_801F13B8; /* 0x801F13B8 */
extern u8                  D_801F1444; /* 0x801F1444 */
extern u8                  D_801F1484; /* 0x801F1484 */
extern u8                  D_801F14C4; /* 0x801F14C4 */
extern u8                  D_801F14F8; /* 0x801F14F8 */
extern u8                  D_801F1538; /* 0x801F1538 */
extern u8                  D_801F1578; /* 0x801F1578 */
extern u8                  D_801F15B8; /* 0x801F15B8 */
extern u8                  D_801F15F8; /* 0x801F15F8 */
extern u8                  D_801F2C68; /* 0x801F2C68 */
extern u8                  D_801F2D28; /* 0x801F2D28 */
extern u8                  D_801F2D38; /* 0x801F2D38 */
extern u8                  D_801F2D48; /* 0x801F2D48 */
extern u8                  D_801F2D50; /* 0x801F2D50 */
extern u8                  D_801F2D70; /* 0x801F2D70 */
extern u8                  D_801F2DA0; /* 0x801F2DA0 */
extern u8                  D_801F2DA8; /* 0x801F2DA8 */
extern u8                  D_801F2DC4; /* 0x801F2DC4 */
extern u8                  D_801F2DE0; /* 0x801F2DE0 */
extern u8                  D_801F2E68; /* 0x801F2E68 */
extern u8                  D_801F2E94; /* 0x801F2E94 */
extern u8                  D_801F2F08; /* 0x801F2F08 */
extern u8                  D_801F2F34; /* 0x801F2F34 */
extern u8                  D_801F3140; /* 0x801F3140 */
extern u8                  D_801F3184; /* 0x801F3184 */
extern u8                  D_801F346C; /* 0x801F346C */
extern u8                  D_801F35BC; /* 0x801F35BC */
extern u8                  D_801F3A34; /* 0x801F3A34 */
extern u8                  D_801F3AA4; /* 0x801F3AA4 */
extern u8                  D_801F3ADC; /* 0x801F3ADC */
extern u8                  D_801F3B20; /* 0x801F3B20 */
extern u8                  D_801F3B9C; /* 0x801F3B9C */
extern u8                  D_801F3BEC; /* 0x801F3BEC */
extern u8                  D_801F3C9C; /* 0x801F3C9C */
extern u8                  D_801F3E00; /* 0x801F3E00 */
extern u8                  D_801F3F24; /* 0x801F3F24 */
extern u8                  D_801F3F48; /* 0x801F3F48 */
extern u8                  D_801F3F70; /* 0x801F3F70 */
extern u8                  D_801F3FF4; /* 0x801F3FF4 */
extern u8                  D_801F4168; /* 0x801F4168 */
extern u8                  D_801F4230; /* 0x801F4230 */
extern u8                  D_801F4250; /* 0x801F4250 */
extern u8                  D_801F4288; /* 0x801F4288 */
extern u8                  D_801F439C; /* 0x801F439C */
extern u8                  D_801F4594; /* 0x801F4594 */
extern u8                  D_801F45E4; /* 0x801F45E4 */
extern u8                  D_801F4674; /* 0x801F4674 */
extern u8                  D_801F4C48; /* 0x801F4C48 */
extern u8                  D_801F4CC8; /* 0x801F4CC8 */
extern u8                  D_801F4D04; /* 0x801F4D04 */
extern u8                  D_801F4D90; /* 0x801F4D90 */
extern u8                  D_801F4DA0; /* 0x801F4DA0 */
extern u8                  D_801F4DA4; /* 0x801F4DA4 */
extern u8                  D_801F4DD4; /* 0x801F4DD4 */
extern u8                  D_801F4DE0; /* 0x801F4DE0 */
extern u8                  D_801F5698; /* 0x801F5698 */
extern u8                  D_801F56E0; /* 0x801F56E0 */
extern u8                  D_801F5708; /* 0x801F5708 */
extern u8                  D_801F58F4; /* 0x801F58F4 */
extern u8                  D_801F591C; /* 0x801F591C */
extern u8                  D_801F599C; /* 0x801F599C */
extern u8                  D_801F5EBC; /* 0x801F5EBC */
extern u8                  D_801F64E8; /* 0x801F64E8 */
extern u8                  D_801F6D58; /* 0x801F6D58 */
extern u8                  D_801F6D80; /* 0x801F6D80 */
extern u8                  D_801F6D84; /* 0x801F6D84 */
extern u8                  D_801F6DBC; /* 0x801F6DBC */
extern u8                  D_801F6DE4; /* 0x801F6DE4 */
extern u8                  D_801F6DE8; /* 0x801F6DE8 */
extern u8                  D_801F8538; /* 0x801F8538 */
extern u8                  D_801F8570; /* 0x801F8570 */
extern u8                  D_801F8574; /* 0x801F8574 */
extern u8                  D_801F9728; /* 0x801F9728 */
extern u8                  D_801F9DC8; /* 0x801F9DC8 */
extern u8                  D_801F9DCC; /* 0x801F9DCC */
extern u8                  D_801FA1F0; /* 0x801FA1F0 */
extern u8                  D_801FA234; /* 0x801FA234 */
extern u8                  D_801FA23C; /* 0x801FA23C */
extern u8                  D_801FAEDC; /* 0x801FAEDC */
extern u8                  D_801FAF60; /* 0x801FAF60 */
extern u8                  D_801FAF84; /* 0x801FAF84 */
extern u8                  D_801FBF34; /* 0x801FBF34 */
extern u8                  D_801FBFC8; /* 0x801FBFC8 */
extern u8                  D_801FBFE8; /* 0x801FBFE8 */
extern u8                  D_801FC404; /* 0x801FC404 */
extern u8                  D_801FC488; /* 0x801FC488 */
extern u8                  D_801FC4BC; /* 0x801FC4BC */
extern u8                  D_801FC9FC; /* 0x801FC9FC */
extern u8                  D_801FCA88; /* 0x801FCA88 */
extern u8                  D_801FCFC0; /* 0x801FCFC0 */
extern u8                  D_801FD03C; /* 0x801FD03C */
extern u8                  D_801FD044; /* 0x801FD044 */
extern u8                  D_801FD1A4; /* 0x801FD1A4 */
extern u8                  D_801FD24C; /* 0x801FD24C */
extern u8                  D_801FD274; /* 0x801FD274 */
extern u8                  D_801FD5C8; /* 0x801FD5C8 */
extern u8                  D_801FD67C; /* 0x801FD67C */
extern u8                  D_801FD6A8; /* 0x801FD6A8 */
extern u8                  D_801FDDFC; /* 0x801FDDFC */
extern u8                  D_801FDFAC; /* 0x801FDFAC */
extern u8                  D_801FDFB4; /* 0x801FDFB4 */
extern u8                  D_801FE274; /* 0x801FE274 */
extern u8                  D_801FE288; /* 0x801FE288 */
extern u8                  D_801FE364; /* 0x801FE364 */
extern u8                  D_801FE370; /* 0x801FE370 */
extern u8                  D_801FE374; /* 0x801FE374 */
extern u8                  D_801FE3C4; /* 0x801FE3C4 */
extern u8                  D_801FE3CC; /* 0x801FE3CC */
extern u8                  D_801FE49C; /* 0x801FE49C */
extern u8                  D_801FE4C4; /* 0x801FE4C4 */
extern u8                  D_801FE4F4; /* 0x801FE4F4 */
extern u8                  D_801FE52C; /* 0x801FE52C */
extern u8                  D_801FE5F4; /* 0x801FE5F4 */
extern u8                  D_801FE724; /* 0x801FE724 */
extern u8                  D_801FE734; /* 0x801FE734 */
extern u8                  D_801FE880; /* 0x801FE880 */
extern u8                  D_801FE950; /* 0x801FE950 */
extern u8                  D_801FE9B0; /* 0x801FE9B0 */
extern u8                  D_801FE9C8; /* 0x801FE9C8 */
extern u8                  D_801FE9CC; /* 0x801FE9CC */
extern u8                  D_801FE9E8; /* 0x801FE9E8 */

void func_80117004(void);
void func_80117610(void);
void func_80117A30(void);
void func_80117BF4(void);
void func_8015A7E8(void);
/* The retail callers pass the id unnarrowed; the shared prototype narrows it. */
#define Actor_SpawnHelper ((s32 (*)())Actor_SpawnHelper)
void func_80164020();
void func_80167910(void);

void    func_80167E00(void);
void    func_801979D4(void);
void    func_801981B4(void);
void    func_80198F1C(void);
void    func_80199230(void);
void    func_80199398(void);
void    func_801999F8(MenuPanelTask* task);
void    WorldMap_StepWalk(void);
void    WorldMap_StepEntry(void);
void    WorldMap_StepFlock(void);
void    WorldMap_StepScript(void);
void    func_8019A330(void);
void    WorldMap_DrawClouds(void);
void    func_8019A3B8(void);
void    func_8019A3FC(void);
void    func_8019A53C(void);
void    func_8019A580(void);
void    func_8019A630(void);
void    func_8019A6AC(void);
void    func_8019A7D4(void);
void    func_8019A804(void);
void    func_8019A848(void);
void    func_8019B10C(void);
void    func_8019B150(void);
void    func_8019B1E8(void);
void    func_8019B284(void);
void    func_8019B704(void);
void    func_8019C620(void);
void    func_8019C664(void);
void    func_8019C794(void);
void    func_8019C910(void);
void    func_8019C954(void);
u8      func_8019CAB4(void);
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
void    func_8019F840(void);
void    func_8019F98C(void);
void    func_8019F9D0(void);
void    func_8019FF88(s32 entry_mode, s32 entry_index, s32 entry_flags);
void    func_801A02E8(void);
u8      func_801A0348(s16 map_x, s16 map_y);
void    func_801A0380(s16 x, s16 y, u16 type);
s32     func_801A17A0(u8* entry_record);
s32     func_801A1BC0(Actor* record);
s32     func_801A1C5C(s32 x, s32 y, s32 route, s32 unused);
s32     func_801A1ED8(s32 x, s32 y, s32 route, s32 unused);
s32     func_801A21EC(s32 x, s32 y);
s32     func_801A223C(s32 x, s32 y);
/* Kept (): retail callers load $a0 in the jal delay slot (`addiu a0,s0,116`) and the callee never reads it; with (void)
 * that instruction is dropped (Area_SetXFixed) or the frame shrinks by 8 bytes (Actor_RunRoute). */
void    func_801A27C4(Actor* entity);
void    func_801A2AE4(Actor* entity, u8 route_flag);
void    func_801A3080(Actor* actor, u8 facing);
void    func_801A3648(void);
void    func_801A386C(void);
s8      func_801A79A4(s32 handler_x, s32 handler_y);
s32     func_801A8714(void);
s8      func_801A8728(s32 entry_x, s32 entry_y);
bool    func_801A8A98(s32 candidate_x, s32 candidate_y);
s8      func_801A8B84(s32 handler_x, s32 handler_y);
void    func_801ABEE0(void);
VECTOR* func_801ABF30(VECTOR* out, s32 sel, s32 selector_type);
void    func_801AC0A0(s8 tuning_delta);
bool    func_801AC33C(s32 ease_in, s32 distance);
void    func_801AC768(ScriptState* cursor_state, s32 mode_byte, s32 value_18, s32 value_1C, s32 extra_value);
void    func_801AC9D0(void);
void    func_801ACA14(void);
void    func_801ACAC0(void);
void    func_801ACBC4(void);
void    func_801ACC08(void);
void    func_801ACCD8(void);
s8      func_801ADC98(void);
/* func_801AF270 */
/* func_801AF494 */

void  func_801B016C(void);
void  func_801B0320(void);
void  func_801B036C(void);
void  func_801B0568(void);
void  func_801B0C88(void);
void  func_801B0DA0(void);
void  func_801B13BC(void);
void  func_801B146C(void);
void  func_801B21E8(void);
void  func_801B29BC(void);
void  func_801B2A70(void);
void  func_801B2AB4(void);
void  func_801B2B6C(void);
void  func_801B2C38(void);
void  func_801B2D90(void);
void  func_801B2DDC(void);
void  func_801B2FC8(void);
void  func_801B315C(void);
void  func_801B31F0(void);
void  func_801B3690(void);
void  func_801B371C(void);
void  func_801B3768(void);
void  func_801B3A3C(void);
void  func_801B3BFC(void);
s32   func_801B4150(void);
s32   func_801B43D0(s32 x, s32 y, s32 dir);
u8    func_801B4494(u8 wanted_code);
u8    func_801B44DC(u8 wanted_code);
u8    func_801B4D7C(u8 wanted_code);
bool  func_801B544C(void);
void* func_801B5C54(void);
void  func_801B60DC(s32 actor_index);
bool  func_801B6258(void);
void  func_801B6418(void);
/* No prototype: the retail callers pass leftover register values the callee ignores. */
bool  func_801B6470();
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
/* No prototype: the retail caller passes a leftover register value the callee ignores. */
bool  func_801BB1B8();
s32   func_801BB2B8(s32 x0, s32 y0, s32 x1, s32 y1);
bool  func_801BB6F0(s32 command);
s32   func_801BB760(s32 x, s32 y);
s32   func_801BB7B0(s32 selector);
bool  func_801BB934(s32 first_index, s32 second_index, s8 route_value, s32 expected_value);
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
bool  func_801BD938(void);
void  func_801BDBC4(void);
s16   func_801BDCF8(s32 x, s32 y);
void  func_801BE574(s32 count, u8* ids);
void  func_801BE710(GameReset* record);
void  func_801BEBB0(void);
void  func_801BFF9C(u32 work_type, u32 work_index, u32 work_mode);
void  func_801C05AC(void);
void  func_801C0758(s32 x, s32 y, u8 type);
s32   func_801C090C(s32 anchor_x, s32 anchor_y, s32 anchor_index);
void  func_801C0A68(void);
void  func_801C0AB4(void);
void  func_801C0CDC(void);
void  func_801C0D34(void);
void  func_801C0D54(void);
s32   func_801C0E48(void);
s32   func_801C0F9C(u8 source_row);
/* func_801C16B8 */
void  func_801C1840(void);
void  func_801C1E88(s32 key, s32* counter);
void  func_801C1F4C(s32 key);
void  func_801C2018(void);
void  func_801C22D8(void);
bool  func_801C27E0(s8 tuning_delta);
bool  func_801C2894(s8 tuning_delta);
s32   func_801C2AAC(void);
s32   func_801C2B4C(void);
void  func_801C3154(void);
void  func_801C3204(void);
s32   func_801C364C(s32 wanted_code, s32 cell_code, s32 find_facing);
bool  func_801C3790(s32 mode_byte);
bool  func_801C37DC(s32 mode_byte);
void  func_801C3828(void);
u8    func_801C3A18(s32 pos_x, s32 pos_y, u8 wanted_code, u8 mask_cells);
s32   func_801C3B78(s32 pos_x, s32 pos_y, s32 wanted_code, s32 mask_cells);
bool  func_801C3E80(s32 pos_x, s32 pos_y, s32 probe_flag);
s32   func_801C4040(s32 pos_x, s32 pos_y, s16 probe_range);
s32   func_801C41D0(s32 pos_x, s32 pos_y, s16 probe_range);
u8    func_801C476C(s32 pos_x, s32 pos_y, u8 wanted_code, u8 mask_cells);
u8    func_801C48FC(s32 pos_x, s32 pos_y, u8 wanted_code, u8 mask_cells);
void  func_801C57F4(void);
void  func_801C5830(void);
void  func_801C5838(void);
void  func_801C5874(void);
void  func_801C5BB8(void);
void  func_801C5C7C(void);
void  func_801C5CB4(void);
void  func_801C5D68(void);
bool  func_801C6658(s32 table_index, s32 table_slot, s32 entry_index, s32 selection);
s32   func_801C6888(s32 entity_index);
s32   func_801C69C8(s32 record_index);
bool  func_801C6DCC(void);
bool  func_801C6EE0(s32 entry_count, s32 pos_x, s32 pos_y, s32 reach);
bool  func_801C7064(s32 x, s32 y, s32 reach, s32 height);
s16   func_801C7188(s16 value);
s32   func_801C71AC(s32 delta);
u16*  func_801C71C4(u16* out, s32 pos_x, s32 pos_y, s32 view_height);
bool  func_801C7498(s32 from_x, s32 from_y, s32 to_x, s32 to_y, u8 reach, u8 other_reach);
s32   func_801C7518(s32 pos_x, s32 pos_y, s32 reach);
bool  func_801C7608(s16 x0, s16 y0, s16 x1, s16 y1);
s32   func_801C7824(s16 from_x, s16 from_y, s16 to_x, s16 to_y);
void  func_801CF5A8(void);
void  func_801CF650(void);
void  func_801CF694(void);
void  func_801CF878(void);
void  func_801CF8BC(void);
void  func_801CFA30(void);
void  func_801CFA74(void);
void  func_801CFAB8(void);
void  func_801CFAFC(void);
void  func_801CFC2C(void);
void  func_801CFC70(void);
void  func_801CFCF8(void);
void  func_801CFD3C(void);
void  func_801CFE54(void);
void  func_801CFE98(void);
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
void  func_801F2C18(void);
void  func_801F2C1C(void);
void  func_801F2C30(void);
void  func_801F2C34(void);
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
void  func_801F3740(void);
void  func_801F3764(void);
void  func_801F3798(void);
void  func_801F37B0(void);
void  func_801F37D0(void);
void  func_801F37E4(void);
void  func_801F37EC(void);
s32   func_801F3868();
void  func_801F389C(void);
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
void  func_801F3FF8(void);
void  func_801F4034(void);
void  func_801F4038(void);
void  func_801F40C0(void);
void  func_801F40E4(void);
s32   func_801F4108(void);
void  func_801F410C(void);
s32   func_801F4140(void);
void  func_801F4158(void);
void  func_801F4164(void);
void  func_801F4178(void);
void  func_801F41A0(void);
void  func_801F41A8(void);
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
s32   func_801F4CC4(s32, s32);
s32   func_801F4CD0();
void  func_801F4CD8(void);
void  func_801F4CDC(void);
void  func_801F4D14(void);
void  func_801F4D9C(void);
s32   func_801F4DF8(void);
void  func_801F4F00(void);
void  func_801F4F60(void);
void  func_801F4F9C(void);
s32   func_801F4FA4(s32, s32);
void  func_801F502C(void);
void  func_801F50F0(void);
void  func_801F5130(void);
s32   func_801F5208(s32, s32);
void  func_801F529C(void);
void  func_801F52C8(void);
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
    SYS_ThreadWait(1U);
    SYS_ThreadWait(1U);
    g_EmiStreamFlags = 0x20;
    EMI_ArchiveLoadFamily(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    while (EMI_IsReady() == 0) {
        SYS_ThreadWait(1U);
    }
    UI_ModeSet(3U);
    if (WINDOW_EFFECT_BUSY()) {
        do {
            Area_RunLoadingFrame();
            SYS_ThreadWait(1U);
        } while (WINDOW_EFFECT_BUSY());
    }
    g_GameEntryState    = 2;
    g_GameEntrySubstate = 0;
    g_GameStateIndex    = GAME_REQUEST_IDLE;
    Area_RunFrame();
}

/* Adds step moves to the actor's move counter when bit 0 of g_EncounterSteps changed since the last actor update; with bit 1 set it sets the move timer while the counter is not 0. */
static inline s32 Game_AddStepByFlag(s32 step, Actor* actor, s32 value_b, u8 flag_bits) {
    s32 bit0;
    s32 flags;
    u8  value;
    u8* work;

    bit0 = flag_bits & 1;
    if (bit0 != 0) {
        if ((g_ScenarioState.unk_08 & 0x1) != (g_EncounterSteps & 0x1)) {
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
            work      = TASK(u8);
            work[9]   = (u8)(0x20 / (s32)(value_b & BYTE_MASK));
            work      = TASK(u8);
            work[0xA] = (u8)(work[9] >> 1);
        }
    }
    return 0;
}

/* Roll the field action's find; a miss leaves the action to end. */
static inline void AreaAction_Roll(s32 actor_slot) {
    u32 choice;

    choice = (u32)RANDOM_MASK(0xF);
    if ((TASK(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
        Script_DispatchSelector((u8)((g_Game.members[0].facing ^ 4) & 7));
    }
    g_Game.flags |= GAME_FLAG_SCRIPT_ACTIVE;
    if ((g_CurrentActor->unk_94 & 0x80) == 0) {
        g_CurrentActor->unk_94 |= 0x80;
        switch ((u8)choice) {
            case 0:
            case 1:
            case 2:
            case 3:
                Actor_SpawnSceneActor(1);
                TASK(Actor)->unk_04 = 3;
                break;
            case 4:
            case 5:
            case 6:
                Actor_SpawnSceneActor(1);
                Party_AddZenny(2, 0);
                Actor_SpawnToss((u8)((s32)(-(((s32)GAME_WORK_AREA_PTR - (s32)g_Actors) * 0xD79435E5)) >> 3));
                TASK(Actor)->unk_04 = 1;
                break;
            case 7:
                Actor_SpawnSceneActor(1);
                Party_AddZenny(5, 0);
                Actor_SpawnToss((u8)((s32)(-(((s32)GAME_WORK_AREA_PTR - (s32)g_Actors) * 0xD79435E5)) >> 3));
                TASK(Actor)->unk_04 = 2;
                break;
            default:
                Actor_SpawnSceneActor(actor_slot);
                TASK(Actor)->unk_04 = 3;
                break;
        }
    } else {
        if (choice >= 8) {
            Actor_SpawnSceneActor(1);
        } else {
            Actor_SpawnSceneActor(actor_slot);
        }
        TASK(Actor)->unk_04 = 3;
    }
}

s32 func_801B1B2C(s32 x, s32 y, s32 probe_type, s32 flags);

s32 func_801B1C18(s32 x, s32 y, s32 mode);

u8 func_801B4BE4(u8 mode, u8 code);

void func_801B690C(void);

s32 func_801BA278(u8 cell0, u8 cell1, u8 cell2, u8 cell3, u8 cell4);

void func_801BBCCC(s16 from_x, s16 from_y, s16 to_x, s16 to_y);

#endif
