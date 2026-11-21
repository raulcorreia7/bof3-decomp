/* Draws a ring of 32 semi-transparent triangles around the projected point: the radius is the point projected at the given size plus the frame parity, and the centre corner takes its colour from the low three bits of the flags (red, green, blue). Every change must verify sce15ef0 and area098. */
/* GFX_DrawColorFan (sce15ef0, area098) */
MATCH void GFX_DrawColorFan(s32* pos, s16 origin, s32 flags) {
    DVECTOR  screen;
    DVECTOR  point;
    DVECTOR  size;
    DVECTOR  scale;
    MATRIX   camera;
    POLY_G3* primitive;
    s32      angle;
    s32      i;

    GFX_AddDitheredDrawMode(2u, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x2C0, 0x100));
    Camera_SetMatrix(&camera);
    Camera_ProjectPoint(pos, &screen);
    size.vx = size.vy = origin;
    Game_ProjectWorldPoint(pos, &size, &scale);
    scale.vx += g_FrameCount & 1;
    point.vx = screen.vx + scale.vx;
    point.vy = screen.vy;
    angle    = 0;
    i        = 0;
    do {
        primitive = GFX_BeginPolyG3(1);
        setXY2(primitive, screen.vx, screen.vy, point.vx, point.vy);
        angle += 128;
        point.vx      = screen.vx + (((s16)scale.vx * rcos((u16)angle)) >> 0xC);
        point.vy      = screen.vy + (((s16)scale.vx * rsin((u16)angle)) >> 0xC);
        primitive->x2 = point.vx;
        primitive->y2 = point.vy;
        setRGB0(primitive, (flags & 4) << 5, (flags & 2) << 6, (flags & 1) << 7);
        setRGB1(primitive, 0, 0, 0);
        setRGB2(primitive, 0, 0, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G3));
        i += 1;
    } while ((i & BYTE_MASK) < 32U);
}
