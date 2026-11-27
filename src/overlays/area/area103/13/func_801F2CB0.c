#include "area103_13.h"

MATCH void func_801F2CB0(void) {
    Pos3            pos;
    MATRIX          matrix;
    AreaSpinEffect* effect;
    u8              i;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    pos.x = SELF(Actor)->pos.x.fixed;
    pos.y = SELF(Actor)->pos.y.fixed;
    pos.z = SELF(Actor)->pos.z.fixed;
    func_801F352C(&pos, SELF(Actor)->unk_0A << 2, 0x80, 0);
    Camera_SetMatrix(&matrix);
    effect = (AreaSpinEffect*)AREA_WORK;
    for (i = 0; i < 3; i++) {
        func_801F2FB8(effect);
        effect->unk_14 += 4;
        SELF(Actor)->unk_0A++;
        if (SELF(Actor)->unk_0A > 32) {
            SELF(Actor)->unk_0A = 32;
            effect->unk_14      = 0x80;
        }
        effect->pos.z -= 0x70000;
        effect->angle += 64;
        effect->scale -= 0x18;
        effect++;
    }
    if (!(--SELF(Actor)->timer & 0xFF)) {
        SELF(Actor)->timer = 32;
        SELF(Actor)->header.mode += 1;
    }
}
