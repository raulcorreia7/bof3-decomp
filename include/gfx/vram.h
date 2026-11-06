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

/* CLUT (0, 494) the area sprite draws share (@source: wiki:formats/assets). */
#define WORLD_SPRITE_CLUT         0x7B80

#endif
