#include "area082_13.h"

/* func_801F5428 */
MATCH void Area_DrawGradient(s32 colors) {
    POLY_G4* polygon;
    s32      texturePage;
    u32      packedColors = colors;
    u8       topRed, topGreen, topBlue, bottomRed, bottomGreen, bottomBlue;

    texturePage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(6, texturePage);
    polygon = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(polygon);
    topRed      = (packedColors & 31) << 3;
    topGreen    = (packedColors >> 2) & 0xF8;
    topBlue     = (packedColors >> 7) & 0xF8;
    bottomRed   = (packedColors >> 13) & 0xF8;
    bottomGreen = (packedColors >> 18) & 0xF8;
    bottomBlue  = (packedColors >> 23) & 0xF8;
    setXY4(polygon, 0, 0, SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    polygon->r0 = polygon->r1 = topRed;
    polygon->g0 = polygon->g1 = topGreen;
    polygon->b0 = polygon->b1 = topBlue;
    polygon->r2 = polygon->r3 = bottomRed;
    polygon->g2 = polygon->g3 = bottomGreen;
    polygon->b2 = polygon->b3 = bottomBlue;
    GFX_AddPrim(6, sizeof(POLY_G4));
    texturePage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(6, texturePage);
}
