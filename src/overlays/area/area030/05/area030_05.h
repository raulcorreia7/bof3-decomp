#ifndef OVERLAY_WORLD00_FISHING_05_H
#define OVERLAY_WORLD00_FISHING_05_H

/* The world00/area030/05 world overlay's local declarations. */

#include "overlays/area/world00.h"
#include <stdio.h>
#include "menu/draw.h"

/* The fishing shop messages. */
typedef enum FishingShopMessageId {
    FISHING_SHOP_MSG_CONFIRM_ALL      = 69,
    FISHING_SHOP_MSG_CONFIRM_ITEM     = 70,
    FISHING_SHOP_MSG_TRADE_ITEM_LABEL = 71,
    FISHING_SHOP_MSG_NEEDED_LABEL     = 72,
    FISHING_SHOP_MSG_OWNED_LABEL      = 73,
    FISHING_SHOP_MSG_YES_NO           = 74,
    FISHING_SHOP_MSG_NONE_OWNED       = 75,
    FISHING_SHOP_MSG_NONE_EQUIPPED    = 76,
    FISHING_SHOP_MSG_TOO_GREEDY       = 77,
    FISHING_SHOP_MSG_QUANTITY_PROMPT  = 78,
} FishingShopMessageId;

/* Work-cost row: two cost bytes followed by two three-byte runs. */
typedef struct AreaCost {
    u8 cost_00;
    u8 cost_01;
    u8 run_02[3];
    u8 run_05[3];
} AreaCost;

/* Payload prologue: the loader-verified module id and the "*%2d" format the cost printers pass to sprintf. */
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

void func_800F5048(void);
void func_800F50B4(void);
void func_800F510C(void);
void func_800F5138(void);
void func_800F51BC(void);
void func_800F550C(void);
void func_800F5828(void);
void func_800F5AD8(void);
void func_800F5BA4(void);
void func_800F5BE0(void);
void func_800F5D98(void);
void func_800F5E44(void);
void func_800F606C(s32 draw_all);
void func_800F63CC(u16 x, u16 y, u8 color);
u8   func_800F65A8(s32 slot, s32 amount);
u8   func_800F66D4(void);
void func_800F6730(void);
void func_800F6A84(u16 x, u16 y);
void func_800F6C5C(void);
void func_800F6EE0(u16 x, u16 y);
void func_800F7094(s32 x, s32 y, s32 kind, s32 value, u8 selected);
void func_800F7100(void);
/* func_801650B4 */
bool Item_Add(s32 category, u8 item, u8 amount, s32 unused);
/* func_8016628C */
s32  Item_Count(u8 category, u8 item, u8 mode);
void func_801D799C(s16 x, s16 y, u8 height, u8 style);
s32  func_801D9534(s16 frame_x, u16 frame_y, s16 frame_width, s16 frame_height, u8 frame_mode);

#endif
