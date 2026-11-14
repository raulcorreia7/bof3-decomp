#ifndef GRAPHICS_VRAM_H
#define GRAPHICS_VRAM_H

#include "types.h"

/* Palette row sizes and chunk geometry used by the area and graphics loaders
 * and the menu palette writers (@source: wiki:formats/graphics). */
#define PAL_ROW_4BPP              0x20
#define PAL_ROW_8BPP              0x200

#define GRAPHICS_CHUNK_VRAM_WORDS 32
#define GRAPHICS_CHUNK_W_4BPP     128
#define GRAPHICS_CHUNK_W_8BPP     64
#define GRAPHICS_CHUNK_W_16BPP    32
#define GRAPHICS_CHUNK_H          32

/* The stage palette: 32 CLUT rows of 256 words at VRAM (0, 480), uploaded by GFX_UploadPalette
 * (@source: wiki:systems/rendering). Text CLUT words are 0x7800 | column, the first row. */
#define STAGE_PALETTE_Y           480
#define STAGE_PALETTE_CLUT        0x7800

/* CLUT (0, 494) the area sprite draws share (@source: wiki:formats/assets). */
#define WORLD_SPRITE_CLUT         0x7B80

/* How many palette cells a sprite owns (work byte 0x28): one 16-color cell, a whole 256-color row, or runs of 2, 4
 * and 8 cells. Area_BuildClut builds its CLUT word from it and GFX_AllocPaletteCell finds a free run of that size. */
typedef enum PaletteType {
    PALETTE_TYPE_CELL    = 0,
    PALETTE_TYPE_ROW     = 1,
    PALETTE_KIND_CELLS_2 = 2,
    PALETTE_TYPE_CELLS_4 = 3,
    PALETTE_TYPE_CELLS_8 = 4,
} PaletteType;

#endif
