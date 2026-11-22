#include "area103_13.h"

MATCH void func_801F2E5C(void) {
    Pos3 pos;
    /* FAKE: unused frame, 8 bytes between pos and matrix. */
    FAKE_STACK_PADS(s32, 2);
    MATRIX          matrix;
    AreaSpinEffect* effect;
    s32             timer;
    u8              i;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    pos.x = TASK(Actor)->pos.x.fixed;
    pos.y = TASK(Actor)->pos.y.fixed;
    pos.z = TASK(Actor)->pos.z.fixed;
    func_801F352C(&pos, TASK(Actor)->timer << 2, 0x80, 0);
    Camera_SetMatrix(&matrix);
    effect = (AreaSpinEffect*)AREA_WORK;
    for (i = 0; i < 3; i++) {
        func_801F2FB8(effect);
        FIELD(u16, effect, 0x10) += 0x40;
        FIELD(u16, effect, 0x14) -= 8;
        effect++;
    }
    ACTOR_COUNT_DOWN(TASK(Actor), timer, timer);
    if (!(timer & 0xFF)) {
        TASK(Actor)->header.mode += 1;
    }
}
