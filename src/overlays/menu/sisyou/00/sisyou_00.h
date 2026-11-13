#ifndef OVERLAY_ETC_SISYOU_00_H
#define OVERLAY_ETC_SISYOU_00_H

/* The master and skill menu overlay's local declarations: the stock rows, the
 * sprite atlas, the message ids and the step handlers. Only this image includes
 * the file. */

#include "game/character.h"
#include "battle/records.h"
#include "shared/etc.h"
#include <stdio.h>

#define MASTER_MENU_HEAD_SIZE        0x18
#define MASTER_MENU_FMT_A_SIZE       4
#define MASTER_MENU_FMT_BC_SIZE      8
#define MASTER_MENU_ATLAS_COUNT      12
#define MASTER_SKILL_SIZE            2
#define MASTER_MENU_SPRITE_BANK_SIZE 0x90
#define MASTER_MENU_SPRITE_090_SIZE  0x2C
#define MASTER_MENU_SPRITE_0BC_SIZE  0x0C
#define MASTER_MENU_SPRITE_0C8_SIZE  0x18
#define MASTER_MENU_LABEL_SIZE       4
#define MASTER_MENU_LABEL_LONG_SIZE  8
#define MASTER_MENU_MESSAGE_ID_COUNT 18

/* The messages of one master, as offsets from the master's entry of g_MenuMasterMessageIds. */
enum MasterMessage {
    MASTER_MESSAGE_GREETING = 0,
    MASTER_MESSAGE_FAREWELL = 4,
    MASTER_MESSAGE_OFFER,
    MASTER_MESSAGE_OFFER_REPLY,
    MASTER_MESSAGE_ALL_ENROLLED,
    MASTER_MESSAGE_ALL_ENROLLED_QUERY,
    MASTER_MESSAGE_NO_PUPILS,
    MASTER_MESSAGE_ENROLLED,
    MASTER_MESSAGE_ENROLLED_MORE_QUERY,
    MASTER_MESSAGE_DISMISSED,
    MASTER_MESSAGE_DISMISSED_MORE_QUERY,
    MASTER_MESSAGE_SKILL_LEARNED,
};

/* The absolute message Deis answers with while the party cannot meet her yet. */
#define MASTER_MESSAGE_DEIS_UNAVAILABLE 0x2E
#define MASTER_MENU_STEP_COUNT          7
#define MASTER_MENU_SUBSTEP_COUNT       2
#define SISYOU_SUB2_HANDLER_COUNT       6
#define SISYOU_SUB3_HANDLER_COUNT       9
#define SISYOU_SUB4_HANDLER_COUNT       9
#define SISYOU_SUB5_HANDLER_COUNT       3
#define MASTER_ACTOR_MODE_COUNT         20
#define MASTER_MENU_STATE_COUNT         4

/* The party screen layout, in pixels: the party rows, the stat panel, the
 * selection box, the header frame and the header text. The four drawers
 * (func_801D10AC, func_801D0DD4, func_801D12FC, func_801D0C88) place them. */
#define MASTER_MENU_ROW_X               17
#define MASTER_MENU_ROW_TOP             62
#define MASTER_MENU_ROW_PITCH           54
#define MASTER_MENU_STAT_PANEL_X        137
#define MASTER_MENU_SELECT_WIDTH        272
#define MASTER_MENU_SELECT_HEIGHT       52
#define MASTER_MENU_FRAME_X             20
#define MASTER_MENU_FRAME_Y             16
#define MASTER_MENU_FRAME_WIDTH         280
#define MASTER_MENU_FRAME_HEIGHT        19
#define MASTER_MENU_TEXT_X              27
#define MASTER_MENU_TEXT_Y              19

/* The payload prologue at 0x801D0C00: the type-0 EMI loader compares the
 * first word with the archive TOC's cached first word; the rest are the three
 * sprintf formats the shop panels pass as D_801D0C04/g_MenuCurrentValueFormat/g_MenuMaxValueFormat. */
typedef struct MasterMenuHead {
    u32  id;                             /* 0x00; TOC cached first word, 0x1F */
    char fmt_a[MASTER_MENU_FMT_A_SIZE];  /* 0x04 "%3d" */
    char fmt_b[MASTER_MENU_FMT_BC_SIZE]; /* 0x08 "%3d/   " */
    char fmt_c[MASTER_MENU_FMT_BC_SIZE]; /* 0x10 "   /%3d" */
} MasterMenuHead;

ASSERT_SIZE(MasterMenuHead, MASTER_MENU_HEAD_SIZE);

/* Master skill record: one level and the ability it teaches. */
typedef struct MasterSkill {
    u8 level;
    u8 ability;
} MasterSkill;

/* The empty slot: MASTER_SKILL_EMPTY as a pair. */
#define MASTER_SKILL_NONE {99, 0xFF}

ASSERT_SIZE(MasterSkill, MASTER_SKILL_SIZE);
ASSERT_OFFSET(MasterSkill, ability, 0x01);

/* Retail addresses. */

/* Data, in address order. */
extern u8                 D_801D0C04[];
/* D_801D0C08 */
extern u8                 g_MenuCurrentValueFormat[];
/* D_801D0C10 */
extern u8                 g_MenuMaxValueFormat[];
extern u8                 D_801D3F58[MASTER_MENU_SPRITE_BANK_SIZE];
extern u8                 D_801D3FE8[MASTER_MENU_SPRITE_090_SIZE];
extern u8                 D_801D4014[MASTER_MENU_SPRITE_0BC_SIZE];
extern u8                 D_801D4020[MASTER_MENU_SPRITE_0C8_SIZE];
/* D_801D4044 */
extern u8                 g_MenuLabelAgility[MASTER_MENU_LABEL_SIZE];
/* D_801D4048 */
extern char               g_MenuLabelPoison[MASTER_MENU_LABEL_LONG_SIZE]; /* "Pois" */
/* D_801D4050 */
extern char               g_MenuLabelConfusion[MASTER_MENU_LABEL_LONG_SIZE]; /* "Conf" */
/* D_801D4058 */
extern MenuPortraitSprite g_MenuPortraitAtlas[MASTER_MENU_ATLAS_COUNT];
/* D_801D4088 */
extern MasterSkill        g_MenuMasterSkills[MASTER_COUNT][MASTER_SKILL_COUNT];
/* D_801D4154 */
extern MasterStats        g_MenuMasterStats[MASTER_COUNT];
extern u8                 D_801D41BA;
extern u8                 D_801D41BB;
/* D_801D41BC */
extern s16                g_MenuMasterMessageIds[MASTER_MENU_MESSAGE_ID_COUNT];
/* D_801D4204 */
extern Callback           g_MenuMasterStep2Funcs[SISYOU_SUB2_HANDLER_COUNT];
/* D_801D421C */
extern Callback           g_MenuMasterStep3Funcs[SISYOU_SUB3_HANDLER_COUNT];
/* D_801D4240 */
extern Callback           g_MenuMasterStep4Funcs[SISYOU_SUB4_HANDLER_COUNT];
/* D_801D4264 */
extern Callback           g_MenuMasterStep5Funcs[SISYOU_SUB5_HANDLER_COUNT];
/* D_801D4270 */
extern u8                 g_MenuMasterActorModes[MASTER_ACTOR_MODE_COUNT];
extern u8                 g_MenuMasterBannerLock;
extern u8                 g_MenuMasterStep;
extern u8                 g_MenuMasterSubStep;
extern u8                 g_MenuMasterPanelLock;
extern u8                 D_801D4288;
extern u8                 g_MenuMasterScrollOffset;
extern u8                 g_MenuMasterCursor;
extern Callback           g_MasterMenuStates[MASTER_MENU_STEP_COUNT];
extern Callback           g_MasterMenuSubFuncs[MASTER_MENU_SUBSTEP_COUNT];

/* Functions, in address order. */
bool Item_Add(s32 category, u8 item_id, u8 count, s32 unused);
void UI_DrawSpriteRun(s16 arg0, s16 arg1, const u8* arg2, u8 arg3);
void Menu_ResetMasterPanel(void);
void func_801D0C48(void);
void func_801D0C88(void);
void func_801D0DD4(s32 message_id, s32 confirm);
void func_801D10AC(u32 message_id);
void Menu_DrawMasterPartyRow(u16 x, u16 y, u8 entry, u8 icon);
void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style);
void Menu_DrawPortrait(u16 x, u16 y, u8 sprite_id, u8 shade);
void Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color);
void Menu_UpdateMaster(void);
void func_801D2614(void);
void func_801D2688(void);
void func_801D26C4(void);
void func_801D2738(void);
void func_801D278C(void);
void Master_StartOffer(void);
void func_801D282C(void);
void func_801D28B0(void);
void func_801D29C8(void);
void func_801D2A4C(void);
void Master_StartFarewell(void);
void func_801D2BE8(void);
void func_801D2C24(void);
void func_801D2C64(void);
void func_801D2CA4(void);
void func_801D30C4(void);
void func_801D3148(void);
void func_801D3258(void);
void func_801D32D4(void);
void func_801D3350(void);
void func_801D3390(void);
void func_801D3714(void);
void func_801D3798(void);
void func_801D38A8(void);
void func_801D3924(void);
void func_801D3960(void);
void func_801D39CC(u32 entry);
void func_801D3A24(void);
void func_801D3E70(void);
void Menu_ApplyMasterMode(void);
void Menu_DrawSelectionBox(s32 x, s32 y, s32 width, s32 height, u8 color, u8 mask);

/* Request the active master's message id plus the handler's panel offset. The
 * caller passes the state pointer so its saved register matches the original. */
static inline void MasterMenuRequestMasterMessage(u8* state, s32 offset) {
    if (*state == GAME_REQUEST_MESSAGE) {
        return;
    }
    Message_StartAreaMessage((s16)(g_MenuMasterMessageIds[g_SceneEventSelection] + offset));
    *state = GAME_REQUEST_MESSAGE;
    g_MenuMasterSubStep++;
}

/* Request the active master's panel message once, then latch the UI state. */
static inline void MasterMenuRunActivePanelMessage(u8* state) {
    if (*state == GAME_REQUEST_MESSAGE) {
        return;
    }
    Message_StartAreaMessage((s16)(g_MenuMasterMessageIds[g_SceneEventSelection] + MASTER_MESSAGE_FAREWELL));
    *state           = 2;
    g_MenuMasterStep = 6;
}

#endif
