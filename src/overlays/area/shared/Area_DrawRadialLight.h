/* Draw the light in area172 and area188; verify both images after changes. */
static inline void Area_DrawRadialLight(void* position, s32 radius, s32 colors, s32 shift) {
    DVECTOR  screen;
    DVECTOR  point;
    DVECTOR  size;
    DVECTOR  scale;
    MATRIX   camera;
    POLY_G3* primitive;
    s32      angle;
    s32      i;
    s32*     pos;
    s16      origin;
    s32      flags;

    pos    = position;
    origin = (s16)radius;
    flags  = colors;

    GFX_AddDitheredDrawMode(2u, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x2C0, 0x100));
    Camera_SetMatrix(&camera);
    Camera_ProjectPoint(pos, &screen);
    size.vx = size.vy = origin;
    func_801AFFD8(pos, &size, &scale);
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
        setRGB0(primitive, (flags & 4) << shift, (flags & 2) << (shift + 1), (flags & 1) << (shift + 2));
        setRGB1(primitive, 0, 0, 0);
        setRGB2(primitive, 0, 0, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G3));
        i += 1;
    } while ((i & BYTE_MASK) < 32U);
}
