#ifndef OVERLAY_SCENARIO_SCENA16_00_H
#define OVERLAY_SCENARIO_SCENA16_00_H

/* The scena16 scenario overlay's local declarations: its palette and VRAM
 * records, the window words it shares and its prototypes. Only this image
 * includes the file. */

#define GAME_SCRATCH_BASE_SCALAR
#include "overlays/scenario/scenario.h"

#define SCENA16_PALETTE_SRC MEM_PTR(const volatile u16, 0x80033800u)
#define SCENA16_VRAM_BASE   (0x80010000u)

/* D_801448FC */
/* D_801448FF */
/* D_80144900 */
/* D_80144904 */
extern s32          g_AreaFocusY;
/* Retail-address data symbols, in address order. */
extern volatile u16 SCENA16_D_80010004;
extern volatile u16 SCENA16_D_80010006;
extern volatile u16 SCENA16_D_80010008;
extern u16          SCENA16_D_80010020;
extern volatile u16 SCENA16_D_80010022;
extern volatile u8  SCENA16_D_80143C30;
extern volatile u8  SCENA16_D_80143F03;
extern u8           SCENA16_D_80143F1D;
extern s32          SCENA16_D_80143F80;
extern volatile u8  SCENA16_D_80145988;
extern u32          SCENA16_D_80145EC4;
extern u32          SCENA16_D_80145EC8;
extern volatile u16 SCENA16_D_80146258;
extern volatile u32 SCENA16_D_80149308;
extern s32          SCENA16_D_8014930C;
extern volatile u32 SCENA16_D_80149314;
extern volatile u16 SCENA16_D_80149322;
extern volatile u16 SCENA16_D_8014932C;

/* Functions, in address order. */
void func_801F6C90(void);
void func_801F6CCC(void);
void func_801F6D90(void);
void func_801F6E30(void);
void func_801F6EB0(void);
void func_801F6F30(void);
void func_801F7144(void);
void func_801F7188(void);
void func_801F7230(void);
void func_801F7790(void);
void func_801F7CC4(void);
void func_801F8358(void* record);
s32  func_801F83A8(void);

#endif
