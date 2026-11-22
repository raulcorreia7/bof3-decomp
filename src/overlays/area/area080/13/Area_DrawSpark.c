#include "area080_13.h"

MATCH void Area_DrawSpark(AreaSparkSlot* spark) {
    CVECTOR  color;
    CVECTOR  delta;
    MATRIX   camera;
    LINE_F2* line;
    POLY_G4* poly;
    s8       i;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Camera_SetMatrix(&camera);
    i = 2;
    do {
        spark->origin_trail[i + 1] = spark->origin_trail[i];
        spark->pos_trail[i + 1]    = spark->pos_trail[i];
        i--;
    } while (i >= 0);
    Camera_ProjectPoint(&spark->origin.x.fixed, &spark->origin_trail[0]);
    Camera_ProjectPoint(&spark->pos.x.fixed, &spark->pos_trail[0]);

    delta = spark->color;
    color = delta;
    delta.r >>= 2;
    delta.g >>= 2;
    delta.b >>= 2;

    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 1);
    setXY2(line, spark->origin_trail[0].vx, spark->origin_trail[0].vy, spark->pos_trail[0].vx, spark->pos_trail[0].vy);
    setRGB0(line, color.r, color.g, color.b);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F2));

    for (i = 0; i < 3; i++) {
        poly = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        setXY2(poly, spark->origin_trail[i].vx, spark->origin_trail[i].vy, spark->pos_trail[i].vx, spark->pos_trail[i].vy);
        setRGB0(poly, color.r, color.g, color.b);
        setRGB1(poly, color.r, color.g, color.b);
        color.r -= delta.r;
        color.g -= delta.g;
        color.b -= delta.b;
        poly->x2 = spark->origin_trail[i + 1].vx;
        poly->y2 = spark->origin_trail[i + 1].vy;
        poly->x3 = spark->pos_trail[i + 1].vx;
        poly->y3 = spark->pos_trail[i + 1].vy;
        setRGB2(poly, color.r, color.g, color.b);
        setRGB3(poly, color.r, color.g, color.b);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    }
}
