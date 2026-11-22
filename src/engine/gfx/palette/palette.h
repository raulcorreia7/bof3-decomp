#ifndef OVERLAY_GFX_PALETTE_H
#define OVERLAY_GFX_PALETTE_H

#include "types.h"

/* func_8014E284 */
void        GFX_PaletteReset(void);
/* func_8014E3A0 */
void        GFX_PaletteCopy(s32 slot);
/* func_8014E3F4 */
void        GFX_PaletteResetFades(void);
/* func_8014E484 */
extern void GFX_PaletteFreeSlot(s32 slot);
/* func_8014E4BC */
void        GFX_PaletteFreeSlotOwner(void* owner);
/* func_8014E528 */
extern void GFX_PaletteFreeAllSlots(void);
/* func_80166C48 */
void        GFX_PaletteLoad(u8* dst, s32 field);
/* func_8019651C */
s32         GFX_PaletteAllocFade(void* owner, s32 red, s32 green, s32 blue, s32 fade_flags);
/* func_80196670 */
void        GFX_PaletteFreeFade(u8 index);
/* func_80196718 */
void        GFX_PaletteFreeFadeTarget(void* owner);
/* func_80196784 */
u8          GFX_PaletteMarkCells(u8 mode, u8 value, u8 search);
/* func_801968BC */
u8          GFX_PaletteFindFreeCell(u8 mode);
/* func_80196B20 */
u8          GFX_PaletteFindCell(u8 value);
/* func_80196B9C */
void        GFX_PaletteUploadRows(void);
/* func_80196C8C */
void        GFX_PaletteUpdateAnimations(void);
/* func_80196CF0 */
u8          GFX_PaletteStartAnimation(u8* owner, u8* source_table);
/* func_80196D84 */
void        GFX_PaletteStepAnimation(u8 palette_slot);

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_GFX_PALETTE_H_LOCAL)
#define OVERLAY_GFX_PALETTE_H_LOCAL

void GFX_PaletteCopyAnimationColors(GraphicsPaletteAnimation* slot);
void GFX_PaletteUpload(void);

#endif
