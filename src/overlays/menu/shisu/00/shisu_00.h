#ifndef OVERLAY_ETC_SHISU_00_H
#define OVERLAY_ETC_SHISU_00_H

/* The etc/shisu/00 overlay's local declarations. Only this image
 * includes the file. */

#include "scenario/party.h"
#include "shared/etc.h"
#include <stdio.h>
#include "scenario/party.h"

/* FAKE: the callers pass and read the cost as s32, the width the real prototype (u8) lacks. */
#define Char_AbilityGetCost ((s32 (*)(s32, s32, s32))Char_AbilityGetCost)

#define g_ScenarioState     (*(struct ScenarioState*)&g_ScenarioState)

extern u8   D_80148656;
/* g_EmiOverlayHeader */
extern char g_MenuStatFormat[];
/* The value formats Menu_DrawCharacterWindow prints. */
extern char g_MenuCurrentValueFormat[];
extern char g_MenuMaxValueFormat[];
/* The sprite run it draws under the record. */
extern u8   D_801D97A4[];
/* The poison and confusion labels it draws beside the name. */
extern u8   D_801D9B3C[];
extern u8   D_801D9B44[];
extern char g_MenuZennyFormat[];
/* D_801D0C2C */
extern char g_MenuClockFormat[];
/* D_801D0D64 */
extern char g_SaveSlotLevelFormat[];
/* D_801D0D68 */
extern char g_SaveSlotTimeFormat[];
/* D_801D0D74 */
extern u8   g_SaveSlotTimeColon[];
/* D_801D0D78 */
extern char g_SaveCardPortLabelFirst[];
/* D_801D0D7C */
extern char g_SaveCardPortLabelSecond[];
/* Entries of the handler tables. */
#define SHISU_STEP_COUNT        5
#define SHISU_TASK_COUNT        4
#define SHISU_STEP1_COUNT       2
#define SHISU_STEP2_COUNT       3
#define SHISU_STEP2_SUB2_COUNT  5
#define SHISU_STEP3_COUNT       2
#define SHISU_TASK1_STATE_COUNT 3
#define SHISU_TASK2_STATE_COUNT 3
#define SHISU_TASK3_STATE_COUNT 3

/* How far above and below the ground the topping and base models start, in 16.16. */
#define SHISU_HEIGHT_BIAS       (512 << 16)

/* The overlay's step and sub-step handler pools; the tables are views into one
 * callback run, selected by the shared menu step byte. */
/* D_801D96DC */
extern Callback g_ShisuSteps[SHISU_STEP_COUNT];
/* D_801D96F0 */
extern Callback g_ShisuStep1Steps[SHISU_STEP1_COUNT];
/* D_801D96F8 */
extern Callback g_ShisuStep3Steps[SHISU_STEP3_COUNT];
/* D_801D9700 */
extern Callback g_ShisuStep2Steps[SHISU_STEP2_COUNT];
/* D_801D970C */
extern Callback g_ShisuStep2Sub2Steps[SHISU_STEP2_SUB2_COUNT];
extern Callback D_801D9720[];
extern Callback D_801D9734[];
extern Callback g_ShisuTaskSteps[SHISU_TASK_COUNT];
/* D_801D975C */
extern Callback g_ShisuTask1Steps[SHISU_TASK1_STATE_COUNT];
/* D_801D9768 */
extern Callback g_ShisuTask2Steps[SHISU_TASK2_STATE_COUNT];
/* D_801D9774 */
extern Callback g_ShisuTask3Steps[SHISU_TASK3_STATE_COUNT];
extern u8       g_MenuCaptionRight[];
extern u8       g_MenuClockCaption[];
extern u8       g_MenuCommandFrame[];
extern u8       g_MenuCommandFrameSelected[];
extern u8       D_80148654;
extern u8*      g_ItemCategoryIds[];
extern u8*      g_ItemCategoryCounts[];
extern u8       D_801D9780[12];
extern u8       D_801D978C[12];
extern u8       D_801D9798[4];
extern u8       D_801D979C[];
/* D_801D9960 */
extern u8       g_MenuListTab2OffSprites[];
/* D_801D9978 */
extern u8       g_MenuListTab2OnSprites[];
extern u8       D_801D9990[];
extern u8       D_801D999C[];
/* D_801D9A60 */
extern u8       g_MenuLabelAgility[];
/* D_801D9B5C */
extern u8       g_MenuEquipRowIcons[];
/* D_801D9B64 */
extern u8       g_MenuLabelEquip[];
extern u8       D_801D9EF0[3];
extern u8       D_801D9EF4[3];
extern u8       g_MenuPortraitAtlas[];
extern u32      g_ShisuScales[];
extern u8       D_801D9BA8[];
extern u8       g_MenuCaptionIcon[];
extern u8       g_MenuClockColon[];
extern u8*      g_MenuCommandLabels[];
extern u8       g_MenuCommandRows[][5];
extern char*    D_801D9EA4[];
extern s32      D_801DA07C;
extern s32      D_801DA080;
extern u8       D_801DA090;
extern s32      D_801DA098;
/* The two work pointers retail stores and then re-reads; volatile keeps the reload. */
extern s32* volatile D_801DA09C;
extern s32 D_801DA0AC;
extern s32 D_801DA0B0;
extern s32 g_ShisuBaseAngle;
extern s32 g_ShisuBaseScale;
extern s32 D_801DA0F4;
extern s32 D_801DA0F8;
extern s32 D_801DA0FC;
extern u8  D_801DA108;
extern s32 D_801DA110;
extern s32* volatile D_801DA114;
extern s32  g_ShisuToppingAngle;
extern s32  D_801DA124;
extern s32  D_801DA128;
extern s32* D_801F501C;

extern const char g_MenuInventoryCountFormat[];

void        Menu_DrawFormationPreview(u16 x, u16 y, u8 index, u8 blink, s32 angle);
void        Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color);
/* func_801AF930 */
void        UI_ListDrawAbilityRow(s32 x, s32 y, u8 shade, u8 element, u8* name, u8 cost, u8 flags);
/* func_801AF494 */
extern void func_801D1D1C(void);
extern void func_801D1E34(void);
void        func_801D4158(s16 x, s16 y, u8 index, u8 flag);
extern void func_801D2978(void);
extern void func_801D2ADC(void);
extern void func_801D2C0C(void);
extern void func_801D2DA8(void);
extern void Menu_DrawIcon(u16 sprite_x, u16 sprite_y, u8 icon_column, u8 shade_mode);
extern void Menu_DrawCommandRow(s16 x, s16 y, u8 row, u8 selected, s32 unused);
void        Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style);

/* Slide the master panel up to y -20 and stop it there. */
static inline void Menu_SlidePanelUp(void) {
    MenuPanelTask* task;
    u16            y;

    task        = g_UiPanelCurrent;
    y           = task->pos.y - MENU_PANEL_STEP_Y;
    task->pos.y = y;
    if ((s16)y < MENU_PANEL_HIDDEN_Y) {
        LOH(task->pos.y) = MENU_PANEL_HIDDEN_Y;
        task->state      = 0;
    }
}

void func_801D3320(MenuPanelTask* task);
s32  Char_GetExpForLevel(s32 character, s32 level);

/* The item stacks the screen counts and consumes: held[] and used[] follow the same four items. */
typedef struct ShisuIngredients {
    /* 0x00 */ u8 held[4];
    /* 0x04 */ u8 used[4];
    /* 0x08 */ u8 rounds;       /* mixing rounds done, at most 8; nonzero commits the use */
    /* 0x09 */ u8 command;      /* 0 mixes, 1 leaves: left and right flip it */
    /* 0x0A */ u8 cursor;       /* the ingredient row the list opens on: up picks 3, down 0 */
    /* 0x0B */ u8 topping_size; /* the topping's g_ShisuScales index, 9-16 from D_80144FF9 */
} ShisuIngredients;

ASSERT_OFFSET(ShisuIngredients, used, 0x04);
ASSERT_SIZE(ShisuIngredients, 12);

extern s8 D_80144E5E;

extern u8               D_80144FF9;
extern s16              D_80148364;
extern u8               D_8014839C;
extern void             func_801D1CA4(void);
extern s32              func_801D1E60(void);
extern u8               func_801D1EE8(void);
extern void             func_801D2308(void* record);
extern void             func_801D27BC(void);
/* D_801DA028 */
extern ShisuIngredients g_ShisuIngredients;
extern s32              D_801DA034;
extern s32              D_801DA038;
extern s32              D_801DA03C;
extern s32              D_801DA040;
extern s32              D_801DA044;
extern u8               g_ShisuBase[3];
extern u8               g_ShisuBaseR;
extern u8               g_ShisuBaseG;
extern u8               g_ShisuBaseB;
extern u8               D_801DA04E;
extern s32              D_801DA084;
extern s32              g_ShisuBaseScale;
extern Actor            D_801DA048;
extern Actor            D_801DA0C0;
extern u8               D_801DA0C6;
extern s32              D_801DA0FC;
extern u32              g_ShisuToppingScale;
/* kept: func_801D2ADC reads the tint bytes as three globals; one array shares their base register
   and leaves it eight bytes short. */
extern u8               g_ShisuTopping[3];
extern u8               g_ShisuToppingR;
extern u8               g_ShisuToppingG;
extern u8               g_ShisuToppingB;

/* The clut strip tables of this overlay, bound in config/symbols/<image>.toml. */
extern UvRect g_MenuClutStripCells[];
extern u8     g_MenuClutStripEntries[];
extern u8     g_MenuClutStripPalettes[];
void          Menu_DrawClutStrip(u8 clut_index);

#endif
