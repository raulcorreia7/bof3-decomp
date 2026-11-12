#ifndef OVERLAY_BMAGIC_MAGIC060_00_H
#define OVERLAY_BMAGIC_MAGIC060_00_H

/* The bmagic/magic060/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC060_STEP_COUNT 5

typedef struct Magic060Steps {
    Callback steps[MAGIC060_STEP_COUNT];
} Magic060Steps;

extern Magic060Steps D_801EEC04;

/* The text rows func_801EF174 stamps beside the character name: WEAK, EXP, a single 0x60 glyph, ITEM,
 * POINT and a bar. D_801F0B8C is the twelve-glyph bar four bytes into D_801F0B88, the one-glyph bar. */
extern u8 D_801F0B64[];
extern u8 D_801F0B6C[];
extern u8 D_801F0B70[];
extern u8 D_801F0B74[];
extern u8 D_801F0B7C[];
extern u8 D_801F0B88[];
extern u8 D_801F0B8C[];

extern Callback D_801F0BBC[];
void            func_801F012C(void);

extern Callback D_801F0BCC[];
void            func_801F0428(void);

void func_801EF174(void);
void func_801EF2DC(void);
void func_801EF590(u8* text, s32 x, s32 y);
void func_801EF76C(u8* text, s32 x, s32 y);

#endif
