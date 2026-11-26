#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "character.h"
#include "encoding.h"
#include "fairy.h"
#include "gene.h"
#include "item.h"
#include "enemy.h"
#include "records.h"
#include "script.h"
#include "spawn.h"
#include "ability.h"
#include "text.h"
#include "gfx/vram.h"
#include "common/callback.h"
#include "types.h"

/* Rows in the palette fade table g_PaletteFades. */
#define PALETTE_FADE_COUNT 32

/* `PaletteFade.flags` bit 0 marks a row in use (@source: write:GFX_PaletteAllocFade@0x8019651C,
 * read:GFX_PaletteFreeFade@0x80196670). */
typedef enum PaletteFadeFlags {
    PALETTE_FADE_ACTIVE = 1 << 0,
} PaletteFadeFlags;

/* The fields of a task record (actor, battler, effect) that a palette fade reads and restores. */
typedef struct PaletteOwner {
    u8 pad_00[0x24];
    u8 flags; /* +0x24 bit 2 is cleared when a fade that flagged its row with 0x80 frees */
    u8 pad_25[0x2];
    u8 saved_byte;   /* +0x27 restored from PaletteFade.saved_byte when the fade frees */
    u8 palette_type; /* +0x28 a PaletteType: how many palette cells the owner's fade covers */
} PaletteOwner;

ASSERT_OFFSET(PaletteOwner, palette_type, 0x28);

#define PALETTE_OWNER(record) ((PaletteOwner*)(record))

/* Largest value of one 5-bit colour channel of a palette cell. */
#define COLOR_CHANNEL_MAX     31

/* One 0xC-byte row of the palette fade table g_PaletteFades. */
typedef struct PaletteFade {
    u8            flags;      /* PaletteFadeFlags */
    u8            saved_byte; /* the target byte at +0x27, restored on free */
    ColorDelta8   offset;
    u8            table_index;
    u8            cell_index; /* the free palette cell GFX_PaletteMarkCells assigned */
    u8            unk_07;
    PaletteOwner* target; /* the record whose palette fades */
} PaletteFade;

ASSERT_OFFSET(PaletteFade, target, 0x08);
ASSERT_SIZE(PaletteFade, 0x0C);

/* One 4-byte step of a palette animation: the destination and source cell
 * columns, the cells to copy and the frames to hold. A step whose first byte is
 * GAME_NONE ends the list; its second byte is the step count back to the loop. */
typedef struct PaletteAnimationStep {
    u8 dst_column; /* 0x00 */
    u8 src_column; /* 0x01 */
    u8 count;      /* 0x02 */
    u8 frames;     /* 0x03 */
} PaletteAnimationStep;

ASSERT_SIZE(PaletteAnimationStep, 0x04);

/* One 0x10-byte slot of the palette animation table at g_PaletteAnimations; bit 0 of flags marks it in use. */
typedef struct GraphicsPaletteAnimation {
    u8                    flags;
    u8                    unk_01;
    u8                    unk_02;
    u8                    unk_03;
    u8*                   source_table;
    PaletteAnimationStep* current_entry;
    u8*                   owner;
} GraphicsPaletteAnimation;

ASSERT_SIZE(GraphicsPaletteAnimation, 0x10);

/* g_PaletteFades */
extern PaletteFade              g_PaletteFades[PALETTE_FADE_COUNT];
/* The palette animation slots. */
/* D_80145D94 */
extern GraphicsPaletteAnimation g_PaletteAnimations[8];

/* The game's area state at 0x80143F00: the area being run, the area to return to and the pending area request.
 * Game_EnterArea stores the current area, its cell type and the scroll target into last_*, and func_801B146C hands
 * them back to Game_RequestAreaChange; Game_RequestAreaChange stores the request fields in the order of its
 * arguments. The members keep their own globals (several images read them with a different width or volatile). */
typedef struct GameAreaState {
    /* 0x00 */ u16 area_id;
    /* 0x02 */ u8  request_flags;
    /* 0x03 */ u8  cell_type;
    /* 0x04 */ u16 last_area_id;
    /* 0x06 */ u16 last_cell_type;
    /* 0x08 */ u32 last_x;
    /* 0x0C */ u32 last_y;
    /* 0x10 */ u16 request_area_id;
    /* 0x12 */ u8  unk_12[2];
    /* 0x14 */ u32 request_x;
    /* 0x18 */ u32 request_y;
    /* 0x1C */ u8  request_facing;
    /* 0x1D */ u8  request_type;
    /* 0x1E */ u8  entry_mode;
    /* 0x1F */ u8  prev_selection;
} GameAreaState;

ASSERT_OFFSET(GameAreaState, request_flags, 0x02);
ASSERT_OFFSET(GameAreaState, last_area_id, 0x04);
ASSERT_OFFSET(GameAreaState, last_x, 0x08);
ASSERT_OFFSET(GameAreaState, last_y, 0x0C);
ASSERT_OFFSET(GameAreaState, request_area_id, 0x10);
ASSERT_OFFSET(GameAreaState, request_x, 0x14);
ASSERT_OFFSET(GameAreaState, request_y, 0x18);
ASSERT_OFFSET(GameAreaState, request_facing, 0x1C);
ASSERT_OFFSET(GameAreaState, request_type, 0x1D);
ASSERT_OFFSET(GameAreaState, entry_mode, 0x1E);
ASSERT_OFFSET(GameAreaState, prev_selection, 0x1F);
ASSERT_SIZE(GameAreaState, 0x20);

/* D_80143F00 */
extern GameAreaState g_GameArea;
/* D_80143F03: the members of g_GameArea that the area and scenario overlays read on their own */
extern u8            g_GameCellType;
/* D_80143F04 */
extern u16           g_GameLastAreaId;

/* GAME.EMI#0 exports: the frontend's data and entry points, in address order. */

/* D_80143F14 */
extern u32      g_GameEntryPosX;
/* D_80143F18 */
extern u32      g_GameEntryPosY;
/* D_80143F1F */
extern u8       g_GamePrevSelection;
/* D_80195FE0 */
extern u8       s_FairyConstructionThresholds[]; /* 0x80195FE0 */
/* Image-local data, in retail address order. */
/* D_801C7AC0 */
extern u8       s_PaletteFadeCounts[8];
/* D_801C7AC8 */
extern u8       s_PaletteFadeDivisors[8];
/* D_801C7AD0 */
extern u8       s_PaletteFadeScales[8];
/* D_801C7AD8 */
extern u8       s_PaletteFadeColorCounts[8];
/* D_801C7AE0 */
extern u8       s_PaletteFadeRowDivisors[8];
/* D_801C7AE8 */
extern u8       s_PaletteFadeStrides[16];
/* D_801C7AF8 */
extern u8       s_PaletteSlotDivisors[8];
/* D_801C7B00 */
extern u8       s_PaletteSlotStrides[8];
/* D_801C7B08 */
extern Callback g_GameCampMenuLoad[];
/* D_801C7B14 */
extern Callback g_GameModes[];
/* D_801C7B44 */
extern Callback g_GameMenuSteps[3];
/* D_801C7B50 */
extern u8       s_DirectionJitters[4];
/* D_801C7B54 */
extern Callback g_GameBattleSteps[8];
/* D_801C7B7C */
extern Callback g_GameShopSteps[3];
/* D_801C7B88 */
extern Callback g_GameFishingSteps[4];
/* D_801C7B98 */
extern Callback g_MenuAbilityOpen[3];
/* D_801C7BA4 */
extern Callback g_GameShisuSteps[3];
/* D_801C7BB0 */
extern Callback g_GameSceneCameraSteps[3];
/* D_801C7BBC */
extern u8       s_MenuLine1Run[12];
/* D_801C7BC8 */
extern u8       s_MenuLine2Run[12];
/* D_801C7BD4 */
extern u8       s_MenuLine1FlagRun[12];
/* D_801C7BE0 */
extern u8       s_MenuLine2FlagRun[12];
/* D_801C7BEC */
extern Callback g_UiPanelModes[5];
/* D_801C7C00 */
extern Callback g_UiPanelSteps[3];
/* D_801C7C0C */
extern Callback g_MenuOptionSteps[3];
/* D_801C7C18 */
extern Callback g_MenuActionSteps[3];
/* D_801C7C24 */
extern Callback g_UiPanelTaskSteps[4];
extern char     g_ItemCategoryLabels[5][8];
extern u8*      g_ItemCategoryLabelPointers[5];
/* D_801C7C70 */
extern Callback g_ActorTypes[187];
extern u8       D_801C7F74[];
extern Callback D_801C8090[3];
/* D_801C809C */
extern u8       s_SceneHandlerIds[8];
extern Callback D_801C80A4[6];
extern Callback D_801C80BC[3];
extern Callback D_801C80C8[6];
/* D_801C80E0 */
extern Callback g_CameraAnglePanModes[3];
/* D_801C80EC */
extern Callback g_CameraZoomPanModes[3];
/* D_801C80F8 */
extern Callback g_ActorTossModes[4];

/* Launch of a tossed actor: initial vertical speed and the gravity pulling it back, both 16.16. */
typedef struct ActorToss {
    s32 vz;
    s32 gravity;
} ActorToss;

extern ActorToss s_ActorTossArcs[3];
extern Callback  D_801C8120[3];

/* D_801C812C */
/* The modes of a rock actor (ACTOR_TYPE_ROCK), selected by header.mode. */
typedef enum ActorRockMode {
    ACTOR_ROCK_MODE_START,  /* blocks its cell and selects its sprite */
    ACTOR_ROCK_MODE_WAIT,   /* waits for a kick */
    ACTOR_ROCK_MODE_ROLL,   /* rolls on with the kick's velocity, slowed by friction */
    ACTOR_ROCK_MODE_SETTLE, /* moves on to the target cell edge and lands */
    ACTOR_ROCK_MODE_END,    /* grows and disappears */
    ACTOR_ROCK_MODE_REST,   /* rests, then waits again */
    ACTOR_ROCK_MODE_COUNT
} ActorRockMode;

extern Callback           g_ActorRockModes[ACTOR_ROCK_MODE_COUNT];
extern Callback           D_801C8144[4];
extern Callback           D_801C8154[4];
extern Callback           D_801C8164[6];
extern Callback           D_801C817C[4];
/* D_801C818C */
extern u8                 s_AreaSeIds[12];
extern Callback           D_801C8198[2];
extern Callback           D_801C81A0[4];
extern Callback           D_801C81B0[2];
extern Callback           D_801C81B8[2];
extern Callback           D_801C81C0[3];
extern Callback           D_801C81CC[4];
extern Callback           g_TaskModes[105];
/* D_801C8380 */
extern u8                 s_EntityModes[4];
extern u16                D_801C8384[28];
/* D_801C8404 */
extern u8                 s_EntityRouteIndices[8][4];
extern u16                g_ActorFacingAngles[8];
extern u16                D_801C842A[];
extern Callback           D_801C8434[2];
extern Callback           D_801C843C[2];
/* D_801C8444 */
extern u8                 s_ScriptOpcodeLengths[16];
/* D_801C84A4 */
extern Callback           g_SceneSteps[2];
/* D_801C84AC */
extern u8                 s_EventFlagsReset[16];
/* D_801C84BC */
extern Callback           g_SceneEvents[64];
/* D_801C85BC */
extern u8                 s_ScenarioStateStepArgs[8];
/* D_801C85C4 */
extern Callback           g_WorldMapGuides[11];
/* D_801C85F0 */
extern SceneActorCallback g_SceneObjects[66];
/* D_801C87D8 */
extern u8                 s_TalkMessageIds[36];
/* D_801C87FC */
extern u8                 s_ActorScriptLengths[256];
extern Callback           D_801C88FC[2];
extern Callback           D_801C8904[2];
/* D_801C8938 */
extern u8                 g_FindZenny[4];
extern u8                 D_801CA624[232];
extern u8                 D_801CA71E[];
/* D_801CD050 */
extern u8                 s_ItemSpriteIds[16];
/* D_801CD060 */
extern u8                 s_ItemIconIds[12];
/* D_801CD06C */
extern u8                 s_RouteStepScratch[32];
/* D_801CD08C */
extern s8                 s_EntityPlacementOffsets[32];
extern s8                 D_801CD08D[];
/* D_801CD0AC */
extern Callback           g_PartyLeaderModes[15];
extern Callback           D_801CD0E8[3];
extern u16                D_801CD0F4[4];
/* D_801CD0FC */
extern Callback           g_GameLeaderSwitchSteps[5];
extern Callback           D_801CD110[2];
extern Callback           D_801CD118[2];
extern Callback           D_801CD120[4];
/* D_801CD130 */
extern Callback           g_AreaClimbSteps[4];
/* D_801CD140 */
extern Callback           g_AreaClimbMountSteps[5];
/* D_801CD154 */
extern Callback           g_AreaClimbDismountSteps[4];
/* D_801CD164 */
extern Callback           g_PersonalActions[19];
extern Callback           D_801CD1B0[2];
/* D_801CD1B8 */
extern u8                 s_EncounterStepThresholds[16];
extern u8                 D_801CD1B9[];
/* D_801CD1C8 */
extern u8                 s_MenuBattlerTypes[4];
/* D_801CD1CC */
extern u8                 s_RouteSlotAlternates[12];
extern Callback           D_801CD1D8[19];
extern u8                 D_801CD226[];
/* D_801CD29C */
extern u8                 s_AreaScenePositions[8];
/* D_801CD2A4 */
extern u8                 s_AreaCellTypes[12];
/* D_801CD2B0 */
extern Callback           g_PartyMoveSteps[PARTY_MOVE_STEP_COUNT];
/* D_801CD2D4 */
extern Callback           g_PartyScriptWalkSteps[6];
/* D_801CD2EC */
extern Callback           g_PartyFadeInSteps[2];
/* D_801CD2F4 */
extern Callback           g_PartyJumpSteps[PARTY_JUMP_STEP_COUNT];
/* D_801CD308 */
extern Callback           g_PartyLadderTransits[PARTY_LADDER_TRANSIT_COUNT];
/* D_801CD310 */
extern Callback           g_PartyLadderUpSteps[8];
/* D_801CD330 */
extern Callback           g_PartyLadderDownSteps[10];
/* D_801CD358 */
extern Callback           g_PartyWalkTransitSteps[5];
/* D_801CD36C */
extern Callback           g_PartyCellWalkSteps[2];
/* D_801CD374 */
extern Callback           g_PartyFallThroughSteps[2];
/* D_801CD37C */
extern Callback           g_PartyFloorDamageSteps[2];
extern u8                 D_801CD384[128];
/* D_801CD404 */
extern Callback           g_PartyFollowerModes[15];
extern Callback           D_801CD440[2];
/* D_801CD448 */
extern Callback           g_AreaClimbFollowerSteps[4];
/* D_801CD458 */
/* D_801CD460 */
extern u8                 s_BattleStartOffsets[12][2];
/* D_801CD478 */
extern u8                 s_RouteIndexByMode[4];
extern s32                D_801CD47C[8];
extern s32                D_801CD480;
extern Callback           D_801CD49C[4];
extern Callback*          D_801CD4C0[20];
extern Callback*          D_801CD510[20];
/* D_801CD560 */
extern u8                 s_AreaProbeCellCodes[8];
extern Callback           D_801CD568[2];
extern Callback           D_801CD570[5];
extern u8                 D_801CD584[56];
/* D_801CD5BC */
/* D_801CD770 */
extern u8                 s_EncounterSpawnChances[8];
/* D_801CD78C */
extern u8                 s_BattleModeRecords[224];
extern u8                 D_801CD78D[];
extern u8                 D_801CD78F[];
extern u16                g_BossArchiveSlots[42];
extern u8                 D_801CD8C0;
extern u8                 D_801CD8C4;
extern u8                 D_801CD8C8;
extern s32                D_801CD8CC;
extern u8                 D_801CD8D0[116];
/* D_801CD950 */
extern u8                 s_PartySlotOrder[4];
extern s32                D_801CD954;

/* The game system: the records, text and script formats the frontend and every
 * overlay read. A game source reaches it through game.h. */

/* GAME.EMI entry points that other overlays call at their fixed address:
 * emi/etc/game/00 (GAME.EMI#0) is resident beside the field overlays. */

/* Finds the first unused slot in the entry table at 0x80143FC8; the retail
 * callee reads no argument and zeroes $a0 before the scan. */
/* Kept (): retail callers load $a0 in the jal delay slot (`addiu a0,s0,116`; `move a0,s4` in Actor_MovementStep) and
 * the callee never reads it; with (void) that instruction is dropped. */
/* Selects a route direction away from the work record's current direction:
 * returns -1 when the current index lies in the selector's four-step span,
 * otherwise 1. */
/* Awards the proximity reward: sound SE, area request, owned money. */
/* Returns a field record slot holding a body near (pos_x, pos_y), or -1. */

#endif
