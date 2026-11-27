#include "area120_13.h"

MATCH u8 func_801F36B0(void) {
    AreaEffect* effect;
    u8          scratch[32];
    u16         i;
    u8          handled;

    Camera_SetMatrix(scratch);

    handled = 0;
    effect  = MEM_PTR(AreaEffect, AREA_WORK);
    i       = 0;
    do {
        if (effect->active != 0) {
            switch (effect->state) {
                case 0:
                    effect->timer = 0x20;
                    effect->x     = SELF(Actor)->pos.x.fixed;
                    effect->z     = SELF(Actor)->pos.y.fixed + (effect->side != 0 ? TO_COORD_HALF(2) : -TO_COORD_HALF(2));
                    effect->y     = SELF(Actor)->pos.z.fixed + TO_COORD(384);
                    effect->speed = (((rand() & 0x1FF) - 0x180) << 16) / 32;
                    effect->state += 1;
                    break;
                case 1:
                    effect->x -= 0x2C00;
                    effect->z += effect->side != 0 ? -0xC00 : 0xC00;
                    effect->y += effect->speed;
                    if (--effect->timer == 0) {
                        effect->angle = (rand() & 0x1F) | (effect->side != 0 ? ANGLE_90 : -ANGLE_90);
                        effect->state += SELF(Actor)->unk_06 + 1;
                        effect->timer = 0x20;
                    }
                    break;
                case 2:
                    effect->x     = (rcos(effect->angle) << 4) + SELF(Actor)->pos.x.fixed - TO_COORD_HALF(5);
                    effect->z     = (rsin(effect->angle) << 4) + SELF(Actor)->pos.y.fixed;
                    effect->angle = (effect->angle + (effect->side != 0 ? 128 : -128)) & ANGLE_MASK;
                    if (--effect->timer == 0) {
                        effect->active = 0;
                    }
                    break;
                case 3:
                    effect->x     = (rcos(effect->angle) << 4) + SELF(Actor)->pos.x.fixed - TO_COORD_HALF(5);
                    effect->z     = (rsin(effect->angle) << 4) + SELF(Actor)->pos.y.fixed;
                    effect->angle = (effect->angle + (effect->side != 0 ? 128 : -128)) & ANGLE_MASK;
                    if (SELF(Actor)->unk_06 == 2) {
                        effect->speed = (rand() & 0x7F) + 128;
                        effect->timer = 16;
                        effect->state += 1;
                    }
                    break;
                case 4:
                    effect->x += (effect->speed * rcos(effect->angle)) >> 4;
                    effect->z += (effect->speed * rsin(effect->angle)) >> 4;
                    if (--effect->timer == 0) {
                        effect->active = 0;
                    }
                    break;
            }
            func_801F3468(effect);
            handled = 1;
        }
        effect++;
        i++;
    } while (i < AREA_EFFECT_COUNT);
    return handled;
}
