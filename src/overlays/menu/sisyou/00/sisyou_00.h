#ifndef OVERLAY_ETC_SISYOU_00_H
#define OVERLAY_ETC_SISYOU_00_H

/* The master and skill menu overlay's local declarations: the stock rows, the
 * sprite atlas, the message ids and the step handlers. Only this image includes
 * the file. */

#include "game/character.h"
#include "battle/ram.h"
#include "shared/etc.h"
#include <stdio.h>

/* The main-executable text bank at 0x80010000: the message id indexes its u16
 * record offsets and func_8014F800 draws the record. */
#define MASTER_MENU_TEXT_BANK         0x80010000

#define MASTER_MENU_HEAD_SIZE         0x18
#define MASTER_MENU_FMT_A_SIZE        4
#define MASTER_MENU_FMT_BC_SIZE       8
#define MASTER_MENU_ATLAS_RECORD_SIZE 4
#define MASTER_MENU_ATLAS_COUNT       12
#define MASTER_SKILL_SIZE             2
#define MASTER_MENU_SPRITE_BANK_SIZE  0x90
#define MASTER_MENU_SPRITE_090_SIZE   0x2C
#define MASTER_MENU_SPRITE_0BC_SIZE   0x0C
#define MASTER_MENU_SPRITE_0C8_SIZE   0x18
#define MASTER_MENU_LABEL_SIZE        4
#define MASTER_MENU_LABEL_LONG_SIZE   8
#define MASTER_MENU_MESSAGE_ID_COUNT  18
#define MASTER_MENU_STEP_COUNT        7
#define MASTER_MENU_SUBSTEP_COUNT     2
#define SISYOU_SUB2_HANDLER_COUNT     6
#define SISYOU_SUB3_HANDLER_COUNT     9
#define SISYOU_SUB4_HANDLER_COUNT     9
#define SISYOU_SUB5_HANDLER_COUNT     3
#define MASTER_MENU_VALUE_COUNT       20
#define MASTER_MENU_STATE_COUNT       4

/* The party screen layout, in pixels: the party rows, the stat panel, the
 * selection box, the header frame and the header text. The four drawers
 * (func_801D10AC, func_801D0DD4, func_801D12FC, func_801D0C88) place them. */
#define MASTER_MENU_ROW_X             17
#define MASTER_MENU_ROW_TOP           62
#define MASTER_MENU_ROW_PITCH         54
#define MASTER_MENU_STAT_PANEL_X      137
#define MASTER_MENU_SELECT_WIDTH      272
#define MASTER_MENU_SELECT_HEIGHT     52
#define MASTER_MENU_FRAME_X           20
#define MASTER_MENU_FRAME_Y           16
#define MASTER_MENU_FRAME_WIDTH       280
#define MASTER_MENU_FRAME_HEIGHT      19
#define MASTER_MENU_TEXT_X            27
#define MASTER_MENU_TEXT_Y            19

/* Retail reads the status halfword at +0x0C of a party record as a word. */
#define STATUS_WORD(record)           (*(u32*)&(record)->status)

/* The payload prologue at 0x801D0C00: the type-0 EMI loader compares the
 * first word with the archive TOC's cached first word; the rest are the three
 * sprintf formats the shop panels pass as D_801D0C04/D_801D0C08/D_801D0C10. */
typedef struct MasterMenuHead {
    u32  id;                             /* 0x00; TOC cached first word, 0x1F */
    char fmt_a[MASTER_MENU_FMT_A_SIZE];  /* 0x04 "%3d" */
    char fmt_b[MASTER_MENU_FMT_BC_SIZE]; /* 0x08 "%3d/   " */
    char fmt_c[MASTER_MENU_FMT_BC_SIZE]; /* 0x10 "   /%3d" */
} MasterMenuHead;

ASSERT_SIZE(MasterMenuHead, MASTER_MENU_HEAD_SIZE);

/* Panel atlas record: u, v, clut x, clut y (Menu_DrawPortrait, 4-byte stride). */
typedef struct MenuPortraitSprite {
    u8 u;
    u8 v;
    u8 clut_x;
    u8 clut_y;
} MenuPortraitSprite;

ASSERT_SIZE(MenuPortraitSprite, MASTER_MENU_ATLAS_RECORD_SIZE);
ASSERT_OFFSET(MenuPortraitSprite, clut_x, 0x02);
ASSERT_OFFSET(MenuPortraitSprite, clut_y, 0x03);

/* Master skill record: the level byte D_801D4088 compares and the ability
 * byte D_801D4089 reads, both at index (i + master * 0xC). */
typedef struct MasterSkill {
    u8 level;
    u8 ability;
} MasterSkill;

ASSERT_SIZE(MasterSkill, MASTER_SKILL_SIZE);
ASSERT_OFFSET(MasterSkill, ability, 0x01);

/* One master's six signed stat bonuses: the hp, ap, power, defense, agility
 * and intellect bonus the master grants. */
typedef struct SisyouMasterStats {
    s8 hp;
    s8 ap;
    s8 power;
    s8 defense;
    s8 agility;
    s8 intellect;
} SisyouMasterStats;

ASSERT_SIZE(SisyouMasterStats, MASTER_STATS_STRIDE);
ASSERT_OFFSET(SisyouMasterStats, power, 0x02);
ASSERT_OFFSET(SisyouMasterStats, defense, 0x03);
ASSERT_OFFSET(SisyouMasterStats, agility, 0x04);
ASSERT_OFFSET(SisyouMasterStats, intellect, 0x05);

/* The shared stock tables are read as rows (2-D) in the master walkers and
 * as raw bytes in the stock-row printers. */
typedef union MasterStock {
    u8 bytes[1];
    u8 rows[1][BATTLE_PARTY_STRIDE];
} MasterStock;

/* Retail addresses. */

/* Data, in address order. */
extern MasterStock        D_80145FCC;
extern u8                 D_801D0C04[];
extern u8                 D_801D0C08[];
extern u8                 D_801D0C10[];
extern u8                 D_801D3F58[MASTER_MENU_SPRITE_BANK_SIZE];
extern u8                 D_801D3FE8[MASTER_MENU_SPRITE_090_SIZE];
extern u8                 D_801D4014[MASTER_MENU_SPRITE_0BC_SIZE];
extern u8                 D_801D4020[MASTER_MENU_SPRITE_0C8_SIZE];
extern char               D_801D4038[MASTER_MENU_LABEL_SIZE];      /* "Pwr" */
extern char               D_801D403C[MASTER_MENU_LABEL_SIZE];      /* "Def" */
extern char               D_801D4040[MASTER_MENU_LABEL_SIZE];      /* "Int" */
extern char               D_801D4044[MASTER_MENU_LABEL_SIZE];      /* "Agl" */
extern char               D_801D4048[MASTER_MENU_LABEL_LONG_SIZE]; /* "Pois" */
extern char               D_801D4050[MASTER_MENU_LABEL_LONG_SIZE]; /* "Conf" */
extern MenuPortraitSprite D_801D4058[MASTER_MENU_ATLAS_COUNT];
extern MasterSkill        D_801D4088[MASTER_COUNT][MASTER_SKILL_COUNT];
extern SisyouMasterStats  D_801D4154[MASTER_COUNT];
extern u8                 D_801D41BA;
extern u8                 D_801D41BB;
extern u16                D_801D41BC[MASTER_MENU_MESSAGE_ID_COUNT];
extern Callback           D_801D4204[SISYOU_SUB2_HANDLER_COUNT];
extern Callback           D_801D421C[SISYOU_SUB3_HANDLER_COUNT];
extern Callback           D_801D4240[SISYOU_SUB4_HANDLER_COUNT];
extern Callback           D_801D4264[SISYOU_SUB5_HANDLER_COUNT];
extern u8                 D_801D4270[MASTER_MENU_VALUE_COUNT];
extern u8                 g_MasterBannerLock;
extern u8                 g_MasterStep;
extern u8                 g_MasterSubStep;
extern u8                 g_MasterPanelLock;
extern u8                 D_801D4288;
extern u8                 g_MasterScrollOffset;
extern u8                 g_MasterMenuCursor;
extern Callback           g_MasterMenuFuncs[MASTER_MENU_STEP_COUNT];
extern Callback           g_MasterMenuSubFuncs[MASTER_MENU_SUBSTEP_COUNT];

/* Functions, in address order. */
bool Party_AddItem(s32 category, u8 item, u8 amount, s32 unused);
void UI_DrawSpriteRun(s16 arg0, s16 arg1, const u8* arg2, u8 arg3);
void Master_ResetPanel(void);
void func_801D0C48(void);
void func_801D0C88(void);
void func_801D0DD4(s32 message_id, s32 confirm);
void func_801D10AC(u32 message_id);
void Master_DrawPartyRow(u16 x, u16 y, u8 entry, u8 icon);
void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style);
void Menu_DrawPortrait(u16 x, u16 y, u8 sprite_id, u8 shade);
void Menu_DrawIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color);
void Master_DispatchMenu(void);
void func_801D2614(void);
void func_801D2688(void);
void func_801D26C4(void);
void func_801D2738(void);
void func_801D278C(void);
void func_801D27C8(void);
void func_801D282C(void);
void func_801D28B0(void);
void func_801D29C8(void);
void func_801D2A4C(void);
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
void Master_ApplyMaster(void);
void MenuDrawSelectionBox(s32 x, s32 y, s32 width, s32 height, u8 color, u8 mask);

/* Request the active master's message id plus the handler's panel offset. The
 * caller passes the state pointer so its saved register matches the original. */
static inline void MasterMenuRequestMasterMessage(u8* state, s32 offset) {
    if (*state == GAME_REQUEST_MESSAGE) {
        return;
    }
    Message_StartAreaMessage((s16)(D_801D41BC[D_801448ED] + offset));
    *state = GAME_REQUEST_MESSAGE;
    g_MasterSubStep++;
}

/* Request the active master's panel message once, then latch the UI state. */
static inline void MasterMenuRunActivePanelMessage(u8* state) {
    if (*state == GAME_REQUEST_MESSAGE) {
        return;
    }
    Message_StartAreaMessage((s16)(D_801D41BC[D_801448ED] + 4));
    *state       = 2;
    g_MasterStep = 6;
}

#endif
