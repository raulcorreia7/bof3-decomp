/* Draws a filled disc as a fan of 32 semi-transparent Gouraud triangles around
 * (x, y) with the given radius; the centre takes center_shade and the
 * rim takes rim_shade. One definition shared by the several overlays; every change
 * here must verify every member. */
/* func_801F8C04 (scena03), func_801F2F04 (area032), func_801F3D90 (area108) */
MATCH void GFX_DrawShadedDisc(s16 x, s16 y, s16 radius, u8 center_shade, u8 rim_shade) {
    POLY_G3* packet;
    u16      angle;
    u16      next;
    u16      other;
    s32      scale;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, FONT_TPAGE_X, FONT_TPAGE_Y) & 0xFFFF, 0);
    GFX_AddPrim(1u, 0x0Cu);
    angle = 0;
    do {
        packet = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(packet);
        SetSemiTrans(packet, 1);
        next  = angle + 128;
        other = (next & ANGLE_MASK);
        setXY2(packet, x, y, (s16)(x + ((radius * rcos((u16)angle)) >> 0x0C)),
               (s16)(y + ((radius * rsin((u16)angle)) >> 0x0C)));
        packet->x2 = (s16)(x + ((radius * rcos((u16)other)) >> 0x0C));
        scale      = rsin((u16)other);
        setRGB0(packet, center_shade, center_shade, center_shade);
        setRGB1(packet, rim_shade, rim_shade, rim_shade);
        setRGB2(packet, rim_shade, rim_shade, rim_shade);
        packet->y2 = (s16)(y + ((radius * scale) >> 0x0C));
        GFX_AddPrim(1u, 0x1Cu);
        angle = next;
    } while ((u16)angle < ONE);
}
