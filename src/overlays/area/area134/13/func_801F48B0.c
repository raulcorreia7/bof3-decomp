#include "area134_13.h"

MATCH void func_801F48B0(void) {
    AreaQuadSprite* record;

    record = (AreaQuadSprite*)func_801F4938();
    if (record == NULL) {
        return;
    }
    record->unk_00[0] = SELF(Actor)->unk_06;
    record->unk_00[1] = 0;
    record->unk_00[2] = 0;
    record->shade     = 0x80;
    record->half_size = 0x80;
    record->origin.x  = SELF(Actor)->pos.x.fixed;
    record->origin.y  = SELF(Actor)->pos.y.fixed;
    record->unk_10    = 0;
    record->unk_18    = 0x1800;
    record->unk_1C    = 0;
    record->unk_20    = 0;
}
