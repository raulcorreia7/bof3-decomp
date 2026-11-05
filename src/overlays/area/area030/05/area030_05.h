#ifndef OVERLAY_WORLD00_FISHING_05_H
#define OVERLAY_WORLD00_FISHING_05_H

/* The world00/area030/05 world overlay's local declarations: the work-cost rows, the
 * payload prologue and the area data symbols. Only this image includes the
 * file. */

#include "overlays/area/world00.h"
#include <stdio.h>
#include "menu/draw.h"

/* Work-cost row: two cost bytes followed by two three-byte runs. */
typedef struct AreaCost {
    u8 cost_00;
    u8 cost_01;
    u8 run_02[3];
    u8 run_05[3];
} AreaCost;

/* Payload prologue: the loader-verified module id and the "*%2d" format the
 * cost printers pass to sprintf. */
typedef struct EmiOverlayHead {
    u32  id;        /* 0x00 */
    char format[5]; /* 0x04 "*%2d" */
    u8   unk_09[3];
} EmiOverlayHead;

/* Data, in address order. */
extern EmiOverlayHead D_800F5000;
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
void func_800F606C(s32 arg0);
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
bool Party_AddItem(s32 category, u8 item, u8 amount, s32 unused);
/* func_8016628C */
s32  Party_CountItem(u8 category, u8 item, u8 mode);
void func_801D799C(s16 arg0, s16 arg1, s32 arg2, s32 arg3);
s32  func_801D9534(s16 arg0, u16 arg1, s16 arg2, s16 arg3, s32 arg4);

#endif
