#include "area098_13.h"

MATCH u8 func_801F42E8(void) {
    MATRIX          matrix;
    AreaStreakSlot* slot;
    u8              i;
    u8              drawn;

    Area_SetCameraMatrix(&matrix);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256), NULL);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(DR_MODE));
    drawn = 0;
    slot  = MEM_PTR(AreaStreakSlot, AREA_WORK);
    for (i = 0; i < 24; slot++, i++) {
        if (slot->active != 0) {
            drawn = 1;
            func_801F4220(slot);
            switch (slot->kind) {
                case 0:
                    slot->head.vx += slot->vel[0];
                    slot->head.vy += slot->vel[1];
                    slot->head.vz += slot->vel[2];
                    slot->head_shade -= 10;
                    if (--slot->life == 0) {
                        slot->life = 8;
                        slot->kind++;
                    }
                    break;
                case 1:
                    slot->tail.vx += slot->vel[0];
                    slot->tail.vy += slot->vel[1];
                    slot->tail.vz += slot->vel[2];
                    slot->tail_shade -= 10;
                    if (--slot->life == 0) {
                        slot->active = 0;
                    }
                    break;
            }
        }
    }
    return drawn;
}
