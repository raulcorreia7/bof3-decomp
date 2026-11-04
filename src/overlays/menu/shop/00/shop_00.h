#ifndef OVERLAY_ETC_SHOP_00_H
#define OVERLAY_ETC_SHOP_00_H

/* The shop overlay's local declarations: its panel and sprite views, the
 * weapon/armor/item stock state, and the prototypes its units share. Only this
 * image includes the file. */

#include "game/character.h"
#include "shared/etc.h"
#include <string.h>
#include <stdio.h>

/* The game clock's seconds byte. Retail reads it a second time through the
 * literal address, so the second read keeps the MEM spelling. */
#define SHOP_CLOCK_SECONDS_ADDR 0x8014496E
#define g_SceneFlags            ((u8**)&g_SceneFlags)
#define g_AreaLoads             ((s32**)g_AreaLoads)

/* Draw the cursor icon; on the countdown or an input advance it and report
 * arrival. A bare statement macro: the member declares `counter` and `count`
 * and returns its result. Kept: as an inline the frame grows 4 bytes (0xBC, retail
 * 0xB8) and the do/while form moves bytes. */
#define ETC_DRAW_CURSOR(row_y, icon, frame)                \
    WinDrawCueText(28, (row_y), *cursor_byte + (icon));    \
    counter = &D_80148654;                                 \
    count   = *counter;                                    \
    count--;                                               \
    *counter = count;                                      \
    if (count == 0 || g_InputPressed != 0) {               \
        *counter = (frame);                                \
        *cursor_byte += 1;                                 \
        if (*cursor_byte == (palette_index & BYTE_MASK)) { \
            return 1;                                      \
        }                                                  \
    }                                                      \
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
        if ((SND_IsXaIdle() & BYTE_MASK) != 0) {     \
            count         = (cue_counter);           \
            (cue_counter) = count + 1;               \
            UI_SetMode(1);                           \
        }                                            \
    } while (0)

/* The shop's panel record, handed to the panel drawers as a pointer: the
 * ability list (Shop_DrawAbilities) and the item list (Shop_DrawItems) read the
 * same cells. The record's extent is not proven; 0x24 is the last proven
 * cell, the names pointer. */
typedef struct ShopPanel {
    u8  pad_00[4];
    u16 x;        /* 0x04 the panel's x; both drawers add 3 and pass it to UI_DrawWindow */
    u16 y;        /* 0x06 the panel's y */
    u8  unk_08;   /* 0x08 the ability list passes it to func_801AF5B0 */
    u8  flags;    /* 0x09 bit 0 and bit 1 pick the cursor; the high nibble counts the frame down */
    u8  unk_0A;   /* 0x0A the list selector, passed to func_80166AE4 */
    u8  unk_0B;   /* 0x0B the stock row; it indexes the name table at a 4-byte stride */
    u8  unk_0C;   /* 0x0C a row the drawer draws an icon for */
    u8  selected; /* 0x0D the selected row; the drawer shades it 2 */
    u8  pad_0E[2];
    s16 unk_10; /* 0x10 tested against zero for the extra frame marks */
    u8  pad_12[0xE];
    u8* names; /* 0x20 the name table: a row count, then 2-byte rows */
} ShopPanel;

ASSERT_SIZE(ShopPanel, 0x24);
ASSERT_OFFSET(ShopPanel, x, 0x04);
ASSERT_OFFSET(ShopPanel, y, 0x06);
ASSERT_OFFSET(ShopPanel, unk_08, 0x08);
ASSERT_OFFSET(ShopPanel, flags, 0x09);
ASSERT_OFFSET(ShopPanel, unk_0A, 0x0A);
ASSERT_OFFSET(ShopPanel, unk_0B, 0x0B);
ASSERT_OFFSET(ShopPanel, unk_0C, 0x0C);
ASSERT_OFFSET(ShopPanel, selected, 0x0D);
ASSERT_OFFSET(ShopPanel, unk_10, 0x10);
ASSERT_OFFSET(ShopPanel, names, 0x20);

/* The scratchpad work row behind g_SpadWork while func_801D62DC fills it from
 * the selection table at 0x801E537C (three words per row). */
typedef struct ShopSelection {
    u8  pad_00[0x34];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
} ShopSelection;

ASSERT_OFFSET(ShopSelection, unk_34, 0x34);

/* D_800C1A00 */
extern u8          g_SaveBuffer[];
extern u8          D_80143BB4;
/* D_80143F00 */
extern u16         g_GameAreaId;
extern u16         g_InputRepeatDelay;
extern u16         g_InputRepeatButtons;
extern u16         D_80144948;
extern u8          D_80145F09[];
extern u8          D_80145FCC[][BATTLE_PARTY_STRIDE];
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
extern u8          D_8018E990[];
extern u8*         D_801C893C[];
extern u8*         D_801C8950[];
/* D_801CA28C */
extern ShopStock   g_GameShopStock[SHOP_COUNT];
extern char        D_801D0C1C[];
extern char        D_801D0C20[];
extern char        D_801D0C68[];
extern char        D_801D0C94[];
extern char        D_801D0C98[];
extern char        D_801D0CDC[];
/* D_801D0CE4 */
extern char        g_MenuStatFormat[];
extern char        D_801D0CE8[];
extern char        D_801D0CF0[];
extern char        D_801D0CF8[];
extern char        D_801D0CFC[];
/* D_801D0D08 */
extern char        g_MenuZennyFormat[];
extern char        D_801D0D0C[];
extern char        g_MenuClockFormat[];
extern char        D_801D0E44[];
extern char        D_801D0E48[];
extern char        D_801D0E54[];
extern char        D_801D0E58[];
extern char        D_801D0E5C[];
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
extern Callback    D_801E5144[];
extern Callback    D_801E5170[];
extern Callback    D_801E5184[];
extern Callback    D_801E518C[];
extern Callback    D_801E5190[];
extern Callback    D_801E51B0[];
extern Callback    D_801E51C4[];
extern Callback    D_801E51D4[];
extern u8          D_801E51E8[0xDC];
extern Callback    D_801E52C4[];
extern Callback    D_801E52D8[];
extern Callback    D_801E52F0[];
extern Callback    D_801E530C[];
extern Callback    D_801E5360[];
extern s32         D_801E537C[];
extern s32         D_801E5380[];
extern s32         D_801E5384[];
extern const char* D_801E5434[];
extern Callback    D_801E545C[];
extern u8          D_801E547C[];
/* D_801E5574 */
extern u8          MENU_CAPTION_GLYPH_2[];
extern u8          MENU_CLOCK_CAPTION[];
extern u8          MENU_COMMAND_FRAME[];
extern u8          MENU_COMMAND_FRAME_SELECTED[];
extern u8          D_801E5638[0xC];
extern u8          D_801E5650[0xC];
extern u8          D_801E5668[0xC];
extern u8          D_801E5674[0xC];
extern u8          D_801E5680[];
extern u8          D_801E56DC[];
extern u8          D_801E5738[];
extern u8          D_801E5814[];
extern u8          D_801E581C[];
/* D_801E5830 */
extern u8          g_MenuLabelAgility[];
extern u8          D_801E5834[];
extern u8          D_801E583C[];
extern u8          D_801E5844[];
extern u8          D_801E5848[];
/* D_801E5850 */
extern u8          g_MenuPortraitAtlas[];
extern u8          D_801E5880[];
/* D_801E58B0 */
extern u8          MENU_CAPTION_ICON[];
extern u8          MENU_CLOCK_COLON[];
extern u8*         g_MenuCommandLabels[];
extern u8          g_MenuCommandRows[][5];
extern u8          D_801E5A10[];
/* D_801E5A24 */
extern const char* D_801E5B7C[4];
extern u8          D_801E5BC8[];
extern Callback    D_801E5BEC[];
extern Callback    D_801E5BFC[];
extern Callback    D_801E5C08[];
extern s32         D_801E5C18[]; /* rows of x, y, distance, pad */
extern s16         D_801E5C48[]; /* rows of x, y shifts */
extern u8          D_801E5C68[];
extern u8          D_801E5C70[];
extern u8          D_801E5C78[];
extern u8          D_801E5C84[];
extern u8          D_801E5C90[];
extern u8          D_801E5CA8[];
extern u8          D_801E5CB4[];
extern u8          D_801E5CC0[];
extern u8          D_801E5CCC[];
extern u8          D_801E5CD8[];
extern Callback    D_801E5CE8[];
extern Callback    D_801E5CFC[];
extern Callback    D_801E5D10[];
extern u8          D_801E5D1C[];
extern Callback    D_801E5D2C[];
extern u8          D_801E5D38[];
extern Callback    D_801E5D3C[];
extern Callback    D_801E5D48[];
extern Callback    D_801E5D50[];
extern Callback    D_801E5D5C[];
extern Callback    D_801E5D68[];
extern void (*D_801E5DB4[])();
extern Callback    D_801E5DC0[];
extern Callback    D_801E5DCC[];
extern u16         D_801E5DD8[];
extern Callback    D_801E5DDC[];
extern Callback    D_801E5DF0[];
extern Callback    D_801E5DFC[];
extern u8          D_801E5E0C[];
extern u8          D_801E5E1C[];
extern Callback    D_801E5E2C[];
extern u8          D_801E5E38[];
extern Callback    D_801E5E48[];
extern Callback    D_801E5E5C[];
extern Callback    D_801E5E70[];
extern u8          D_801E5E7C[];
extern u8          D_801E5EA0[];
extern u8          D_801E5EAC[];
extern u32         D_801E5EFC[];
extern u8          D_801E5F0C;
extern u8          D_801E5F0D[];
extern Callback    D_801E5F14[];
extern Callback    D_801E5F24[];
extern Callback    D_801E5F30[];
extern Callback    D_801E5F3C[];
extern u32         D_801E5F48[3];
extern u32         D_801E5F54[3];
extern char        D_801E5F60[];
extern u32         D_801E5F68;
extern u8*         D_801E5FC0[];
extern u8          D_801E600C[];
extern u8          D_801E603C;
extern u8          D_801E6040;
extern s8          D_801E6044;
extern u8          D_801E6048;
extern u8          D_801E604C;
extern u8          D_801E6050;
extern u8          D_801E6054;
extern u8          D_801E6058;
extern s32         D_801E605C;
extern s32         D_801E6060;
extern u16         D_801E6064;
extern u8          D_801E606C;
extern u8          D_801E607C;
extern u8          D_801E6080;
extern u8          D_801E6088;
extern u8          D_801E608C;
extern u8          D_801E6094;
extern u8          D_801E60EC;
extern u8          D_801E60F0;
extern u8          D_801E60F4;
extern u8          D_801E60F8;
extern u8          D_801E60FC;
extern s16         D_801E6100[];
extern u8          D_801E6108;
extern u8          D_801E610C;
extern u8          D_801E6110;
extern u8          D_801E6144[0x80];
extern u8          D_801E61C4[0x80];
extern u8          D_801E6244[];
extern u8          D_801E6248[];
extern u8          D_801E6249[];
extern u8          D_801E6250;
extern u8          D_801E6254;
extern u8          D_801E6258;
extern u8          D_801E625C;
extern volatile u8 D_801E6260;
extern u8          D_801E6264[];

/* func_8014FF0C */
void UI_DrawAsciiString(s16 left, s16 top, s32 flags, u8* text);
void func_80164D2C(u8 idx, u8 sel, u8 val, u8* flags, u16* dst);
/* func_801650B4 */
bool Party_AddItem(s32 category, u8 item, u8 amount, s32 unused);
u32  Char_ClearStatus(u8 index, u16 mask, u8 mode);
/* func_8016628C */
s32  Party_CountItem(u8 category, u8 item, u8 mode);
/* func_80166A10 */
s32  Char_GetAbilityCost(u8 character_index, u8 ability_kind, u8 mode);
void Area_RunSetupStream(s32 cursor);
/* func_801AED54 */
void UI_DrawWindowOutline(s16 x, s16 y, s16 width, s32 height, s32 flags);
void UI_DrawSprite(s16 x, s16 y, u8 sprite_id, u8 flags);
void UI_DrawSpriteRun(s16 base_x, s16 base_y, const u8* record_table, u8 flags);
bool func_801AF494(u8 predicate_kind, u8 record_bit, u8 record_kind, u8 record_index);
s32  func_801AF5B0(s32 item_category, s32 character_index, s32 ability_kind);
void func_801AF930(s32 x, s32 y, u8 palette_index, u8 icon_index, u8* command_stream, u8 stat_value, u8 sprite_flag);
void func_801AFA1C(u8* arg0, u8 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);
s32  func_801AFD10(u8* column_counter, u8* row_offset, u8* row_flag, u8* position);
/* func_801BDB7C */
u8   Party_CountOrder(u8 mode);
void func_801C1254(u8 ability_id, u8 slot_index);
/* func_801D0EA0 */
void Shop_DispatchStep(void);
void func_801D0EDC(void);
void func_801D1000(void);
void func_801D10E4(void);
void func_801D1120(void);
void func_801D115C(void);
void func_801D1254(void);
void func_801D12C0(void);
void func_801D14B0(void);
void func_801D14EC(void);
void func_801D163C(void);
void func_801D1A90(void);
void func_801D1D60(void);
void func_801D1F74(void);
void func_801D20D0(void);
void func_801D23E4(void);
void func_801D26A8(void);
void func_801D27EC(void);
void func_801D2828(void);
void func_801D28D0(void);
void func_801D2D64(void);
void func_801D3014(void);
void func_801D3280(void);
void func_801D32C0(void);
void func_801D334C(void);
void func_801D349C(void);
void func_801D34F0(void);
void func_801D352C(void);
void func_801D3560(u16* result_code);
/* func_801D3654 */
s32  Shop_ApplyPercent(s32 value, s32 percent);
/* func_801D3688 */
u32  Shop_GetSellPrice(s32 item_kind, s32 quantity, s32 discount_flag);
void func_801D3710(void);
void func_801D3828(u8 record, u8 row, u8 color);
void func_801D39BC(void);
void func_801D39F8(void);
void func_801D3AA8(void);
void func_801D3AE4(void);
void func_801D3B98(void);
void func_801D3C9C(void);
void func_801D3D84(void);
void func_801D3FD4(void);
void func_801D408C(void);
void func_801D41B0(void);
void func_801D41EC(void);
void func_801D430C(void);
void func_801D43A4(void);
void func_801D43F0(void);
void func_801D446C(void);
void func_801D456C(void);
void func_801D4614(void);
/* func_801D46A4 */
void SAVE_DispatchState(void);
void func_801D46E0(void);
void func_801D472C(void);
void func_801D47AC(void);
void func_801D4970(void);
void func_801D4A3C(void);
void func_801D4BBC(void);
void func_801D4CF0(void);
void func_801D4DB4(void);
void func_801D4E74(void);
void func_801D50C0(void);
void func_801D51B8(void);
void func_801D5390(void);
void func_801D543C(void);
void func_801D5790(void);
void func_801D5894(void);
void func_801D5AD0(void);
void func_801D5BB0(void);
void func_801D5CB0(void);
void func_801D5D98(void);
void func_801D5E88(void);
void func_801D6018(void);
void func_801D60B0(void);
void func_801D6184(void);
void func_801D61C0(void);
void func_801D62DC(void);
void func_801D65A0(void);
void func_801D65EC(void);
void func_801D6668(void);
void func_801D66AC(void);
void func_801D66C8(void);
s32  func_801D66F8(u8* cursor_byte, s32 palette_index);
void func_801D68D0(s32 reset_slots);
/* func_801D69E0 */
void SAVE_BuildSlotImage(void);
void func_801D6CE4(u8 row_index, u8* source_record);
void func_801D6D6C(s32 strip_x, s32 strip_y);
void func_801D6E94(void);
void func_801D6F00(void);
void func_801D7080(void);
void func_801D7208(void);
void func_801D7344(void);
void func_801D7380(void);
void func_801D7444(void);
void func_801D76B8(void);
void func_801D7960(void);
void func_801D7AE4(void);
void func_801D7B74(void);
void func_801D7CC8(void);
void func_801D7D48(void);
/* func_801D7E08 */
void Menu_SwapBytes(u8* first, u8* second);
void func_801D7E1C(u8 slot, s32 x, s32 y, s32 style, u8 cursor);
void func_801D8050(s32 panel_x);
s32  func_801D81B4(u8* cursor_byte, s32 palette_index);
/* func_801D826C */
void Menu_DrawCharacterWindow(s32 px, s32 py, u8 character_slot, s32 shaded, s32 unused);
/* func_801D86D4 */
void Menu_DrawStatPanel(u16 panel_x, u16 panel_y, u8 palette_index);
/* func_801D8A0C */
void Shop_DrawEquipment(s16 x, s16 y, u8 record_index);
void func_801D8C58(s16 x, s16 y, u8 index, u8 flag);
/* func_801D8FC0 */
void Menu_DrawPortrait(s32 sprite_x, s32 sprite_y, s32 atlas_index, s32 shade_mode);
void func_801D910C(u16 sprite_x, u16 sprite_y, u8 atlas_index, u8 shade_mode);
/* func_801D9160 */
void Menu_DrawTintedLine(s16 line_x0, s16 line_y0, s16 line_x1, s16 line_y1, u8 color_r, u8 color_g, u8 color_b,
                         u8 tpage);
/* func_801DA00C */
void Menu_DrawIcon(u16 sprite_x, u16 sprite_y, u8 icon_column, u8 shade_mode);
void func_801DA120(u16 icon_x, u16 icon_y, s32 icon_u, s32 icon_v, u16 icon_clut, u8 icon_shade);
void Menu_DrawPlayTimeWindow(u16 panel_x, u16 panel_y);
void Menu_DrawCommandRow(s16 x, s16 y, u8 row, u8 selected, s32 unused);
/* func_801DA9C4 */
u16  Item_GetPrice(s32 category, s32 item_id);
/* func_801DAA78 */
s32  Char_GetExpForLevel(s32 character, s32 level);
void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, s32 window_style);
/* func_801DB938 */
void Menu_DrawRowIcons(u8* row_record, s32 palette_index);
/* func_801DB9F0 */
void Menu_DrawEquipStatWindow(s32 x, s32 y, u8 character_slot, s32 equip_slot, u8 item_id);
/* func_801DC1F4 */
void Menu_DrawWindowFrame(s16 x, s16 y, s32 width, s32 height);
void func_801DC6FC(MenuPanelTask* arg0);
/* func_801DDCB0 */
void SAVE_DrawSlot(u8 index, s32 left, s32 top, MenuListRow* row);
void func_801DDFB0(s16 x, s16 y, u32 flags, u8 row, u8 variant);
void func_801DE188(void);
void func_801DE1C4(void);
void func_801DE200(void);
void func_801DE3C8(void);
void func_801DE40C(void);
void func_801DE45C(void);
void func_801DE4C8(void);
void func_801DE850(void);
void func_801DE88C(void);
void func_801DE8E8(void);
void func_801DE944(void);
void func_801DEE20(void);
void func_801DEE64(void);
void func_801DF00C(s32 panel_x, s32 panel_y);
/* func_801DF464 */
void Menu_SwapBytes_801DF464(u8* first, u8* second);
s32  func_801DF478(void);
void func_801DF6A8(void);
void func_801DF90C(void);
void func_801DF978(void);
void func_801DF9B4(void);
void func_801DF9EC(void);
void func_801DFDB8(void);
void func_801DFDF4(void);
void func_801E0028(void);
void func_801E006C(void);
void func_801E032C(void);
void func_801E05E0(void);
void func_801E092C(void);
void func_801E0968(void);
void func_801E09F4(void);
void func_801E0BAC(void);
void func_801E0F28(void);
void func_801E0F78(void);
void func_801E112C(MenuPanelTask* task);
void func_801E1710(MenuPanelTask* task);
void func_801E1B80(s32 handler_index);
/* func_801E1BB8 */
void Menu_SwapBytes_801E1BB8(u8* first, u8* second);
void func_801E1BCC(void);
void func_801E1C88(void);
void func_801E1D84(void);
void func_801E1E80(s16 panel_x, s16 panel_y);
void func_801E200C(void);
void func_801E2048(void);
void func_801E2084(void);
void func_801E20CC(void);
void func_801E2114(void);
void func_801E2150(void);
void func_801E2474(void);
void func_801E254C(void);
void func_801E2590(void);
void func_801E25CC(void);
void func_801E2610(void);
void func_801E262C(void);
void func_801E2650(void);
void func_801E2724(void);
void func_801E27BC(void);
void func_801E2800(void);
void func_801E2808(void);
void func_801E2948(void);
void func_801E2988(void);
void func_801E29C8(void);
void func_801E2A30(void);
void func_801E2A70(void);
void func_801E2AB0(void);
void func_801E2B14(void);
void func_801E2B54(void);
void func_801E2BC4(void);
void func_801E2C18(void);
void func_801E2C9C(void);
void func_801E2CDC(void);
void func_801E2D1C(void);
void func_801E2D5C(void);
void func_801E2DB4(void);
void func_801E2E30(void);
void func_801E2E70(void);
void func_801E2EB0(void);
/* func_801E2F04 */
void Shop_DrawItems(ShopPanel* panel);
void func_801E31C4(void);
void func_801E3204(void);
void func_801E3244(void);
void func_801E3284(MenuPanelTask* task);
void func_801E36F8(void);
void func_801E3720(void);
void func_801E3774(void);
void func_801E37B4(void);
void func_801E37F4(MenuPanelTask* task);
void func_801E3B7C(void);
void func_801E3BA4(void);
void func_801E3BF8(void);
void func_801E3C38(void);
void func_801E3C78(void);
void func_801E3CB8(void);
void func_801E3CF8(void);
void func_801E3D4C(void);
void func_801E3D8C(void);
void func_801E3DCC(void);
void func_801E3E0C(void);
void func_801E3E4C(void);
void func_801E3EB4(void);
void func_801E3EF4(void);
void func_801E3F34(void);
void func_801E3F5C(void* arg0);
void func_801E4224(void);
void func_801E4278(void);
void func_801E42B8(void);
void func_801E42F8(void);
void func_801E4338(void);
void func_801E438C(void);
void func_801E43CC(void);
void func_801E440C(void);
void func_801E4460(void);
void func_801E44A0(void);
void func_801E44E0(void);
void func_801E4540(void);
void func_801E4580(void);
void func_801E45C0(MenuPanelTask* arg0);
s32  func_801E4C2C(s32 item_class);
/* func_801E4D4C */
s32  Party_HasSkill(s32 item_id);
void func_801E4DF4(MenuPanelTask* panel_task);
void func_801E4E9C(MenuPanelTask* panel_task);
void func_801E4FC8(s32 sprite_x, s32 sprite_y, u8 atlas_index, s32 shade_mode);
/* Returns the save probe's signed byte result; its caller tests it against -1. */
s8   CardAccessFile(s32 port, s32 name, s32 mode, s32 size, s32 offset);
u32  func_801EF200(void);
s32  func_801EF27C(s32, s32, u8*);

/* Decrement the countdown; on zero run the panel reset and latch D_80148650. */
static inline void MenuTickCountdown(void) {
    volatile u8* p   = &D_80148654;
    u8           val = *p - 1;

    *p = val;
    if (val == 0) {
        Menu_ResetPanelTasks();
        D_80148650 = 1;
    }
}

/* Fill the screen with an opaque black 320x240 tile. */
static inline void MenuClearScreenTile(void) {
    TILE* prim = (TILE*)g_GfxPrimCursor;

    SetTile(prim);
    SetSemiTrans(prim, 0);
    prim->w  = 320;
    prim->x0 = 0;
    prim->y0 = 0;
    prim->h  = 240;
    setRGB0(prim, 0, 0, 0);
    GFX_AddPrim(1, 0x10);
}

#endif
