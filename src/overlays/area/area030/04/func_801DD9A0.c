#include "area030_04.h"

/* Draw the fishing depth gauge. */
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
        if (((PADRup & g_PadStates[0].held) || (g_AreaScrollTargetCoordY.fixed == TO_COORD(21))) && (g_SpawnedActors[3].header.mode == 0)) {
            g_AreaCameraSpeed              = 0x40;
            g_AreaScrollTargetCoordY.fixed = TO_COORD(60);
            TASK(FishingState)->sub_index  = 1;
        } else {
            g_AreaCameraSpeed = 0x20;
            g_AreaScrollTargetCoordY.fixed -= COORD_HALF;
        }
    }
    i = 1;
    if (0x4 & g_FrameCount) {
        sxy_out     = (long*)sxy;
        depth_out   = &depth;
        flag_out    = &flag;
        gray        = 0x80;
        line_offset = TO_COORD(10);
        do {
            line = (LINE_F2*)g_GfxPrimCursor;
            i += 1;
            SetLineF2(line);
            pos.vx = -0x4000;
            y      = ((TO_COORD(62) - line_offset) >> 9) - 0x4000;
            pos.vy = y;
            pos.vz = 0;
            RotTransPers(&pos, sxy_out, depth_out, flag_out);
            setXY0(line, sxy[0], sxy[1]);
            setVector(&pos, -0x3100, y, 0);
            RotTransPers(&pos, sxy_out, depth_out, flag_out);
            line->x1 = sxy[0];
            line->y1 = sxy[1];
            setRGB0(line, gray, gray, gray);
            GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(LINE_F2));
            line_offset += TO_COORD(10);
        } while (i < 6);
    }
}
