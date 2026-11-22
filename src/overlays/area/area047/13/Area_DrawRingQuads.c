#include "area047_13.h"

MATCH void Area_DrawRingQuads(AreaRingRow* row) {
    DVECTOR  screen;
    DVECTOR  size;
    DVECTOR  scale;
    POLY_G4* prim;
    s32      row_size;
    s32      pass_size;
    u16      pass;
    u16      angle;
    u16      next;
    u16      other;

    Camera_ProjectPoint((s32*)row, &screen);
    pass = 0;
    do {
        row_size = row->size;
        if (pass == 0) {
            pass_size = row_size + row->size_delta;
            size.vx   = pass_size;
        } else {
            pass_size = row_size - row->size_delta;
            size.vx   = pass_size;
        }
        size.vy = (u16)row->size;
        Game_ProjectWorldPoint(row, &size, &scale);
        angle = 0;
        do {
            prim  = GFX_BeginPolyG4(1);
            next  = angle + (ONE / 32);
            other = next & ANGLE_MASK;
            setXY4(prim, screen.vx + FIXED_MUL((s16)scale.vx, rcos(angle)), screen.vy + FIXED_MUL((s16)scale.vx, rsin(angle)), screen.vx + FIXED_MUL((s16)scale.vx, rcos(other)),
                   screen.vy + FIXED_MUL((s16)scale.vx, rsin(other)), screen.vx + FIXED_MUL((s16)scale.vy, rcos(angle)), screen.vy + FIXED_MUL((s16)scale.vy, rsin(angle)),
                   screen.vx + FIXED_MUL((s16)scale.vy, rcos(other)), screen.vy + FIXED_MUL((s16)scale.vy, rsin(other)));
            setRGB0(prim, 0, 0, 0);
            setRGB1(prim, 0, 0, 0);
            setRGB2(prim, row->shade, row->shade, row->shade);
            setRGB3(prim, row->shade, row->shade, row->shade);
            GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
            angle = next;
        } while ((u16)angle < ONE);
        pass++;
    } while (pass < 2);
}
