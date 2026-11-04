#ifndef OVERLAY_WORLD02_AREA103_13_H
#define OVERLAY_WORLD02_AREA103_13_H

/* The world02/area103/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "work/area_spad.h"

void      func_801F482C(void);
void      func_801F49A0(s32 arg);
void      func_801F4E70(s32 arg);
extern u8 D_801F5934[];
extern u8 D_801F5D64[];
extern u8 D_80145F09[][BATTLE_PARTY_STRIDE];
extern u8 D_801F5948[];
extern u8 D_801F5954[];
extern u8 D_801F5A28[];
extern s8 D_801F5D68[];

/* One of the three effect rows the area program keeps at the work window; the
 * rows are 0x4BC bytes apart and func_801F349C seeds the first 0x16 bytes. */
typedef struct AreaEffectRow {
    s32 x;      /* 0x00 - actor x */
    s32 y;      /* 0x04 - actor y */
    s32 z;      /* 0x08 - actor z plus 0x03800000 */
    s32 unk_0C; /* 0x0C */
    s16 angle;  /* 0x10 - row index * 0x1000 / 3 */
    s16 scale;  /* 0x12 */
    s16 unk_14; /* 0x14 */
    u8  pad_16[0x4BC - 0x16];
} AreaEffectRow;

/* The shared frame tail of the scripted scene steps: every fifth frame it
 * advances the cell palette cycle, then draws both cell layers and the overlay. */
static inline void Area_StepSceneFrame(void) {
    s32 beat = g_FrameCount / 5;

    if (g_FrameCount == beat * 5) {
        func_801F4E70(beat & 3);
    }
    func_801F49A0(0);
    func_801F49A0(1);
    func_801F482C();
}

#endif
