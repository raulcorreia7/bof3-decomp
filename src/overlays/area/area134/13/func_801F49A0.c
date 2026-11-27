#include "area134_13.h"

/* Steps the quad sprites whose owner byte is the acting row: grow, fade, shrink, then free. */
MATCH s32 func_801F49A0(void) {
    MATRIX          matrix;
    AreaQuadSprite* work;
    u8              found;
    u8              i;

    /* FAKE: retail reserves 16 bytes no local here uses. */
    FAKE_STACK_PADS(u8, 16);

    Camera_SetMatrix(&matrix);
    found = 0;
    work  = (AreaQuadSprite*)AREA_WORK;
    i     = 0;
    do {
        if (work->unk_00[0] != SELF(Actor)->unk_06) {
            goto next;
        }
        found = 1;
        switch (work->unk_00[1]) {
            case 0:
                work->half_size += 4;
                if ((work->unk_00[2] += 1) == 8) {
                    work->unk_00[1] += 1;
                }
                break;
            case 1:
                work->shade -= 8;
                if ((work->unk_00[2] += 1) == 16) {
                    work->unk_00[1] += 1;
                }
                break;
            case 2:
                work->half_size -= 16;
                if ((work->unk_00[2] += 1) == 24) {
                    work->unk_00[1] += 1;
                }
                break;
            case 3:
                work->half_size -= 16;
                if ((work->unk_00[2] += 1) == 32) {
                    work->unk_00[0] = 0;
                }
                break;
        }
        work->origin.x += work->unk_18;
        work->half_size += 8;
        work->origin.y += work->unk_1C;
        work->unk_10 = Area_HeightSample(work->origin.x, work->origin.y) << 16;
        func_801F46EC(work);
    next:
        work++;
        i++;
    } while ((i & BYTE_MASK) < 32);
    return found;
}
