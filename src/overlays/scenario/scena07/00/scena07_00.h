#ifndef OVERLAY_SCENARIO_SCENA07_00_H
#define OVERLAY_SCENARIO_SCENA07_00_H

/* The scenario/scena07/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"
#define SCRATCH_ROW_STRIDE 0x1C
#define SCRATCH_ROW_OFFSET 0x00

void            func_801F3C3C(s32 value);
void            func_801F8358(void);
extern u16      D_800E4C1E;
extern s8       D_80144EC0;
extern u32      D_801F6C00;
extern Callback D_801FDD3C[];
extern Callback D_801FDD48[];
extern Callback D_801FDD50[];
extern Callback D_801FDD70[];
extern Callback D_801FDD8C[];
extern Callback D_801FDDAC[];
extern Callback D_801FDDB4[];
extern Callback D_801FDDC0[];
extern Callback D_801FDDC8[];
extern Callback D_801FDDD0[];
extern void (*D_801FDDF0[])(u8* row);
extern Callback  D_801FDE10[];
extern Callback  D_801FDE1C[];
extern u8        D_801FDE88[4];
/* D_801FDF8C */
extern SceneFunc g_SceneActorDispatch[];
extern u8        D_801FDFC4;

/* The record D_801FDFBC points at: a world position the burst draws around and its size. */
typedef struct Scena07Burst {
    s32 x;
    s32 y;
    s32 z;
    s32 unk_0C;
    u16 unk_10;
} Scena07Burst;

extern Scena07Burst* D_801FDFBC;
void                 func_801F97E0(Scena07Burst* burst);

void func_801F81D4(u8* row);

u8*       func_801F8394(void);
void      func_801F83D0(u8* row);
void      func_801F88B8(void* table);
void      func_801F8BE8(void* table);
void      func_801FA38C(void);
extern u8 D_801FDFC8;

/* The panel's sprite rows, 0x18 bytes each: the panel steps shift them down and draw the first 31. */
#define SCENA07_PANEL_ROWS MEM_PTR(void, 0x800E48E0u)

/* The panel fade step func_801F72E0 and func_801F80F0 share: draw the panel table, dim it by 12 and
 * advance the actor when its countdown ends. Every change must keep both members matching. */
#define SCENA07_PANEL_FADE_STEP()      \
    func_801F88B8(SCENA07_PANEL_ROWS); \
    func_801F8BE8(SCENA07_PANEL_ROWS); \
    D_800E4C1E -= 0xC;                 \
    if (--g_Task->timer == 0) {        \
        g_Task->header.step++;         \
    }

/* The panel brighten step func_801F724C and func_801F805C share: draw the panel table, brighten it by 6
 * and re-arm the countdown to 0x20 when it ends. Every change must keep both members matching. */
#define SCENA07_PANEL_BRIGHTEN_STEP()  \
    func_801F88B8(SCENA07_PANEL_ROWS); \
    func_801F8BE8(SCENA07_PANEL_ROWS); \
    D_800E4C1E += 6;                   \
    if (--g_Task->timer == 0) {        \
        g_Task->timer = 32;            \
        g_Task->header.step++;         \
    }
u8   func_801F85D8(void);
void func_801F9DA8(void);
u8   func_801F9EFC(void);

/* D_801FDD14 */
extern Callback g_SceneEntityDispatch[];

extern u8       D_80144EB8[];
extern u8       D_80146865;
extern u8       D_80146866;
extern u8       D_80146867;
extern u8       D_80146874;
extern u8       D_80146875;
/* D_801FDFA0 */
extern u8       g_ScenePositionTable;
/* D_801FDFA8 */
extern Callback g_ScenePositionDispatch[];
extern void (*D_801FDDF0[])(u8* row);
void func_801F81D4(u8* row);

s8 func_801A7AD8(u8* entry, u8 count, u16 x, u16 y);

#endif
