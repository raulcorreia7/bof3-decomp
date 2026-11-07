#ifndef OVERLAY_ETC_SHISU_00_H
#define OVERLAY_ETC_SHISU_00_H

/* The etc/shisu/00 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"
#include <stdio.h>

#define g_SceneState (*(struct SceneState*)&g_SceneState)

extern u8            D_80148656;
extern OverlayHeader D_801D0C00;
extern char          g_MenuStatFormat[];
extern char          g_MenuZennyFormat[];
/* D_801D0C2C */
extern char          g_MenuNextExpBlank[];
extern char          g_MenuClockFormat[];
extern char          D_801D0D64[];
extern char          D_801D0D68[];
extern char          D_801D0D74[];
extern char          D_801D0D78[];
extern char          D_801D0D7C[];
/* Entries of the handler tables. */
#define MENU_STATUS_STEP_COUNT        5
#define MENU_STATUS_TASK_COUNT        7
#define MENU_STATUS_STEP1_COUNT       2
#define MENU_STATUS_STEP2_COUNT       3
#define MENU_STATUS_STEP2_SUB2_COUNT  5
#define MENU_STATUS_STEP3_COUNT       2
#define MENU_STATUS_TASK2_STATE_COUNT 3
#define MENU_STATUS_TASK3_STATE_COUNT 3

/* The overlay's step and sub-step handler pools; the tables are views into one
 * callback run, selected by the shared menu step byte. */
/* D_801D96DC */
extern Callback g_MenuStatusStates[MENU_STATUS_STEP_COUNT];
/* D_801D96F0 */
extern Callback g_MenuStatusStep1Funcs[MENU_STATUS_STEP1_COUNT];
/* D_801D96F8 */
extern Callback g_MenuStatusStep3Funcs[MENU_STATUS_STEP3_COUNT];
/* D_801D9700 */
extern Callback g_MenuStatusStep2Funcs[MENU_STATUS_STEP2_COUNT];
/* D_801D970C */
extern Callback g_MenuStatusStep2Sub2Funcs[MENU_STATUS_STEP2_SUB2_COUNT];
extern Callback D_801D9720[];
extern Callback D_801D9734[];
extern Callback g_MenuStatusTaskFuncs[MENU_STATUS_TASK_COUNT];
/* D_801D9768 */
extern Callback g_MenuStatusTask2StateFuncs[MENU_STATUS_TASK2_STATE_COUNT];
/* D_801D9774 */
extern Callback g_MenuStatusTask3StateFuncs[MENU_STATUS_TASK3_STATE_COUNT];
extern u8       MENU_CAPTION_GLYPH_2[];
extern u8       MENU_CLOCK_CAPTION[];
extern u8       MENU_COMMAND_FRAME[];
extern u8       MENU_COMMAND_FRAME_SELECTED[];
/* D_801D9960 */
extern u8       g_MenuListTab2OffSprites[];
/* D_801D9978 */
extern u8       g_MenuListTab2OnSprites[];
extern u8*      D_801C893C[];
extern u8*      D_801C8950[];
extern u8*      g_MenuInventoryTitles[5];
extern char     g_MenuInventoryCountFormat[];
extern u8       g_MenuInventoryTab1OffSprites[];
extern u8       g_MenuInventoryTab1OnSprites[];
extern u8       D_801D9990[];
extern u8       D_801D999C[];
extern u8       D_801D9A60[];
extern u8       g_MenuLabelAgility[];
/* D_801D9B5C */
extern u8       g_MenuEquipRowIcons[];
/* D_801D9B64 */
extern u8       g_MenuLabelEquip[];
extern u8       g_MenuPortraitAtlas[];
extern u8       D_801D9BA8[];
extern u8       MENU_CAPTION_ICON[];
extern u8       MENU_CLOCK_COLON[];
extern u8*      g_MenuCommandLabels[];
extern u8       g_MenuCommandRows[][5];
extern char*    D_801D9EA4[];
extern u8       D_801DA049;
extern s32      D_801DA0B4;
extern u8       D_801DA0C1;
extern s32      D_801DA12C;

void UI_DrawSpriteRun(s16 base_x, s16 base_y, const u8* record_table, u8 flags);
void func_801AF930(s32 x, s32 y, u8 palette_index, u8 icon_index, u8* command_stream, u8 stat_value, u8 sprite_flag);
bool func_801AF494(u8 predicate_kind, u8 record_bit, u8 record_kind, u8 record_index);
void func_801AF800(s16 record_x, s32 record_y, u8 record_kind, u8 record_mode, s32 record_index, s32 record_shade,
                   s32 sprite_flag);
void func_801AFA1C(u8* arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void func_801D1D1C(void);
extern void func_801D1E34(void);
extern s32  func_801D2978(void);
extern s32  func_801D2ADC(void);
extern void func_801D2C0C(void);
extern void func_801D2DA8(void);
extern void Menu_DrawIcon(u16 sprite_x, u16 sprite_y, u8 icon_column, u8 shade_mode);
extern void Menu_DrawCommandRow(s16 x, s16 y, u8 row, u8 selected, s32 unused);

/* Slide the master panel up to y -20 and stop it there. */
static inline void Menu_SlidePanelUp(void) {
    MenuPanelTask* task;
    u16            y;

    task        = g_MenuCurrentPanel;
    y           = task->pos.y - MENU_PANEL_STEP_Y;
    task->pos.y = y;
    if ((s16)y < MENU_PANEL_HIDDEN_Y) {
        LOH(task->pos.y) = MENU_PANEL_HIDDEN_Y;
        task->state      = 0;
    }
}

s32 Item_Count(u8 category, u8 item, u8 mode);

void func_801D3320(MenuPanelTask* task);
s32  Char_GetExpForLevel(s32 character, s32 level);

/* The item stacks the screen counts and consumes: held[] and used[] follow the same four items. */
typedef struct MenuStatusItems {
    /* 0x00 */ u8 held[4];
    /* 0x04 */ u8 used[4];
    /* 0x08 */ u8 unk_08; /* nonzero commits the use */
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
} MenuStatusItems;

ASSERT_OFFSET(MenuStatusItems, used, 0x04);
ASSERT_SIZE(MenuStatusItems, 12);

extern s8 D_80144E5E;

extern void            func_801D1CA4(void);
extern s32             func_801D1E60(void);
extern void            func_801D1EE8(void);
extern void            func_801D27BC(void);
extern u8              D_80144FF9;
extern s8              D_80146867;
extern s8              D_80146875;
extern s16             D_80148364;
extern u8              D_8014839C;
/* D_801DA028 */
extern MenuStatusItems g_MenuStatusItems;
extern s32             D_801DA044;
extern u8              D_801DA04E;
extern u8              D_801DA0C6;

s32 Char_GetAbilityCost(s32 character_index, s32 ability_kind, s32 mode);

/* The clut strip tables of this overlay, bound in config/symbols.toml. */
extern UvRect MENU_CLUT_STRIP_CELLS[];
extern u8     MENU_CLUT_STRIP_ENTRIES[];
extern u8     MENU_CLUT_STRIP_PALETTES[];
void          Menu_DrawClutStrip(u8 clut_index);

#endif
