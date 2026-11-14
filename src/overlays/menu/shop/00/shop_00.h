#ifndef OVERLAY_ETC_SHOP_00_H
#define OVERLAY_ETC_SHOP_00_H

/* The shop overlay's local declarations: its panel and sprite views, the
 * weapon/armor/item stock state, and the prototypes its units share. Only this
 * image includes the file. */

#include "game/character.h"
#include "menu/party.h"
#include "shared/etc.h"
#include "menu/save_data.h"
#include <string.h>
#include <stdio.h>

/* Antique IDs: GAME.EMI item table, @source: wiki:data/records#gameemi-fixed-tables. */
#define SHOP_ANTIQUE_FIRST            ITEM_CLAY_VASE
#define SHOP_ANTIQUE_COUNT            (ITEM_DRAGON_TEAR - ITEM_CLAY_VASE + 1U)
#define SHOP_ANTIQUE_PRICE_MULTIPLIER 50

/* The game clock's seconds byte. Retail reads it a second time through the
 * literal address, so the second read keeps the MEM spelling. */
#define SHOP_CLOCK_SECONDS_ADDR       0x8014496E
#define g_SceneFlags                  ((u8**)&g_SceneFlags)
#define g_AreaLoads                   ((s32**)g_AreaLoads)

/* Draw the cursor icon; on the countdown or an input advance it and report
 * arrival. A bare statement macro: the member declares `counter` and `count`
 * and returns its result. Kept: as an inline the frame grows 4 bytes (0xBC, retail
 * 0xB8) and the do/while form moves bytes. */
#define ETC_DRAW_CURSOR(row_y, icon, frame)                        \
    WinDrawCueText(MENU_PROMPT_X, (row_y), *cursor_byte + (icon)); \
    counter = &D_80148654;                                         \
    count   = *counter;                                            \
    count--;                                                       \
    *counter = count;                                              \
    if (count == 0 || g_InputPressed != 0) {                       \
        *counter = (frame);                                        \
        *cursor_byte += 1;                                         \
        if (*cursor_byte == (palette_index & BYTE_MASK)) {         \
            return 1;                                              \
        }                                                          \
    }                                                              \
    return 0

/* Tick the request counter and switch the window to mode 1 when the stream
 * loader is idle. Kept: the cue counter is a global lvalue; as an inline taking
 * its address, the first lui moves from $v1 to $v0 in both members. */
#define ETC_ADVANCE_CUE_AFTER_COUNTDOWN(cue_counter) \
    do {                                             \
        u8* counter;                                 \
        u8  count;                                   \
                                                     \
        func_801D6E94();                             \
        counter = &D_80148654;                       \
        count   = *counter;                          \
        if (count != 0) {                            \
            count--;                                 \
            *counter = count;                        \
            if (count != 0) {                        \
                return;                              \
            }                                        \
        }                                            \
        if ((SND_IsXAIdle() & BYTE_MASK) != 0) {     \
            count         = (cue_counter);           \
            (cue_counter) = count + 1;               \
            UI_SetMode(UI_MODE_FADE_IN);             \
        }                                            \
    } while (0)

ASSERT_OFFSET(MenuListPanel, pos, 0x04);
ASSERT_OFFSET(MenuListPanel, use_context, 0x08);
ASSERT_OFFSET(MenuListPanel, flags, 0x09);
ASSERT_OFFSET(MenuListPanel, source, 0x0A);
ASSERT_OFFSET(MenuListPanel, unk_0C, 0x0C);
ASSERT_OFFSET(MenuListPanel, selected, 0x0D);
ASSERT_OFFSET(MenuListPanel, unk_10, 0x10);
ASSERT_OFFSET(MenuListPanel, names, 0x20);

/* The scratchpad work row behind g_Task while func_801D62DC fills it from
 * the selection table at 0x801E537C (three words per row). */
typedef struct ShopSelection {
    u8  pad_00[0x34];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
} ShopSelection;

ASSERT_OFFSET(ShopSelection, unk_34, 0x34);

/* The save menu results g_SaveCardStatus holds beyond the CardEvent codes 0 to 4. */
enum {
    SAVE_STATUS_NO_FILE       = 5,  /* GAME_TEXT_NO_SAVE_FILE */
    SAVE_STATUS_WRITE_FAILED  = 6,  /* the write ended in a card error */
    SAVE_STATUS_FORMAT_FAILED = 7,  /* the card format failed */
    SAVE_STATUS_SAVED         = 8,  /* GAME_TEXT_SAVE_COMPLETE */
    SAVE_STATUS_FORMATTED     = 9,  /* GAME_TEXT_INIT_COMPLETE */
    SAVE_STATUS_CREATED       = 10, /* a new file was saved */
};

/* D_801E60EC: the save message shown during the timed wait, named for the step it precedes. */
enum {
    SAVE_WAIT_OVERWRITE = 20,
    SAVE_WAIT_FORMAT    = 21,
    SAVE_WAIT_CREATE    = 22,
    SAVE_WAIT_PROBE     = 23,
    SAVE_WAIT_SCAN      = 25,
};

extern u8          g_SaveBuffer[];
extern u8          D_80143BB4;
extern u16         D_80144948;
extern u8          D_80148331;
extern u8          D_80148332;
extern s16         D_80148340;
extern u8          D_80148355;
extern u8          D_8014835F;
extern u8          D_80148360;
extern u8          D_80148361;
extern u8          D_80148382;
extern u8          D_80148383;
extern u8          D_8014839C;
extern u8          D_801483A7;
extern u8          D_801483CB;
extern u8          D_801483E5;
extern u8          D_801483E6;
extern u16         D_801483E8;
extern u16         D_801483EA;
extern u8          D_801483EE;
extern u8          D_801483EF;
extern u8          D_80148412;
extern u8          D_80148434;
extern u8          D_80148435;
extern u8          D_80148436;
extern u8          D_80148437;
extern u8          D_80148438;
extern u8          D_80148439;
extern u16         D_8014843C;
extern u16         D_8014843E;
extern u8          D_8014845B;
extern u8          D_8014845C;
extern u8*         D_80148470;
extern s8          D_80148480;
extern u8*         D_80148494;
extern u8          D_801484A2;
extern u8          D_801484A3;
extern u8          D_801484A4;
extern u8          D_801484A5;
extern u8          D_80148601;
extern u8          D_80148602;
extern s16         D_80148628;
extern s16         D_8014862A;
extern u8*         D_80148644;
extern u8          D_80148654;
extern u8          D_80148656;
extern s8          D_80148658;
extern s8          D_80148659;
extern s8          D_8014865A;
extern volatile u8 D_8014865F;
extern u8*         D_8018E7CC;
/* D_8018E990 */
extern u8          g_SaveCardDirectory[];
extern u8*         D_801C893C[];
extern u8*         D_801C8950[];
extern ShopStock   g_GameShopStock[SHOP_COUNT];
extern char        D_801D0C1C[];
extern char        D_801D0C20[];
extern char        D_801D0C68[];
extern char        D_801D0C94[];
extern char        D_801D0C98[];
extern char        D_801D0CDC[];
extern char        g_MenuStatFormat[];
/* D_801D0CE8 */
extern char        g_MenuCurrentValueFormat[];
/* D_801D0CF0 */
extern char        g_MenuMaxValueFormat[];
/* D_801D0CF8 */
extern char        g_MenuExperienceFormat[];
/* D_801D0CFC */
extern char        g_MenuExperienceBlank[];
extern char        g_MenuZennyFormat[];
/* D_801D0D0C */
extern char        g_MenuNextExpBlank[];
extern char        g_MenuClockFormat[];
extern char        g_SaveSlotLevelFormat[];
extern char        g_SaveSlotTimeFormat[];
extern char        g_SaveSlotTimeColon[];
/* D_801D0E58 */
extern char        g_SaveCardPortLabelFirst[];
/* D_801D0E5C */
extern char        g_SaveCardPortLabelSecond[];
extern char        D_801D0E60[];
extern char        D_801D0E64[];
extern char        D_801D0E68[];
extern char        D_801D0E70[];
extern char        D_801D0E78[];
extern char        D_801D0E7C[];
extern char        D_801D0E84[];
extern char        D_801D0E88[];
extern char        D_801D0E90[];
extern char        D_801D0E98[];
/* Entries of the step handler tables. */
#define SHOP_STEP_COUNT          11
#define SHOP_STEP2_COUNT         5
#define SHOP_STEP2_SUB0_COUNT    2
#define SHOP_STEP2_SUB1_COUNT    1
#define SHOP_STEP2_SUB2_COUNT    8
#define SHOP_STEP2_SUB3_COUNT    5
#define SHOP_STEP3_COUNT         5
#define SHOP_STEP3_SUB1_COUNT    6
#define SHOP_STEP3_SUB2_COUNT    7
#define SHOP_STEP5_COUNT         8
#define SHOP_STEP6_COUNT         4
#define SHOP_STEP6_SUB0_COUNT    3
#define SHOP_STEP6_SUB3_COUNT    4
#define SHOP_STEP7_COUNT         5
#define SHOP_STEP7_SUB2_COUNT    5
#define SHOP_STEP7_SUB3_COUNT    3
#define SHOP_STEP8_COUNT         4
#define SHOP_STEP8_SUB2_COUNT    5
#define SHOP_STEP9_COUNT         3
#define SHOP_STEP9_SUB0_COUNT    2
#define SHOP_STEP9_SUB1_COUNT    3
#define SHOP_STEP9_SUB2_COUNT    3
#define SHOP_STEP10_COUNT        7
#define SAVE_STATE_COUNT         21

/* Entries of the panel handler tables. */
#define SHOP_MODE_COUNT          19
#define SHOP_PANEL0_STATE_COUNT  3
#define SHOP_PANEL1_STATE_COUNT  3
#define SHOP_PANEL2_STATE_COUNT  3
#define SHOP_PANEL5_STATE_COUNT  5
#define SHOP_PANEL6_STATE_COUNT  3
#define SHOP_PANEL7_STATE_COUNT  4
#define SHOP_PANEL9_STATE_COUNT  3
#define SHOP_PANEL11_STATE_COUNT 5
#define SHOP_PANEL12_STATE_COUNT 5
#define SHOP_PANEL13_STATE_COUNT 3
#define SHOP_PANEL15_STATE_COUNT 4
#define SHOP_PANEL16_STATE_COUNT 3
#define SHOP_PANEL17_STATE_COUNT 3
#define SHOP_PANEL18_STATE_COUNT 3

/* D_801E5144 */
extern Callback    g_ShopStates[SHOP_STEP_COUNT];
/* D_801E5170 */
extern Callback    g_ShopStep2Funcs[SHOP_STEP2_COUNT];
/* D_801E5184 */
extern Callback    g_ShopStep2Sub0Funcs[SHOP_STEP2_SUB0_COUNT];
/* D_801E518C */
extern Callback    g_ShopStep2Sub1Funcs[SHOP_STEP2_SUB1_COUNT];
/* D_801E5190 */
extern Callback    g_ShopStep2Sub2Funcs[SHOP_STEP2_SUB2_COUNT];
/* D_801E51B0 */
extern Callback    g_ShopStep2Sub3Funcs[SHOP_STEP2_SUB3_COUNT];
/* D_801E51C4 */
extern Callback    g_ShopStep8Funcs[SHOP_STEP8_COUNT];
/* D_801E51D4 */
extern Callback    g_ShopStep8Sub2Funcs[SHOP_STEP8_SUB2_COUNT];
extern u8          D_801E51E8[0xDC];
/* D_801E52C4 */
extern Callback    g_ShopStep3Funcs[SHOP_STEP3_COUNT];
/* D_801E52D8 */
extern Callback    g_ShopStep3Sub1Funcs[SHOP_STEP3_SUB1_COUNT];
/* D_801E52F0 */
extern Callback    g_ShopStep3Sub2Funcs[SHOP_STEP3_SUB2_COUNT];
/* D_801E530C */
extern Callback    g_SaveStates[SAVE_STATE_COUNT];
/* D_801E5360 */
extern Callback    g_ShopStep10Funcs[SHOP_STEP10_COUNT];
extern s32         D_801E537C[];
extern s32         D_801E5380[];
extern s32         D_801E5384[];
extern const char* D_801E5434[];
/* D_801E545C */
extern Callback    g_ShopStep5Funcs[SHOP_STEP5_COUNT];
extern u8          D_801E547C[];
extern u8          g_MenuCaptionRight[];
extern u8          g_MenuClockCaption[];
extern u8          g_MenuCommandFrame[];
extern u8          g_MenuCommandFrameSelected[];
/* D_801E5638 */
extern u8          g_MenuListTab2OffSprites[0xC];
/* D_801E5650 */
extern u8          g_MenuListTab2OnSprites[0xC];
extern u8*         g_MenuInventoryTitles[5];
extern char        g_MenuInventoryCountFormat[];
extern u8          g_MenuInventoryTab1OffSprites[];
extern u8*         g_MenuEquipTitles[5];
extern u8          g_MenuEquipChoiceIds[];
extern u8          g_MenuEquipChoiceCounts[];
extern u8          g_MenuInventoryTab1OnSprites[];
/* D_801E5668 */
extern u8          g_MenuListTab1OffSprites[0xC];
/* D_801E5674 */
extern u8          g_MenuListTab1OnSprites[0xC];
extern u8          D_801E5680[];
extern u8          g_MenuEquipStatSprites[];
extern u8          g_SaveSlotFrameSprites[];
extern u8          D_801E5814[];
extern u8          D_801E581C[];
extern u8          g_MenuLabelAgility[];
/* D_801E5834 */
extern u8          g_MenuEquipRowIcons[];
/* D_801E583C */
extern u8          g_MenuLabelEquip[];
extern u8          D_801E5844[];
extern u8          D_801E5848[];
extern u8          g_MenuPortraitAtlas[];
extern u8          D_801E5880[];
extern u8          g_MenuCaptionIcon[];
extern u8          g_MenuClockColon[];
extern u8*         g_MenuCommandLabels[];
extern u8          g_MenuCommandRows[][5];
extern u8          g_MenuEquipStatLabels[];
extern u8          g_MenuEquipCompareLabels[];
extern u8          g_MenuEquipCompareSprites[];
extern u8          g_MenuEquipSlotIcons[];
/* D_801E5B7C */
extern u8*         g_MenuAbilityListNames[4];
extern u8          D_801E5BC8[];
/* D_801E5BEC */
extern Callback    g_ShopStep6Funcs[SHOP_STEP6_COUNT];
/* D_801E5BFC */
extern Callback    g_ShopStep6Sub0Funcs[SHOP_STEP6_SUB0_COUNT];
/* D_801E5C08 */
extern Callback    g_ShopStep6Sub3Funcs[SHOP_STEP6_SUB3_COUNT];

typedef struct BoatPartyPos {
    s32 x;
    s32 y;
    s32 z;
    s32 unk_0C;
} BoatPartyPos;

extern BoatPartyPos g_ShopBoatPartyPositions[PARTY_SLOT_COUNT];
extern Point2D      g_ShopFacingSteps[8];
extern u8           D_801E5C68[];
extern u8           D_801E5C70[];
extern u8           D_801E5C78[];
extern u8           D_801E5C84[];
extern u8           D_801E5C90[];
extern u8           D_801E5CA8[];
extern u8           D_801E5CB4[];
extern u8           D_801E5CC0[];
extern u8           D_801E5CCC[];
extern u8           D_801E5CD8[];
/* D_801E5CE8 */
extern Callback     g_ShopStep7Funcs[SHOP_STEP7_COUNT];
/* D_801E5CFC */
extern Callback     g_ShopStep7Sub2Funcs[SHOP_STEP7_SUB2_COUNT];
/* D_801E5D10 */
extern Callback     g_ShopStep7Sub3Funcs[SHOP_STEP7_SUB3_COUNT];
extern u8           D_801E5D1C[];
/* D_801E5D2C */
extern Callback     g_AbilityStockCommands[];
extern u8           D_801E5D38[];
/* D_801E5D3C */
extern Callback     g_ShopStep9Funcs[SHOP_STEP9_COUNT];
/* D_801E5D48 */
extern Callback     g_ShopStep9Sub0Funcs[SHOP_STEP9_SUB0_COUNT];
/* D_801E5D50 */
extern Callback     g_ShopStep9Sub1Funcs[SHOP_STEP9_SUB1_COUNT];
/* D_801E5D5C */
extern Callback     g_ShopStep9Sub2Funcs[SHOP_STEP9_SUB2_COUNT];
/* D_801E5D68 */
extern Callback     g_ShopPanelModes[SHOP_MODE_COUNT];
extern void (*g_ShopMessageStates[SHOP_PANEL0_STATE_COUNT])();
/* D_801E5DC0 */
extern Callback           g_ShopCommandsStates[SHOP_PANEL2_STATE_COUNT];
/* D_801E5DCC */
extern Callback           g_ShopZennyStates[SHOP_PANEL1_STATE_COUNT];
extern u16                D_801E5DD8[];
/* D_801E5DDC */
extern Callback           g_ShopEquipStatStates[SHOP_PANEL5_STATE_COUNT];
/* D_801E5DF0 */
extern Callback           g_ShopEquipmentStates[SHOP_PANEL6_STATE_COUNT];
/* D_801E5DFC */
extern Callback           g_ShopItemsStates[SHOP_PANEL7_STATE_COUNT];
extern u8                 D_801E5E0C[];
extern u8                 D_801E5E1C[];
/* D_801E5E2C */
extern Callback           g_ShopInventoryStates[SHOP_PANEL9_STATE_COUNT];
extern u8                 D_801E5E38[];
/* D_801E5E48 */
extern Callback           g_ShopPanel11StateFuncs[SHOP_PANEL11_STATE_COUNT];
/* D_801E5E5C */
extern Callback           g_ShopPanel12StateFuncs[SHOP_PANEL12_STATE_COUNT];
/* D_801E5E70 */
extern Callback           g_ShopCharacterStates[SHOP_PANEL13_STATE_COUNT];
extern u8                 D_801E5E7C[];
extern u8                 D_801E5EA0[];
extern u8                 D_801E5EAC[];
extern u32                D_801E5EFC[];
extern u8                 D_801E5F0C;
extern u8                 D_801E5F0D[];
/* D_801E5F14 */
extern Callback           g_ShopPanel15StateFuncs[SHOP_PANEL15_STATE_COUNT];
/* D_801E5F24 */
extern Callback           g_ShopPanel16StateFuncs[SHOP_PANEL16_STATE_COUNT];
/* D_801E5F30 */
extern Callback           g_ShopPanel17StateFuncs[SHOP_PANEL17_STATE_COUNT];
/* D_801E5F3C */
extern Callback           g_ShopPanel18StateFuncs[SHOP_PANEL18_STATE_COUNT];
extern u32                D_801E5F48[3];
extern u32                D_801E5F54[3];
extern char               D_801E5F60[];
extern u32                D_801E5F68;
extern u8*                D_801E5FC0[];
extern MenuPortraitSprite g_ShopPortraitAtlas[12];
extern u8                 D_801E603C;
extern u8                 D_801E6040;
/* D_801E6044 */
extern s8                 g_ShopStockIndex;
/* D_801E6048 */
extern u8                 g_ShopItemCategory;
/* D_801E604C */
extern u8                 g_ShopItemId;
/* D_801E6050 */
extern u8                 g_ShopItemCount;
extern u8                 D_801E6054;
extern u8                 D_801E6058;
/* D_801E605C */
extern s32                g_ShopItemCountMax;
/* D_801E6060 */
extern s32                g_ShopItemPrice;
/* D_801E6064 */
extern u16                g_ShopPricePercent;
extern u8                 D_801E606C;
extern u8                 D_801E607C;
extern u8                 D_801E6080;
extern u8                 D_801E6088;
extern u8                 D_801E608C;
extern u8                 D_801E6094;
extern u8                 D_801E60EC;
extern u8                 D_801E60F0;
extern u8                 D_801E60F4;
extern u8                 D_801E60F8;
extern u8                 D_801E60FC;
extern s16                D_801E6100[];
extern u8                 D_801E6108;
extern u8                 D_801E610C;
extern u8                 D_801E6110;
extern u8                 D_801E6144[0x80];
extern u8                 D_801E61C4[0x80];
extern u8                 D_801E6244[];
extern u8                 D_801E6248[];
extern u8                 D_801E6249[];
extern u8                 D_801E6250;
extern u8                 D_801E6254;
extern u8                 D_801E6258;
extern u8                 D_801E625C;
extern volatile u8        D_801E6260;
extern u8                 D_801E6264[];

bool Item_Add(s32 category, u8 item_id, u8 count, s32 unused);
s32  Item_Count(u8 category, u8 item_id, u8 mode);
s32  Char_GetAbilityCost(u8 character_index, u8 ability_kind, u8 mode);
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
bool                   func_801AF494(u8 test, u8 character_id, u8 category, u8 item_id);
void                   func_801AF930(s16 x, s16 y, u8 palette_index, u8 icon_index, volatile Ability* ability, u8 stat_value, u8 sprite_flag);
void                   func_801AF800(s16 record_x, s32 record_y, u8 text_shade, u8 category, s32 item_id, s32 quantity, s32 sprite_flag);
void                   func_801AFA1C(u8* arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);
/* func_801C1254 */
void                   Party_LoadMemberSprite(u8 character_id, u8 party_slot);
void                   Shop_DispatchStep(void);
void                   func_801D0EDC(void);
void                   func_801D1000(void);
void                   func_801D10E4(void);
void                   func_801D1120(void);
void                   func_801D115C(void);
void                   func_801D1254(void);
void                   func_801D12C0(void);
void                   func_801D14B0(void);
void                   func_801D14EC(void);
void                   func_801D163C(void);
void                   func_801D1A90(void);
void                   func_801D1D60(void);
void                   func_801D1F74(void);
void                   func_801D20D0(void);
void                   func_801D23E4(void);
void                   func_801D26A8(void);
void                   func_801D27EC(void);
void                   func_801D2828(void);
void                   func_801D28D0(void);
void                   func_801D2D64(void);
void                   func_801D3014(void);
void                   func_801D3280(void);
void                   func_801D32C0(void);
void                   func_801D334C(void);
void                   func_801D349C(void);
void                   func_801D34F0(void);
void                   func_801D352C(void);
void                   func_801D3560(u16* result_code);
s32                    Shop_ApplyPercent(s32 value, s32 percent);
u32                    Shop_GetSellPrice(ItemCategory category, s32 item_id, s32 antique_shop);
void                   func_801D3710(void);
/* func_801D3828 */
void                   Shop_Equip(u8 character_id, u8 slot, u8 item_id);
void                   func_801D39BC(void);
void                   func_801D39F8(void);
void                   func_801D3AA8(void);
void                   func_801D3AE4(void);
void                   func_801D3B98(void);
void                   func_801D3C9C(void);
void                   func_801D3D84(void);
void                   func_801D3FD4(void);
void                   func_801D408C(void);
void                   func_801D41B0(void);
void                   func_801D41EC(void);
void                   func_801D430C(void);
void                   func_801D43A4(void);
void                   func_801D43F0(void);
void                   func_801D446C(void);
void                   func_801D456C(void);
void                   func_801D4614(void);
void                   SAVE_DispatchState(void);
void                   func_801D46E0(void);
void                   func_801D472C(void);
void                   func_801D47AC(void);
void                   func_801D4970(void);
void                   func_801D4A3C(void);
void                   func_801D4BBC(void);
void                   func_801D4CF0(void);
void                   func_801D4DB4(void);
void                   func_801D4E74(void);
void                   func_801D50C0(void);
void                   func_801D51B8(void);
void                   func_801D5390(void);
void                   func_801D543C(void);
void                   func_801D5790(void);
void                   func_801D5894(void);
void                   func_801D5AD0(void);
void                   func_801D5BB0(void);
void                   func_801D5CB0(void);
void                   func_801D5D98(void);
void                   func_801D5E88(void);
void                   func_801D6018(void);
void                   func_801D60B0(void);
void                   func_801D6184(void);
void                   func_801D61C0(void);
void                   func_801D62DC(void);
void                   func_801D65A0(void);
void                   func_801D65EC(void);
void                   func_801D6668(void);
void                   func_801D66AC(void);
void                   func_801D66C8(void);
s32                    func_801D66F8(u8* cursor_byte, s32 palette_index);
void                   func_801D68D0(s32 reset_slots);
void                   SAVE_BuildSlotImage(void);
void                   func_801D6CE4(u8 row_index, u8* source_record);
void                   func_801D6D6C(s32 strip_x, s32 strip_y);
void                   func_801D6E94(void);
void                   func_801D6F00(void);
/* func_801D7080 */
void                   SAVE_FormatSlot(void);
void                   func_801D7208(void);
void                   func_801D7344(void);
void                   func_801D7380(void);
void                   func_801D7444(void);
void                   func_801D76B8(void);
void                   func_801D7960(void);
void                   func_801D7AE4(void);
void                   func_801D7B74(void);
void                   func_801D7CC8(void);
void                   func_801D7D48(void);
void                   Menu_SwapBytes(u8* first, u8* second);
void                   func_801D7E1C(u8 slot, s32 x, s32 y, s32 style, u8 cursor);
void                   func_801D8050(s32 panel_x);
u8                     func_801D81B4(u8* cursor_byte, s32 palette_index);
void                   Menu_DrawCharacterWindow(s32 px, s32 py, u8 character_index, s32 shaded, s32 unused);
void                   Menu_DrawStatPanel(u16 panel_x, u16 panel_y, u8 palette_index);
void                   Shop_DrawEquipment(s16 x, s16 y, u8 record_index);
void                   func_801D8C58(s16 x, s16 y, u8 index, u8 flag);
void                   Menu_DrawPortrait(s32 sprite_x, s32 sprite_y, s32 atlas_index, s32 shade_mode);
void                   Menu_DrawCharacterPortrait(u16 sprite_x, u16 sprite_y, u8 atlas_index, u8 shade_mode);
void                   Menu_DrawTintedLine(s16 line_x0, s16 line_y0, s16 line_x1, s16 line_y1, u8 color_r, u8 color_g, u8 color_b, u8 tpage);
void                   Menu_DrawIcon(u16 sprite_x, u16 sprite_y, u8 icon_column, u8 shade_mode);
/* func_801DA120 */
void                   Menu_DrawPanelIcon(u16 icon_x, u16 icon_y, s32 icon_u, s32 icon_v, u16 icon_clut, u8 icon_shade);
void                   Menu_DrawPlayTimeWindow(u16 panel_x, u16 panel_y);
void                   Menu_DrawCommandRow(s16 x, s16 y, u8 row, u8 selected, s32 unused);
u16                    Item_GetPrice(ItemCategory category, s32 item_id);
s32                    Char_GetExpForLevel(s32 character, s32 level);
void                   Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, s32 window_style);
void                   Menu_DrawRowIcons(u8* row_record, s32 palette_index);
void                   Menu_DrawEquipStatWindow(u16 x, u16 y, u8 character_index, u8 item_kind, u8 item_id);
void                   Menu_DrawWindowFrame(s16 x, s16 y, u8 width, u8 height);
/* func_801DC6FC */
void                   Menu_DrawInventoryWindow(MenuPanelTask* arg0);
void                   SAVE_DrawSlot(u8 index, s32 left, s32 top, MenuListRow* row);
void                   SAVE_DrawPortTabs(s16 x, s16 y, u32 tab_flags, u8 port, u8 variant);
void                   func_801DE188(void);
void                   func_801DE1C4(void);
void                   func_801DE200(void);
void                   Shop_StartFadeIn(void);
void                   func_801DE40C(void);
void                   func_801DE45C(void);
void                   func_801DE4C8(void);
void                   func_801DE850(void);
void                   func_801DE88C(void);
void                   func_801DE8E8(void);
void                   func_801DE944(void);
void                   func_801DEE20(void);
void                   func_801DEE64(void);
void                   func_801DF00C(s32 panel_x, s32 panel_y);
void                   Menu_SwapBytes5(u8* first, u8* second);
s32                    func_801DF478(void);
void                   func_801DF6A8(void);
void                   func_801DF90C(void);
void                   func_801DF978(void);
void                   func_801DF9B4(void);
void                   func_801DF9EC(void);
void                   func_801DFDB8(void);
void                   func_801DFDF4(void);
void                   func_801E0028(void);
void                   func_801E006C(void);
void                   func_801E032C(void);
void                   func_801E05E0(void);
void                   func_801E092C(void);
void                   func_801E0968(void);
void                   func_801E09F4(void);
void                   func_801E0BAC(void);
void                   func_801E0F28(void);
void                   func_801E0F78(void);
void                   func_801E112C(MenuPanelTask* task);
void                   func_801E1710(MenuPanelTask* task);
/* func_801E1B80 */
void                   Menu_RunAbilityStockSort(s32 cursor_row);
void                   Menu_SwapBytes6(u8* first, u8* second);
/* func_801E1BCC */
void                   Menu_PackAbilityStock(void);
/* func_801E1C88 */
void                   Menu_SortAbilityStockByCostDescending(void);
/* func_801E1D84 */
void                   Menu_SortAbilityStockByCostAscending(void);
void                   func_801E1E80(s16 panel_x, s16 panel_y);
void                   func_801E200C(void);
void                   func_801E2048(void);
void                   func_801E2084(void);
void                   func_801E20CC(void);
void                   func_801E2114(void);
void                   func_801E2150(void);
void                   func_801E2474(void);
void                   func_801E254C(void);
void                   func_801E2590(void);
void                   func_801E25CC(void);
void                   func_801E2610(void);
void                   func_801E262C(void);
void                   func_801E2650(void);
void                   func_801E2724(void);
void                   func_801E27BC(void);
void                   func_801E2800(void);
/* func_801E2808 */
void                   Menu_MessagePanel(void);
void                   func_801E2948(void);
void                   func_801E2988(void);
/* func_801E29C8 */
void                   Menu_CommandsPanel(void);
void                   func_801E2A30(void);
void                   func_801E2A70(void);
/* func_801E2AB0 */
void                   Menu_ZennyPanel(void);
void                   func_801E2B14(void);
void                   func_801E2B54(void);
/* func_801E2BC4 */
void                   Menu_CursorFramePanel(void);
/* func_801E2C18 */
void                   Menu_EquipStatPanel(void);
void                   func_801E2C9C(void);
void                   func_801E2CDC(void);
void                   func_801E2D1C(void);
void                   func_801E2D5C(void);
/* func_801E2DB4 */
void                   Menu_EquipmentPanel(void);
/* func_801E2E30 */
void                   Battle_PickFormationTarget(void);
void                   func_801E2E70(void);
/* func_801E2EB0 */
void                   Menu_ItemsPanel(void);
void                   Shop_DrawItems(MenuListPanel* panel);
void                   func_801E31C4(void);
void                   func_801E3204(void);
void                   func_801E3244(void);
void                   func_801E3284(MenuPanelTask* task);
void                   func_801E36F8(void);
/* func_801E3720 */
void                   Menu_InventoryPanel(void);
void                   func_801E3774(void);
void                   func_801E37B4(void);
void                   func_801E37F4(MenuPanelTask* task);
void                   func_801E3B7C(void);
void                   func_801E3BA4(void);
void                   func_801E3BF8(void);
void                   func_801E3C38(void);
void                   func_801E3C78(void);
void                   func_801E3CB8(void);
void                   func_801E3CF8(void);
void                   func_801E3D4C(void);
void                   func_801E3D8C(void);
void                   func_801E3DCC(void);
void                   func_801E3E0C(void);
/* func_801E3E4C */
void                   Menu_CharacterPanel(void);
void                   func_801E3EB4(void);
void                   func_801E3EF4(void);
void                   func_801E3F34(void);
void                   func_801E3F5C(void* panel);
void                   func_801E4224(void);
void                   func_801E4278(void);
void                   func_801E42B8(void);
void                   func_801E42F8(void);
void                   func_801E4338(void);
void                   func_801E438C(void);
void                   func_801E43CC(void);
void                   func_801E440C(void);
void                   func_801E4460(void);
void                   func_801E44A0(void);
void                   func_801E44E0(void);
void                   func_801E4540(void);
void                   func_801E4580(void);
void                   func_801E45C0(MenuPanelTask* arg0);
s32                    func_801E4C2C(s32 item_class);
bool                   Party_HasSkill(s32 item_id);
/* func_801E4DF4 */
void                   Shop_DrawCuePanel(MenuPanelTask* panel_task);
void                   func_801E4E9C(MenuPanelTask* panel_task);
void                   func_801E4FC8(s32 sprite_x, s32 sprite_y, u8 atlas_index, s32 shade_mode);
/* Returns the save probe's signed byte result; its caller tests it against -1. */
s8                     SAVE_AccessFile(s32 port, s32 name, s32 mode, s32 size, s32 offset);
u32                    func_801EF200(void);
s32                    func_801EF27C(s32, s32, u8*);

/* Decrement the countdown; on zero run the panel reset and latch g_MenuStep.step. */
static inline void MenuTickCountdown(void) {
    volatile u8* p   = &D_80148654;
    u8           val = *p - 1;

    *p = val;
    if (val == 0) {
        Menu_ResetPanelTasks();
        g_MenuStep.step = 1;
    }
}

/* Fill the screen with an opaque black 320x240 tile. */
static inline void MenuClearScreenTile(void) {
    TILE* prim = (TILE*)g_GfxPrimCursor;

    SetTile(prim);
    SetSemiTrans(prim, 0);
    prim->w = 320;
    setXY0(prim, 0, 0);
    prim->h = 240;
    setRGB0(prim, 0, 0, 0);
    GFX_AddPrim(1, sizeof(TILE));
}

/* Counts the cue counter down and steps the shop when it reaches zero.
 * The member declares p and val. */
#define SHOP_TICK_COUNTDOWN_AND_STEP() \
    p   = &D_80148654;                 \
    val = *p - 1;                      \
    *p  = val;                         \
    if (val == 0) {                    \
        D_80148652 += 1;               \
    }

#endif
