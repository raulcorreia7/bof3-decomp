#ifndef SYSTEM_GAMEUI_H
#define SYSTEM_GAMEUI_H

#include "types.h"
#include "game/character.h"

/* Script interpreter state; the same 12-byte record in each handler. */
typedef struct ScriptState {
    u8  flag_00;
    u8  unk_01;
    u8  count_02;
    u8  pad_03;
    u8  unk_04; /* 0x04 */
    u8  unk_05; /* 0x05 */
    u8  pad_06;
    u8  unk_07;
    s16 unk_08; /* 0x08 */
    u16 cursor;
} ScriptState;

ASSERT_SIZE(ScriptState, 0x0C);
ASSERT_OFFSET(ScriptState, unk_04, 0x04);
ASSERT_OFFSET(ScriptState, unk_05, 0x05);
ASSERT_OFFSET(ScriptState, unk_07, 0x07);
ASSERT_OFFSET(ScriptState, unk_08, 0x08);
ASSERT_OFFSET(ScriptState, cursor, 0x0A);

/* The front-end step record behind g_MessageState: func_8015102C walks the timer,
 * phase, cursor and flag fields; the other units read only its first byte. */
typedef struct FrontendStep {
    u8  state_00;     /* 0x00 */
    u8  selection_01; /* 0x01 */
    u8  pad_02[2];    /* 0x02 */
    u16 flags_04;     /* 0x04 */
    u8  count_06;     /* 0x06 */
    u8  pad_07[5];    /* 0x07 */
    s32 entry_0C;     /* 0x0C */
    s32 cursor_10;    /* 0x10 */
    u8  pad_14[4];    /* 0x14 */
    u8  phase_18;     /* 0x18 */
    u8  index_19;     /* 0x19 */
    u8  pad_1A[0x0E]; /* 0x1A */
    u16 scroll_28;    /* 0x28 */
} FrontendStep;

ASSERT_SIZE(FrontendStep, 0x2C);
ASSERT_OFFSET(FrontendStep, state_00, 0x00);
ASSERT_OFFSET(FrontendStep, count_06, 0x06);
ASSERT_OFFSET(FrontendStep, cursor_10, 0x10);
ASSERT_OFFSET(FrontendStep, scroll_28, 0x28);

typedef struct AreaDrawState {
    u8 actor_count;
    u8 unk_01;
    u8 flags;
    u8 unk_03;
} AreaDrawState;

ASSERT_SIZE(AreaDrawState, 4);
ASSERT_OFFSET(AreaDrawState, actor_count, 0x00);
ASSERT_OFFSET(AreaDrawState, flags, 0x02);

extern AreaDrawState g_AreaDrawState;

/* retail addresses */

/* The menu header bar every screen draws at the top: geometry in pixels, y at its resting row. */
#define MENU_HEADER_X           20
#define MENU_HEADER_Y           18
#define MENU_HEADER_WIDTH       280
#define MENU_HEADER_HEIGHT      19
#define MENU_HEADER_SHORT_WIDTH 72

/* Draw the menu header bar at its resting row in the player's window style. */
#define MENU_DRAW_HEADER()      Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle)

/* Where the shop and save screens put their prompt line, the Zenny window and the save slot list. */
#define MENU_PROMPT_X           28
#define MENU_PROMPT_Y           22
#define MENU_ZENNY_WINDOW_X     98
#define MENU_ZENNY_WINDOW_Y     40
#define SAVE_SLOTS_X            32
#define SAVE_SLOTS_Y            48

/* The rows of the equip stat window, top to bottom. */
typedef enum EquipStatRow {
    EQUIP_STAT_ROW_POWER   = 0,
    EQUIP_STAT_ROW_DEFENSE = 1,
    EQUIP_STAT_ROW_AGILITY = 2,
} EquipStatRow;

/* A message table (the wiki calls this a message bank): u16 byte offsets from
 * the table start, then the records. An area loads its table at
 * AREA_MESSAGE_TABLE; a message id is the offset index. */
typedef struct MessageTable {
    u16 offsets[1];
} MessageTable;

#define AREA_MESSAGE_TABLE            ((MessageTable*)0x80010000)
#define MESSAGE_TABLE_TEXT(table, id) ((u8*)(table) + (table)->offsets[id])

/* The most bytes of a text record UI_DrawText draws. */
#define TEXT_LENGTH_MAX               0xFF

/* Sizes of the framed windows the menu overlays draw with UI_DrawWindow. */
#define MENU_CHARACTER_WINDOW_WIDTH   125
#define MENU_CHARACTER_WINDOW_HEIGHT  48
#define MENU_EQUIP_STAT_WINDOW_WIDTH  108
#define MENU_EQUIP_STAT_WINDOW_HEIGHT 48
#define MENU_EQUIP_STAT_ROWS          3  /* power, defense and agility */
#define MENU_EQUIP_STAT_INSET         3  /* window offset from the panel origin */
#define MENU_EQUIP_STAT_VALUE_X       44 /* stat value column, from the panel origin */
#define MENU_EQUIP_STAT_VALUE_Y       8  /* first stat value row */
#define MENU_EQUIP_STAT_LABEL_X       5
#define MENU_EQUIP_STAT_LABEL_Y       6
#define MENU_EQUIP_STAT_ROW_HEIGHT    15
#define MENU_EQUIP_STAT_PORTRAIT_X    70
#define MENU_EQUIP_STAT_PORTRAIT_Y    2
#define MENU_EQUIP_STAT_LABEL_SIZE    6 /* bytes per label of g_MenuEquipStatLabels */
#define MENU_ZENNY_WINDOW_WIDTH       101
#define MENU_ZENNY_WINDOW_HEIGHT      16
#define MENU_PLAY_TIME_WINDOW_WIDTH   85
#define MENU_PLAY_TIME_WINDOW_HEIGHT  16
#define MENU_INVENTORY_WINDOW_WIDTH   153
#define MENU_INVENTORY_WINDOW_HEIGHT  154
#define MENU_INVENTORY_TOP_HEIGHT     20
#define MENU_INVENTORY_BOTTOM_HEIGHT  8
#define MENU_STAT_WINDOW_WIDTH        148
#define MENU_STAT_WINDOW_HEIGHT       45
#define MENU_SAVE_SLOT_WINDOW_WIDTH   200
#define MENU_SAVE_SLOT_WINDOW_HEIGHT  48
#define MENU_FORMATION_WINDOW_WIDTH   69
#define MENU_FORMATION_WINDOW_HEIGHT  48

/* The requested message id: 0xFFFF means no message. ResourceRequestMessage
 * stores a message index in the slot and Message_StartRequest reads the slot as that
 * index; the player's menu choice at g_MessageChoice decides the index. */
#define MESSAGE_NONE                  0xFFFF
#define MESSAGE_REQUEST_CLEAR()       (g_MessageRequest = MESSAGE_NONE)

/* The player's menu choice at 0x801490C7 (MenuState.selection_index): zero
 * while no answer is selected, nonzero once the player picks one. */
/* An alias byte of g_MessageWindow.selection_index: the area overlays read it as a plain byte, and the
 * member access changes their code. */
/* D_801490C7 */
extern s8 g_MessageChoice;
#define MENU_SELECTION_IDLE()            (g_MessageChoice == 0)
#define MENU_SELECTION_ARMED()           (g_MessageChoice != 0)

/* The repeatable buttons of a pad mask: PAD_GetRepeatedButtons sees the held keys
 * filtered to the buttons that repeat. */
#define INPUT_DIRECTIONAL                (PADLup | PADLright | PADLdown | PADLleft)
#define INPUT_ACTION_BUTTONS             (PADRup | PADRdown | PADRleft | PADRright | PADL1 | PADL2 | PADR1 | PADR2 | PADstart | PADselect)
#define INPUT_REPEATED(pressed, buttons) (PAD_GetRepeatedButtons((pressed) & (buttons)))

/* The window effect has finished (idle) or is still running (busy). */
#define WINDOW_EFFECT_IDLE()             (g_UiWindowEffectBusy == 0)
#define WINDOW_EFFECT_BUSY()             (g_UiWindowEffectBusy != 0)

/* A countdown timer expires when the decrement reaches zero. */
#define TIMER_EXPIRED(timer)             (--(timer) == 0)
/* EMI_GetArchiveId packs the loaded archive's index (low 7 bits) with
 * the family-0 (PL) marker bit; readers mask the index off. */
#define EMI_LOADED_INDEX_MASK            0x7F
#define EMI_LOADED_PL                    0x80

/* The window and frontend system: a state machine (game state, window state,
 * substate, timer and the fade/phase words below) drives text boxes, choices
 * and transitions. The game, shop, start-menu and scenario overlays read these
 * words; the shared calls resolve resources, decode pad input and queue cues.
 * Format: @source: wiki:data/text. */

/* The work-list draw flags in D_8014832E: the draw pass sorts the work table
 * by its key, then walks the records the set bits ask for. */
typedef enum AreaDrawFlags {
    AREA_DRAW_SORTED_RECORDS          = 1 << 0,
    AREA_DRAW_NEGATIVE_DEPTH          = 1 << 1,
    AREA_DRAW_CELL_LAYERS             = 1 << 2,
    AREA_DRAW_APPEND_ACTOR_PRIMITIVES = 1 << 3,
    AREA_DRAW_APPEND_AREA_PRIMITIVES  = 1 << 4,
    AREA_DRAW_ALL_FLAGS               = AREA_DRAW_SORTED_RECORDS | AREA_DRAW_NEGATIVE_DEPTH | AREA_DRAW_CELL_LAYERS | AREA_DRAW_APPEND_ACTOR_PRIMITIVES | AREA_DRAW_APPEND_AREA_PRIMITIVES,
} AreaDrawFlags;

/* The frontend channel word D_801490A4: the window script machine, the
 * selection passes and the shop/start overlays share it. */
typedef enum FrontendFlags {
    FRONTEND_FLAG_TIMER_ACTIVE    = 1 << 0,
    FRONTEND_FLAG_CONFIRM         = 1 << 1,
    FRONTEND_FLAG_SELECTION       = 1 << 2,
    FRONTEND_FLAG_REQUEST_PENDING = 1 << 3,
    FRONTEND_FLAG_NO_INPUT_WAIT   = 1 << 4,
    FRONTEND_FLAG_ADVANCE_REQUEST = 1 << 6,
    FRONTEND_FLAG_MODE_LATCH      = 1 << 7,
    FRONTEND_FLAG_FORCE_STEP      = 1 << 8,
} FrontendFlags;

extern s32 D_80143B4C;
extern s32 D_80143B50;

/* The request code that field code writes to g_GameStateIndex. Game_UpdateField reads it after the per-frame
 * update and enters the state named in the comment. Codes 0 to 9 are all it handles. */
typedef enum GameRequest {
    GAME_REQUEST_IDLE         = 0,
    GAME_REQUEST_MENU         = 1, /* state 3 */
    GAME_REQUEST_MESSAGE      = 2, /* state 4, the message window wait */
    GAME_REQUEST_BATTLE       = 3, /* state 5 */
    GAME_REQUEST_CAMERA_LOOK  = 4, /* state 6, Game_UpdateCameraLook: free camera orbit */
    GAME_REQUEST_AREA_CHANGE  = 5, /* state 1 */
    GAME_REQUEST_SHOP         = 6, /* state 7 */
    GAME_REQUEST_ABILITY_MENU = 7, /* state 9; scena06 writes it */
    GAME_REQUEST_STATUS_MENU  = 8, /* state 10; scena11 writes it */
    GAME_REQUEST_SCENE_CAMERA = 9, /* state 11 */
} GameRequest;

/* The rows of g_GameStates, the full-screen modes Game_UpdateMain runs. */
typedef enum GameEntryState {
    GAME_STATE_NEW_GAME     = 0,
    GAME_STATE_AREA_LOAD    = 1,
    GAME_STATE_FIELD        = 2,
    GAME_STATE_MENU         = 3,
    GAME_STATE_MESSAGE      = 4,
    GAME_STATE_BATTLE       = 5,
    GAME_STATE_CAMERA_LOOK  = 6,
    GAME_STATE_SHOP         = 7,
    GAME_STATE_FISHING      = 8,
    GAME_STATE_ABILITY_MENU = 9,
    GAME_STATE_STATUS_MENU  = 10,
    GAME_STATE_SCENE_CAMERA = 11,
} GameEntryState;

/* The main state machine index, a GameEntryState value. */
/* D_80143B90 */
extern u16 g_GameEntryState;
/* The request code, a GameRequest value. */
/* D_80143BB0 */
extern u8  g_GameStateIndex;
/* D_80143F02. A unit that reads it as volatile (etc/game/00) defines
 * GAME_REQUEST_FLAGS_VOLATILE before its first include. */
#ifdef GAME_REQUEST_FLAGS_VOLATILE
extern volatile u8 g_GameRequestFlags;
#else
extern u8 g_GameRequestFlags;
#endif
/* Map kind bit of g_GameRequestFlags: the area runs the world map. */
#define GAME_REQUEST_FLAG_WORLD_MAP 0x01
/* Not volatile: the qualifier changes the generated order in the scena00 drawer. */
/* D_80143C40 */
extern u16 g_UiWindowEffectBusy;

/* The screen effects UI_SetMode starts, by index into g_UiLocalModes. Each
 * effect comes as an out/in pair: out takes the screen to black or white, in
 * brings it back. The indexes not named here run camera spins and distance
 * resets. */
typedef enum UiMode {
    UI_MODE_FADE_OUT       = 0,
    UI_MODE_FADE_IN        = 1,
    UI_MODE_FAST_FADE_OUT  = 2,
    UI_MODE_FAST_FADE_IN   = 3,
    UI_MODE_SLOW_FADE_OUT  = 4,
    UI_MODE_SLOW_FADE_IN   = 5,
    UI_MODE_LAYER_FADE_OUT = 6,
    UI_MODE_LAYER_FADE_IN  = 7,
    UI_MODE_WHITE_OUT      = 8,
    UI_MODE_WHITE_IN       = 9,
    UI_MODE_LONG_FADE_OUT  = 13,
    UI_MODE_LONG_FADE_IN   = 14,
    UI_MODE_LONG_WHITE_OUT = 15,
    UI_MODE_LONG_WHITE_IN  = 16,
} UiMode;

/* D_80143C90 */
extern u16 g_UiLocalMode;
/* D_80143F1E */
extern u8  g_GameEntryMode;
/* D_80145024 */
/* D_80145024 */
extern u8  g_EmiLoadedCharacterIndex;
extern u8  D_80145025;
/* D_8014502C */
extern u32 g_BattleCount;
extern u16 D_80145A7C;
/* D_80145AA4 */
extern u16 g_InputHeld;

/* Pad masks, one slot per game action. The config screen remaps the six
 * labelled Speak, Move, Action, Menu, View and Change; Confirm and Cancel are
 * read by the menu-like states. Each game state names the slots it reads. */
typedef enum InputSlot {
    INPUT_SLOT_SPEAK,
    INPUT_SLOT_MOVE,
    INPUT_SLOT_MENU,
    INPUT_SLOT_VIEW,
    INPUT_SLOT_CHANGE,
    INPUT_SLOT_UNUSED, /* only the config screen touches it */
    INPUT_SLOT_ACTION,
    INPUT_SLOT_CONFIRM,
    INPUT_SLOT_CANCEL,
    INPUT_SLOT_COUNT
} InputSlot;

/* Field: X talks to people, examines objects and opens chests; the run button
 * walks or runs by the Auto Run option; the triangle starts the lead
 * character's personal action. */
#define FIELD_INPUT_INTERACT        INPUT_SLOT_SPEAK
#define FIELD_INPUT_RUN             INPUT_SLOT_MOVE
#define FIELD_INPUT_MENU            INPUT_SLOT_MENU
#define FIELD_INPUT_VIEW            INPUT_SLOT_VIEW
#define FIELD_INPUT_SWITCH_LEADER   INPUT_SLOT_CHANGE
#define FIELD_INPUT_PERSONAL_ACTION INPUT_SLOT_ACTION

/* World map: X enters the location under the party; the triangle shows a short
 * text guide to the current location; the areas that run the world map variant
 * read the run and view buttons too. */
#define WORLD_INPUT_ENTER           INPUT_SLOT_SPEAK
#define WORLD_INPUT_RUN             INPUT_SLOT_MOVE
#define WORLD_INPUT_VIEW            INPUT_SLOT_VIEW
#define WORLD_INPUT_LOCATION_GUIDE  INPUT_SLOT_ACTION

/* Message window: holding the talk button prints text at the fast step. */
#define MESSAGE_INPUT_SPEED_UP      INPUT_SLOT_SPEAK

#define MENU_INPUT_CONFIRM          INPUT_SLOT_CONFIRM
#define MENU_INPUT_CANCEL           INPUT_SLOT_CANCEL
#define BATTLE_INPUT_CONFIRM        INPUT_SLOT_CONFIRM
#define BATTLE_INPUT_CANCEL         INPUT_SLOT_CANCEL
#define FISHING_INPUT_CAST          INPUT_SLOT_CONFIRM
#define FISHING_INPUT_CANCEL        INPUT_SLOT_CANCEL
extern u16          g_InputMasks[INPUT_SLOT_COUNT];
extern u16          D_80145ACE;
extern u8           D_80145AD0;
extern u8           D_80145AE5;
extern u16          D_801481DA;
extern u16          D_801481E2;
extern u16          D_801481E4;
extern u16          D_801481E6;
/* D_80148210 */
extern ScriptState* g_ScriptState;
extern u8           D_8014832C;
extern u8           D_8014832D;
/* D_8014832E */
extern u8           g_AreaDrawFlags;
extern u8           D_8014833B;
extern u8           D_8014833D;
extern u8           D_8014833E;
extern u8           D_8014833F;
extern u16          D_80148344;
extern u16          D_80148346;
extern u8           D_80148354;
extern u8           D_80148357;
extern u8           D_8014835D;
extern u8           D_80148379;
extern u8           D_8014837A;
extern u8           D_8014839D;
extern u8           D_8014839E;
extern u16          D_801483A0;
extern u16          D_801483A2;
extern u8           D_801483A6;
extern u8           D_801483A8;
extern u8           D_801483A9;
extern u8           D_801483C1;
extern u8           D_801483C2;
/* D_801483C3 */
extern volatile u8  g_BattleMessageState;
extern u16          D_801483C4;
extern u16          D_801483C6;
extern u8           D_801483CA;
extern u8           D_801483CC;
extern u8           D_801483CD;
extern u8           D_80148408;
extern u8           D_80148409;
extern u8           D_8014840A;
extern u8           D_8014840B;
extern u16          D_8014840C;
extern u16          D_8014840E;
extern u8           D_8014842C;
/* The SPU has 24 voices; the sound system has 7 SEP/VAB slots. */
#define SND_VOICE_COUNT 24
#define SND_SLOT_COUNT  7

extern s8           g_SndVabIds[SND_SLOT_COUNT];
extern s8           g_SndVoiceVolume[SND_VOICE_COUNT];
extern u8           D_80148FE0[SND_VOICE_COUNT];
/* D_801490A0 */
extern FrontendStep g_MessageState;
/* D_801490A2 */
extern u8           g_MessageChoiceMode;
/* Shared selection counter read by etc/game/00 and etc/shop/00. */
/* D_801490A4 */
extern volatile u16 g_UiWindowChannel;
/* D_801490A6 */
extern u8           g_MessageStateTimer[];

/* D_801490A8 */
extern u16      g_MessageRequest;
/* D_801490AA */
extern u16      g_MessageChoiceTimer;
extern u8       D_801490CF[];
/* D_80181D98 */
extern const u8 s_LoaderRecordBytes[168];
extern u8       D_80181D99;
/* 0x80181EBA / 0x80181EBB: byte tables the selection paths read with a 4-byte
 * row stride. */
/* D_80181EBA */
extern const u8 g_SelectionCues[];
/* D_80181EBB */
extern const u8 g_SelectionSequences[];

/* Resource and pad-input helpers the overlays call: resolve a resource id to
 * its data pointer, look up a group choice's resource id, and decode the
 * repeatable buttons of an input mask.  The resource id is taken whole: the
 * retail callee shifts the incoming $a0 logically (srl $v0,$a0,12 at
 * 0x801502D8) and masks it itself (andi $a0,$a0,0x3FFF at 0x801502E4), and
 * the eight callers pass a 32-bit word. */
/* Game-front dispatchers: mode, layout bank, and cue entry points. */

#endif
