#ifndef OVERLAY_WORLD02_AREA103_13_H
#define OVERLAY_WORLD02_AREA103_13_H

/* The world02/area103/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

u8        Area_FindTaggedPartySlot(void);
void      func_801F482C(void);
void      func_801F49A0(s32 arg);
void      func_801F4E70(s32 frame);
extern u8 D_801F5934[];
extern u8 D_801F5948[];
extern u8 D_801F5954[];
extern u8 D_801F5A14[];
extern u8 D_801F5A15[];
extern u8 D_801F5A28[];
extern u8 D_801F5D64[];
extern s8 D_801F5D68[];

/* One of the three effect rows the area program keeps at the work window; the
 * rows are 0x4BC bytes apart and func_801F349C seeds the first 0x16 bytes. */
typedef struct AreaEffectRow {
    Point3l pos;    /* 0x00 - actor position, z plus 0x03800000 */
    s32     unk_0C; /* 0x0C */
    s16     angle;  /* 0x10 - row index * 0x1000 / 3 */
    s16     scale;  /* 0x12 */
    s16     unk_14; /* 0x14 */
    u8      pad_16[0x4BC - 0x16];
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

void func_801F349C(void);

void func_801F352C(s32* pos, s16 radius, u8 center_shade, u8 rim_shade);
void func_801F5174(s32 arg0, s32 arg1);
void func_801F53F0(s32 arg0);

#endif
