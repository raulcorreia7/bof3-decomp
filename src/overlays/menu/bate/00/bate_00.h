#ifndef OVERLAY_ETC_BATE_00_H
#define OVERLAY_ETC_BATE_00_H

/* The etc/bate/00 overlay's local declarations. Only this image
 * includes the file. */

#include "scenario/party.h"
#include "shared/etc.h"
#include <stdio.h>
#include "scenario/party.h"

/* FAKE: the callers pass and read the cost as s32, the width the real prototype (u8) lacks. */
#define Char_GetAbilityCost ((s32 (*)(s32, s32, s32))Char_GetAbilityCost)

extern u8  D_80148654;
extern u8  D_80148339;
extern u8  D_8014835F;
extern u8  D_80148361;
extern s16 D_80148388;
extern s16 D_801483AC;

#define g_SceneState (*(struct SceneState*)&g_SceneState)

extern s8   D_80144DE4;
extern u8   D_80144DF2;
extern u8   D_80144DF3;
extern u8   D_80144DF4;
extern char g_MenuStatFormat[];
extern char g_MenuExperienceFormat[];
extern char g_MenuExperienceBlank[];
extern char g_MenuZennyFormat[];
/* D_801D0C48 */
extern char g_MenuClockFormat[];
extern u8   D_80144DF5;
extern u8   D_80144DF6;
extern u8   D_80144DF7;
/* The item category of each equipment slot. */
extern u8   D_801D875C[];
extern u8*  D_801D8744[4];
extern u16  D_801D8ECC[];
extern u8   D_80148338;
extern s8   D_80148511;
extern u8   D_80148656;
extern s8   D_80148658;
extern u8   D_8018E244;
/* g_EmiOverlayHeader */
/* D_801D0D80 */
extern u8   g_SaveSlotLevelFormat[];
/* D_801D0D84 */
extern u8   g_SaveSlotTimeFormat[];
extern u8   g_MenuCaptionRight[];
extern u8   g_MenuClockCaption[];
extern u8   g_MenuCommandFrame[];
extern u8   g_MenuCommandFrameSelected[];
/* D_801D0D90 */
extern u8   g_SaveSlotTimeColon[];
/* D_801D0D94 */
extern u8   g_SaveCardPortLabelFirst[];
/* D_801D0D98 */
extern u8   g_SaveCardPortLabelSecond[];

/* The eighth character record is the equipment menu's work record. */
#define MENU_BATE_CHARACTER_RECORD 7

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
extern Callback g_MenuBateStates[MENU_BATE_STEP_COUNT];
extern s8       D_801D86F0;
extern u8       g_MenuLabelAgility[];
/* D_801D8B38 */
extern u8       g_MenuEquipRowIcons[];
/* D_801D8B40 */
extern u8       g_MenuLabelEquip[];
extern u8       D_801D8B18[];
extern u8       D_801D8B20[];
extern u8       D_801D8B48[];
extern u8       D_801D8B4C[];
extern u8       g_MenuPortraitAtlas[];
/* D_801D8700 */
extern Callback g_MenuBateStep2Funcs[MENU_BATE_STEP2_COUNT];
extern u8       g_MenuCaptionIcon[];
extern u8       g_MenuClockColon[];
extern u8*      g_MenuCommandLabels[];
extern u8       g_MenuCommandRows[][5];
/* D_801D870C */
extern Callback g_MenuBateStep2Sub0Funcs[MENU_BATE_STEP2_SUB0_COUNT];
/* D_801D8718 */
extern Callback g_MenuBateStep2Sub1Funcs[MENU_BATE_STEP2_SUB1_COUNT];
/* D_801D8720 */
extern Callback g_MenuBateStep2Sub2Funcs[MENU_BATE_STEP2_SUB2_COUNT];
/* D_801D8764 */
extern Callback g_MenuBateStep3Funcs[MENU_BATE_STEP3_COUNT];
/* D_801D8770 */
extern Callback g_MenuBateStep3Sub0Funcs[MENU_BATE_STEP3_SUB0_COUNT];
extern u8       D_801D8778[];
/* D_801D893C */
extern u8       g_MenuListTab2OffSprites[];
/* D_801D8954 */
extern u8       g_MenuListTab2OnSprites[];
extern u8*      D_801C893C[];
extern u8*      D_801C8950[];
/* D_801D896C */
extern u8       g_MenuListTab1OffSprites[];
/* D_801D8978 */
extern u8       g_MenuListTab1OnSprites[];
/* D_801D8984 */
extern u8       D_801D8984[];
/* D_801D8A3C */
extern u8       D_801D8B84[];
/* D_801D8E80 */
extern u8*      g_MenuAbilityListNames[];

extern const char g_MenuInventoryCountFormat[];

typedef struct BateState {
    u8 unk_00;
    u8 pad_01[3];
    u8 unk_04;
    u8 pad_05[3];
    u8 unk_08;
    u8 pad_09[3];
    /* The equipped item in each slot before the change. */
    u8 equipped_items[EQUIP_SLOT_COUNT];
} BateState;

extern s8        D_80148659;
extern BateState D_801D8ED4;
extern u8        D_801D86F8[];
/* The stat tally: the six targets it counts to and the six shown counters. */
extern s32       D_801D8EE8[6];
extern s32       D_801D8F00[6];

void Menu_DrawPortrait(s32 sprite_x, s32 sprite_y, s32 atlas_index, s32 shade_mode);
void Menu_DrawIcon(u16 sprite_x, u16 sprite_y, u8 icon_column, u8 shade_mode);
s32  Char_GetExpForLevel(s32 character, s32 level);

void Menu_DrawFormationPreview(u16 x, u16 y, u8 index, u8 blink, s32 angle);
void Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color);

/* func_801AF930; sig-kept: the retail callers narrow x and y to s16 and pass the ability record. */
void UI_DrawAbilityRow(s16 x, s16 y, u8 shade, u8 element, volatile Ability* ability, u8 cost, u8 flags);
/* func_801AF494 */

/* func_801D73B4 */
void Menu_DrawAbilityList(MenuListPanel* panel);

void func_801D2304(s32 x, s32 y);
void func_801D259C(void);
void func_801D31B0(s16 x, s16 y, u8 index, u8 flag);
void func_801AE3F0(u16 x, u16 y, u16 width, u16 height, s32 frame_flags, u8 palette);

extern u8   D_801D8EE0[];
extern char D_801D0C18[];
extern char D_801D0C1C[];
extern char D_801D0C24[];
extern char D_801D0C2C[];
extern s32  D_801D8F0C[];
extern u8   D_801D8780[];

#endif
