#include "area104_14.h"

/* Loader-verified payload id: 52 + area. */
u32 D_801F2C00 = 0x9C;

/* The torch gauge arrow cells, one per gauge state. */
TorchGaugeCells D_801F2C04 = {{{0xB0, 0x98}, {0xE0, 0x90}}};

/* Header string and its alignment bytes. */
u8 D_801F2C08[12] = {
    0x25, 0x30, 0x32, 0x64, 0x2E, 0x25, 0x64, 0x25, 0x64, 0x00, 0x10, 0x00,
};
