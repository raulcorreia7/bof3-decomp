#include "area168_13.h"

MATCH void func_801F44F4(void) {
    s32  entry;
    s32  pair;
    s32  quad;
    s32* code;

    entry                = g_Task->pos.x.part.integer;
    pair                 = entry * 2;
    g_Task->direction_08 = g_Task->pos.y.part.integer == 0;

    g_Task->pos.x.part.integer = AREA168_ENTRY_TABLE(u8, 0x50, pair);
    g_Task->pos.y.part.integer = AREA168_ENTRY_TABLE(u8, 0x51, pair);
    g_Task->pos.z.part.integer =
        -Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) / 2 - AREA168_ENTRY_TABLE(u16, 0x30, pair);
    quad                 = entry * 4;
    g_Task->gravity      = AREA168_ENTRY_TABLE(s32, 0x3C, quad);
    g_Task->screen_y     = 0;
    g_Task->param.unk_0B = AREA168_ENTRY_TABLE(s32, 0x9C, quad);

    code = &AREA168_ENTRY_TABLE(s32, 0xB0, quad);
    func_801A4BC0(g_Task->pos.x.part.integer, g_Task->pos.y.part.integer, *code);
    func_801A4BC0(g_Task->pos.x.part.integer, g_Task->pos.y.part.integer + 1, *code);
    g_Task->header.step += 1;
    Area_Update();
}
