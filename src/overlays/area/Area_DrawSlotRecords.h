/* Draws the sixteen 0x2C-byte records at 0x800E48C0 with DRAW_SLOT, turning each record's angle by 0x10. */
/* AREA_DRAW_SLOT_RECORDS (area098 0x801F5940, area188 0x801F44B4) */
#define AREA_DRAW_SLOT_RECORDS(DRAW_SLOT)                     \
    MATRIX matrix;                                            \
    s32    spin;                                              \
    s32    angle;                                             \
    s32    i;                                                 \
    GFX_AddDitheredDrawMode(2, GetTPage(0, 1, 0x380, 0x100)); \
    Area_SetCameraMatrix(&matrix);                            \
    spin  = 0x800E48C0;                                       \
    i     = 0;                                                \
    angle = 0x800E48E4;                                       \
    do {                                                      \
        DRAW_SLOT(spin);                                      \
        spin += 0x2C;                                         \
        FIELD(u16, angle, 0) += 0x10;                         \
        i += 1;                                               \
        angle += 0x2C;                                        \
    } while ((i & 0xFF) < 0x10U);
