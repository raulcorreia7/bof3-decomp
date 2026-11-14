#ifndef OVERLAY_WORLD00_FISHING_05_H
#define OVERLAY_WORLD00_FISHING_05_H

/* The world00/area030/05 world overlay's local declarations: the work-cost rows, the
 * payload prologue and the area data symbols. Only this image includes the
 * file. */

#include "overlays/area/world00.h"
#include <stdio.h>
#include "menu/draw.h"

/* The fishing shop messages: indexes into the message table the pond loads at
 * AREA_MESSAGE_TABLE (the AREA030, AREA089 and AREA129 payload). */
typedef enum FishingShopMessageId {
    FISHING_SHOP_MESSAGE_CONFIRM_ALL      = 69,
    FISHING_SHOP_MESSAGE_CONFIRM_ITEM     = 70,
    FISHING_SHOP_MESSAGE_TRADE_ITEM_LABEL = 71,
    FISHING_SHOP_MESSAGE_NEEDED_LABEL     = 72,
    FISHING_SHOP_MESSAGE_OWNED_LABEL      = 73,
    FISHING_SHOP_MESSAGE_YES_NO           = 74,
    FISHING_SHOP_MESSAGE_NONE_OWNED       = 75,
    FISHING_SHOP_MESSAGE_NONE_EQUIPPED    = 76,
    FISHING_SHOP_MESSAGE_TOO_GREEDY       = 77,
    FISHING_SHOP_MESSAGE_QUANTITY_PROMPT  = 78,
} FishingShopMessageId;

/* Work-cost row: two cost bytes followed by two three-byte runs. */
typedef struct AreaCost {
    u8 cost_00;
    u8 cost_01;
    u8 run_02[3];
    u8 run_05[3];
} AreaCost;

/* Payload prologue: the loader-verified module id and the "*%2d" format the
 * cost printers pass to sprintf. */
typedef struct EMIOverlayHead {
    u32  id;        /* 0x00 */
    char format[5]; /* 0x04 "*%2d" */
    u8   unk_09[3];
} EMIOverlayHead;

/* Data, in address order. */
extern EMIOverlayHead D_800F5000;
extern AreaCost       D_801E2F7C[];
extern u8             D_801E2F7D[];
extern u8             D_801E2F7E[][8];
extern u8             D_801E2F81[][8];
extern u8             D_801E3134[][10];

/* func_800F5048 */
void Fishing_ShopOpen(void);
/* func_800F50B4 */
void Fishing_ShopInit(void);
/* func_800F510C */
void Fishing_ShopWaitOpen(void);
/* func_800F5138 */
void Fishing_ShopChooseTrade(void);
/* func_800F51BC */
void Fishing_ShopChooseItem(void);
/* func_800F550C */
void Fishing_ShopChooseQuantity(void);
/* func_800F5828 */
void Fishing_ShopConfirm(void);
/* func_800F5AD8 */
void Fishing_ShopTooGreedy(void);
/* func_800F5BA4 */
void Fishing_ShopConfirmAll(void);
/* func_800F5BE0 */
void Fishing_ShopConfirmAllInput(void);
/* func_800F5D98 */
void Fishing_ShopExit(void);
/* func_800F5E44 */
void Fishing_ShopDrawBackdrop(void);
/* func_800F606C */
void Fishing_ShopDrawTradeList(s32 draw_all);
/* func_800F63CC */
void Fishing_ShopDrawListWindow(u16 x, u16 y, u8 color);
/* func_800F65A8 */
u8   Fishing_ShopTradeBlocked(s32 slot, s32 amount);
/* func_800F66D4 */
u8   Fishing_ShopItemCount(void);
/* func_800F6730 */
void Fishing_ShopDrawNeeded(void);
/* func_800F6A84 */
void Fishing_ShopDrawNeededWindow(u16 x, u16 y);
/* func_800F6C5C */
void Fishing_ShopDrawQuantity(void);
/* func_800F6EE0 */
void Fishing_ShopDrawQuantityWindow(u16 x, u16 y);
/* func_800F7094 */
void Fishing_ShopDrawItemIcon(s32 x, s32 y, s32 kind, s32 value, u8 selected);
/* func_800F7100 */
void Fishing_ShopTakeTradeItems(void);
/* func_801650B4 */
bool Item_Add(s32 category, u8 item_id, u8 count, s32 unused);
/* func_8016628C */
s32  Item_Count(u8 category, u8 item_id, u8 mode);
/* func_801D799C */
void Fishing_DrawWindowFill(s16 x, s16 y, u8 height, u8 style);
/* func_801D9534 */
s32  Fishing_DrawWindowFrame(s16 frame_x, u16 frame_y, s16 frame_width, s16 frame_height, u8 frame_mode);

#endif
