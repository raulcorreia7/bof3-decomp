#include "area168_13.h"

MATCH void func_801F44F4(void) {
    s32  entry;
    s32  pair;
    s32  quad;
    s32* code;

    entry                  = SELF(Actor)->pos.x.part.integer;
    pair                   = entry * 2;
    SELF(Actor)->direction = SELF(Actor)->pos.y.part.integer == 0;

    SELF(Actor)->pos.x.part.integer = AREA168_ENTRY_TABLE(u8, 0x50, pair);
    SELF(Actor)->pos.y.part.integer = AREA168_ENTRY_TABLE(u8, 0x51, pair);
    SELF(Actor)->pos.z.part.integer = -Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) / 2 - AREA168_ENTRY_TABLE(u16, 0x30, pair);
    quad                            = entry * 4;
    SELF(Actor)->gravity            = AREA168_ENTRY_TABLE(s32, 0x3C, quad);
    SELF(Actor)->screen_y           = 0;
    SELF(Actor)->param.unk_0B       = AREA168_ENTRY_TABLE(s32, 0x9C, quad);

    code = &AREA168_ENTRY_TABLE(s32, 0xB0, quad);
    func_801A4BC0(SELF(Actor)->pos.x.part.integer, SELF(Actor)->pos.y.part.integer, *code);
    func_801A4BC0(SELF(Actor)->pos.x.part.integer, SELF(Actor)->pos.y.part.integer + 1, *code);
    SELF(Actor)->header.step += 1;
    Area_Update();
}
