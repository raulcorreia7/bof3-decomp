#ifndef OVERLAY_ETC_BATE_00_H
#define OVERLAY_ETC_BATE_00_H

/* The etc/bate/00 overlay's local declarations. Only this image
 * includes the file. */

#include "menu/party.h"
#include "shared/etc.h"
#include <stdio.h>
#include "menu/party.h"

extern u8  D_80148654;
extern u8  D_80148339;
extern u8  D_8014835F;
extern u8  D_80148361;
extern s16 D_80148388;
extern s16 D_801483AC;

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
/* The item category of each equipment slot. */
extern u8            D_801D875C[];
extern u8            D_80148338;
extern s8            D_80148511;
extern u8            D_80148656;
extern s8            D_80148658;
extern u8            D_8018E244;
extern OverlayHeader D_801D0C00;
/* D_801D0D80 */
extern u8            g_SaveSlotLevelFormat[];
/* D_801D0D84 */
extern u8            g_SaveSlotTimeFormat[];
extern u8            g_MenuCaptionRight[];
extern u8            g_MenuClockCaption[];
extern u8            g_MenuCommandFrame[];
extern u8            g_MenuCommandFrameSelected[];
/* D_801D0D90 */
extern u8            g_SaveSlotTimeColon[];
/* D_801D0D94 */
extern u8            g_SaveCardPortLabelFirst[];
/* D_801D0D98 */
extern u8            g_SaveCardPortLabelSecond[];

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
/* D_801D893C */
extern u8       g_MenuListTab2OffSprites[];
/* D_801D8954 */
extern u8       g_MenuListTab2OnSprites[];
extern u8*      D_801C893C[];
extern u8*      D_801C8950[];
extern u8*      g_MenuInventoryTitles[5];
extern u8       g_MenuInventoryTab1OffSprites[];
extern u8*      g_MenuEquipTitles[5];
extern u8       g_MenuEquipStatLabels[];
extern u8       g_MenuEquipCompareLabels[];
extern u8       g_MenuEquipCompareSprites[];
extern u8       g_MenuEquipSlotIcons[];
extern u8       g_MenuEquipStatSprites[];
extern u8       g_MenuEquipChoiceIds[];
extern u8       g_MenuEquipChoiceCounts[];
extern u8       g_MenuInventoryTab1OnSprites[];
/* D_801D896C */
extern u8       g_MenuListTab1OffSprites[];
/* D_801D8978 */
extern u8       g_MenuListTab1OnSprites[];
/* D_801D8A3C */
extern u8       g_SaveSlotFrameSprites[];
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

bool Item_Add(s32 category, u8 item, u8 amount, s32 unused);
s32  Item_Count(u8 category, u8 item, u8 mode);
void Menu_DrawPortrait(s32 sprite_x, s32 sprite_y, s32 atlas_index, s32 shade_mode);
void Menu_DrawIcon(u16 sprite_x, u16 sprite_y, u8 icon_column, u8 shade_mode);
s32  Char_GetExpForLevel(s32 character, s32 level);

void UI_DrawSpriteRun(s16 base_x, s16 base_y, const u8* record_table, u8 flags);

extern FormationLayout g_MenuFormations[FORMATION_COUNT];
extern FormationOrder  g_MenuFormationOrder;
extern s32             g_MenuFormationArrow[3][2];
extern s32             g_MenuFormationArrowTurned[3][2];
extern s32             g_MenuFormationSpots[PARTY_SLOT_COUNT][2];
extern u8              g_MenuFormationFrameLeft[];
extern u8              g_MenuFormationFrameMiddle[];
extern u8              g_MenuFormationFrameRight[];
void                   Menu_DrawFormationPreview(u16 x, u16 y, u8 index, u8 blink, s32 angle);
void                   Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color);

void func_801AF930(s16 x, s16 y, u8 palette_index, u8 icon_index, volatile Ability* ability, u8 stat_value, u8 sprite_flag);
bool func_801AF494(u8 test, u8 character_id, u8 category, u8 item_id);
void func_801AF800(s16 record_x, s32 record_y, u8 text_shade, u8 category, s32 item_id, s32 quantity, s32 sprite_flag);
void func_801AFA1C(u8* arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);

/* func_801D73B4 */
void Menu_DrawAbilityList(MenuListPanel* panel);

s32 Char_GetAbilityCost(s32 character_index, s32 ability_kind, s32 mode);

void func_801D2304(s32 arg0, s32 arg1);
void func_801D259C(void);

#endif
