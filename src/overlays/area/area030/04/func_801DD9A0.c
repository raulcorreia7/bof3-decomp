#include "area030_04.h"

/* Resets the area-030 depth gauge when its state byte is clear and,
 * when the gauge flag is set, draws five shaded horizontal segments projected
 * from the depth steps. */
MATCH void func_801DD9A0(void) {
    SVECTOR  pos;
    s16      sxy[4];
    long     depth;
    long     flag;
    long*    flag_out;
    long*    depth_out;
    long*    sxy_out;
    s32      y;
    s32      line_offset;
    s32      i;
    s32      gray;
    LINE_F2* line;

    if (g_AreaCameraMoving == 0) {
        if (((PADRup & g_InputHeld) || (g_AreaScrollTargetY == 0x150000)) && (D_80144125 == 0)) {
            g_AreaCameraStep            = 0x40;
            g_AreaScrollTargetY         = 0x3C0000;
            FISHING_STATE->sub_index_03 = 1;
        } else {
            u32* work = &g_AreaScrollTargetY;

            g_AreaCameraStep = 0x20;
            *work -= 0x8000;
        }
    }
    i = 1;
    if (4 & g_FrameCount) {
        sxy_out     = (long*)sxy;
        depth_out   = &depth;
        flag_out    = &flag;
        gray        = 0x80;
        line_offset = 0xA0000;
        do {
            line = (LINE_F2*)g_GfxPrimCursor;
            i += 1;
            SetLineF2(line);
            pos.vx = -0x4000;
            y      = ((0x3E0000 - line_offset) >> 9) - 0x4000;
            pos.vy = y;
            pos.vz = 0;
            RotTransPers(&pos, sxy_out, depth_out, flag_out);
            setXY0(line, sxy[0], sxy[1]);
            pos.vx = -0x3100;
            pos.vy = y;
            pos.vz = 0;
            RotTransPers(&pos, sxy_out, depth_out, flag_out);
            line->x1 = sxy[0];
            line->y1 = sxy[1];
            setRGB0(line, gray, gray, gray);
            GFX_AddPrim(2U, 0x10U);
            line_offset += 0xA0000;
        } while (i < 6);
    }
}
