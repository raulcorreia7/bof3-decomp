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

/* retail addresses */

/* The requested message id: 0xFFFF means no message. ResourceRequestMessage
 * stores a message index in the slot and Message_StartRequest reads the slot as that
 * index; the player's menu choice at D_801490C7 decides the index. */
#define MESSAGE_NONE            0xFFFF
#define MESSAGE_REQUEST_CLEAR() (g_MessageRequest = MESSAGE_NONE)

/* The player's menu choice at 0x801490C7 (MenuState.selection_index): zero
 * while no answer is selected, nonzero once the player picks one. */
#define MENU_SELECTION_IDLE()   (D_801490C7 == 0)
#define MENU_SELECTION_ARMED()  (D_801490C7 != 0)

/* The repeatable buttons of a pad mask: INPUT_GetRepeatedButtons sees the held keys
 * filtered to the buttons that repeat. */
#define INPUT_DIRECTIONAL       (PADLup | PADLright | PADLdown | PADLleft)
#define INPUT_ACTION_BUTTONS                                                                          \
    (PADRup | PADRdown | PADRleft | PADRright | PADL1 | PADL2 | PADR1 | PADR2 | PADstart | PADselect)
#define INPUT_REPEATED(pressed, buttons) (INPUT_GetRepeatedButtons((pressed) & (buttons)))

/* The window effect has finished (idle) or is still running (busy). */
#define WINDOW_EFFECT_IDLE()             (g_UiWindowEffectBusy == 0)
#define WINDOW_EFFECT_BUSY()             (g_UiWindowEffectBusy != 0)

/* A countdown timer expires when the decrement reaches zero. */
#define TIMER_EXPIRED(timer)             (--(timer) == 0)
/* EMI_StreamFamilyArchive packs the loaded archive's index (low 7 bits) with
 * the family-0 (PL) marker bit; readers mask the index off. */
#define EMI_LOADED_INDEX_MASK            0x7F
#define EMI_LOADED_PL                    0x80

/* The window and frontend system: a state machine (game state, window state,
 * substate, timer and the fade/phase words below) drives text boxes, choices
 * and transitions. The game, shop, start-menu and scenario overlays read these
 * words; the shared calls resolve resources, decode pad input and queue cues.
 * Evidence: the writer/reader addresses beside the names and
 * @source: wiki:data/text. */

/* The work-list draw flags in D_8014832E: the draw pass sorts the work table
 * by its key, then walks the records the set bits ask for. */
typedef enum AreaDrawFlags {
    AREA_DRAW_SORTED_RECORDS          = 1 << 0,
    AREA_DRAW_NEGATIVE_DEPTH          = 1 << 1,
    AREA_DRAW_CELL_LAYERS             = 1 << 2,
    AREA_DRAW_APPEND_ACTOR_PRIMITIVES = 1 << 3,
    AREA_DRAW_APPEND_AREA_PRIMITIVES  = 1 << 4,
    AREA_DRAW_ALL_FLAGS               = AREA_DRAW_SORTED_RECORDS | AREA_DRAW_NEGATIVE_DEPTH | AREA_DRAW_CELL_LAYERS |
        AREA_DRAW_APPEND_ACTOR_PRIMITIVES | AREA_DRAW_APPEND_AREA_PRIMITIVES,
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

/* The request code that field code writes to g_GameStateIndex. Game_RunFieldState reads it after the per-frame
 * update and enters the state named in the comment. Codes 0 to 9 are all it handles. */
typedef enum GameRequest {
    GAME_REQUEST_IDLE         = 0,
    GAME_REQUEST_MENU         = 1, /* state 3 */
    GAME_REQUEST_MESSAGE      = 2, /* state 4, the message window wait */
    GAME_REQUEST_BATTLE       = 3, /* state 5 */
    GAME_REQUEST_CAMERA_LOOK  = 4, /* state 6, Game_RunCameraLookState: free camera orbit */
    GAME_REQUEST_AREA_CHANGE  = 5, /* state 1 */
    GAME_REQUEST_SHOP         = 6, /* state 7 */
    GAME_REQUEST_ABILITY_MENU = 7, /* state 9; scena06 writes it */
    GAME_REQUEST_STATUS_MENU  = 8, /* state 10; scena11 writes it */
    GAME_REQUEST_SCENE_CAMERA = 9, /* state 11 */
} GameRequest;

/* The main state machine index. */
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
/* Not volatile: the qualifier changes the generated order in the scena00 drawer. */
/* D_80143C40 */
extern u16          g_UiWindowEffectBusy;
/* D_80143C90 */
extern u16          g_UiLocalMode;
/* D_80143F1E */
extern u8           g_GameEntryMode;
/* D_80145024 */
/* D_80145024 */
extern u8           g_EmiLoadedCharacterIndex;
extern u8           D_80145025;
/* D_8014502C */
extern u32          g_BattleCount;
extern u16          D_80145A7C;
/* D_80145AA4 */
extern u16          g_InputHeld;
/* D_80145AB4 */
extern u16          g_InputMasks;
extern u16          D_80145AB6;
extern u16          D_80145AB8;
extern u16          D_80145ABC;
extern u16          D_80145AC0;
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
extern u8           D_8014833C[][0x24];
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
extern s8           D_80148FB0;
extern s8           D_80148FB1;
extern s8           D_80148FB2;
extern s8           D_80148FB3;
extern s8           D_80148FB4;
extern s8           D_80148FB5;
extern s8           D_80148FB6;
extern s8           D_80148FC1;
extern s8           D_80148FC2;
extern s8           D_80148FC3;
extern s8           D_80148FC4;
extern s8           D_80148FC5;
extern s8           D_80148FC6;
extern s8           D_80148FC8;
extern u8           D_80148FE0;
extern u8           D_801490A2;
/* Shared selection counter read by etc/game/00 and etc/shop/00. */
/* D_801490A4 */
extern volatile u16 g_UiWindowChannel;
/* Area request slot shared by the area024 and area027 overlays. */
/* D_801490A8 */
extern u16          g_MessageRequest;
extern u16          D_801490AA;
extern u8           D_801490CF[];
/* D_80181D98 */
extern const u8     s_LoaderRecordBytes[168];
extern u8           D_80181D99;
/* 0x80181EBA / 0x80181EBB: byte tables the selection paths read with a 4-byte
 * row stride. */
/* D_80181EBA */
extern const u8     g_SelectionCues[];
extern const u8     D_80181EBB[];

/* Game-front dispatchers: mode, layout bank, and cue entry points. */
/* func_8014ECAC */
void             UI_SetMode(u16 local_mode);
/* func_8014FC90 */
extern const u8* UI_DrawTextString(s16 x, s16 y, s32 flags, u8 count, const u8* text);
/* func_80150224 */
void             Message_StartAreaMessage(s32 message_index);
/* func_80150284 */
extern void      Resource_RequestArea(s32 request_id);
/* func_801502D0 */
u8*              Resource_GetText(u32 resource_id);
/* func_80158DB8 */
s32              Menu_ArmPanelTask(u8 menu_id, u8 mode);
/* func_8015B580 */
void             SYS_SetFlag(void* bits, u8 bit_index);
/* func_8015B5A8 */
extern void      SYS_ClearFlag(void* bits, u8 bit_index);
/* func_80161808 */
void             SND_SetBankLayout(u32 layout_bank);
/* func_80161C20 */
void             SND_PlayBgm(s32 selection_id, s32 cue_level, s32 cue_shape);
/* func_80161CD0 */
void             SND_FadeOutBgm(u8 selection_id, s32 cue_level, s32 cue_shape);
/* func_80164A44 */
void             Char_RebuildStats(Character* record);
/* func_801666C8 */
s32              Item_GetDescription(s32 group_index, s32 choice_entry);
/* func_80196070 */
void             Actor_Clear(void);
/* func_80196F78 */
void             Game_RunCampMenuLoop(void);
/* Resource and pad-input helpers the overlays call: resolve a resource id to
 * its data pointer, look up a group choice's resource id, and decode the
 * repeatable buttons of an input mask.  The resource id is taken whole: the
 * retail callee shifts the incoming $a0 logically (srl $v0,$a0,12 at
 * 0x801502D8) and masks it itself (andi $a0,$a0,0x3FFF at 0x801502E4), and
 * the eight callers pass a 32-bit word. */
s32              INPUT_GetRepeatedButtons(s32 button_mask);

#endif
