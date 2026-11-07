#ifndef OVERLAY_ETC_BATE_00_H
#define OVERLAY_ETC_BATE_00_H

/* The etc/bate/00 overlay's local declarations. Only this image
 * includes the file. */

#include "shared/etc.h"
#include <stdio.h>

extern u8 D_80148654;

#define g_SceneState (*(struct SceneState*)&g_SceneState)

extern s8            D_80144DE4;
extern u8            D_80144DF2;
extern u8            D_80144DF3;
extern u8            D_80144DF4;
extern char          g_MenuStatFormat[];
extern char          g_MenuZennyFormat[];
/* D_801D0C48 */
extern char          g_MenuNextExpBlank[];
extern char          g_MenuClockFormat[];
extern u8            D_80144DF5;
extern u8            D_80144DF6;
extern u8            D_80144DF7;
extern u8            D_80145FCC[][BATTLE_PARTY_STRIDE];
extern u8            D_80148338;
extern s8            D_80148511;
extern u8            D_80148656;
extern s8            D_80148658;
extern u8            D_8018E244;
extern OverlayHeader D_801D0C00;
extern u8            D_801D0D80[];
extern u8            D_801D0D84[];
extern u8            MENU_CAPTION_GLYPH_2[];
extern u8            MENU_CLOCK_CAPTION[];
extern u8            MENU_COMMAND_FRAME[];
extern u8            MENU_COMMAND_FRAME_SELECTED[];
extern u8            D_801D0D90[];
extern u8            D_801D0D94[];
extern u8            D_801D0D98[];
/* Entries of the handler tables. */
#define MENU_BATE_STEP_COUNT       4
#define MENU_BATE_STEP2_COUNT      3
#define MENU_BATE_STEP2_SUB0_COUNT 3
#define MENU_BATE_STEP2_SUB1_COUNT 2
#define MENU_BATE_STEP2_SUB2_COUNT 2
#define MENU_BATE_STEP3_COUNT      3
#define MENU_BATE_STEP3_SUB0_COUNT 2

/* The overlay's step and sub-step handler pools; the tables are views into one
 * callback run, selected by the shared menu step bytes. */
/* D_801D86E0 */
extern Callback    g_MenuBateStepFuncs[MENU_BATE_STEP_COUNT];
extern s8          D_801D86F0;
extern u8          g_MenuLabelAgility[];
/* D_801D8B38 */
extern u8          g_MenuEquipRowIcons[];
/* D_801D8B40 */
extern u8          g_MenuLabelEquip[];
extern u8          g_MenuPortraitAtlas[];
/* D_801D8700 */
extern Callback    g_MenuBateStep2Funcs[MENU_BATE_STEP2_COUNT];
extern u8          MENU_CAPTION_ICON[];
extern u8          MENU_CLOCK_COLON[];
extern u8*         g_MenuCommandLabels[];
extern u8          g_MenuCommandRows[][5];
/* D_801D870C */
extern Callback    g_MenuBateStep2Sub0Funcs[MENU_BATE_STEP2_SUB0_COUNT];
/* D_801D8718 */
extern Callback    g_MenuBateStep2Sub1Funcs[MENU_BATE_STEP2_SUB1_COUNT];
/* D_801D8720 */
extern Callback    g_MenuBateStep2Sub2Funcs[MENU_BATE_STEP2_SUB2_COUNT];
/* D_801D8764 */
extern Callback    g_MenuBateStep3Funcs[MENU_BATE_STEP3_COUNT];
/* D_801D8770 */
extern Callback    g_MenuBateStep3Sub0Funcs[MENU_BATE_STEP3_SUB0_COUNT];
/* D_801D893C */
extern u8          g_MenuListTab2OffSprites[];
/* D_801D8954 */
extern u8          g_MenuListTab2OnSprites[];
/* D_801D896C */
extern u8          g_MenuListTab1OffSprites[];
/* D_801D8978 */
extern u8          g_MenuListTab1OnSprites[];
extern u8          D_801D8A3C[];
extern u8          D_801D8B84[];
/* D_801D8E80 */
extern const char* g_MenuAbilityListNames[];
extern u8          D_801D8EE0[5];

typedef struct BateState {
    u8 unk_00;
    u8 pad_01[3];
    u8 unk_04;
    u8 pad_05[3];
    u8 unk_08;
} BateState;

extern s8        D_80148659;
extern BateState D_801D8ED4;

s32  Item_Count(u8 category, u8 item, u8 mode);
void Menu_DrawPortrait(s32 sprite_x, s32 sprite_y, s32 atlas_index, s32 shade_mode);
void Menu_DrawIcon(u16 sprite_x, u16 sprite_y, u8 icon_column, u8 shade_mode);
s32  Char_GetExpForLevel(s32 character, s32 level);

void UI_DrawSpriteRun(s16 base_x, s16 base_y, const u8* record_table, u8 flags);

void func_801AF930(s32 x, s32 y, u8 palette_index, u8 icon_index, u8* command_stream, u8 stat_value, u8 sprite_flag);

/* func_801D73B4 */
void Menu_DrawAbilityList(MenuListPanel* panel);

s32 Char_GetAbilityCost(s32 character_index, s32 ability_kind, s32 mode);

void func_801D2304(s32 arg0, s32 arg1);
void func_801D259C(void);

#endif
