#include "game_00.h"

typedef struct WorkScript {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
    u8 unk_0C;
    u8 unk_0D;
} WorkScript;

MATCH void func_801A6C98(u8* record) {
    u8*         script;
    WorkScript* data;
    u8*         src;
    Actor*      work;
    void*       shared;
    u32         x;
    u32         y;
    s32         off;
    u8          index;
    Actor*      tail;
    Actor*      entry;

    script               = record;
    off                  = script[9] * 8;
    g_Task               = &D_80147A58[script[0xB]];
    g_CurrentActor       = &D_80147A58[script[0xB]];
    src                  = *(u8**)((u8*)g_AreaLoads[g_GameAreaId] + 8) + off;
    g_Task->direction_08 = script[0] & 0xF;

    func_801A4AA8();
    func_801A4B80(script[0xB]);
    func_8015AC8C(src);

    x    = script[2] << 16;
    work = g_Task;
    if (script[1] != 0) {
        x |= 32768;
    }
    work->pos.x.fixed = x;

    y = script[4] << 16;
    if (script[3] != 0) {
        y |= 32768;
    }
    work->pos.y.fixed        = y;
    COORD_INT(g_Task->pos.z) = Area_SampleHeight(work->pos.x.fixed, y);
    data                     = (WorkScript*)script;

    work                   = g_Task;
    work->header.mode      = data->unk_05;
    g_Task->header.step    = data->unk_07;
    g_Task->unk_06         = (data->unk_00 >> 4) - 1;
    tail                   = g_Task;
    shared                 = tail->range_54.table;
    tail->gravity          = 0;
    tail->unk_1C           = 0;
    tail->unk_18           = 0;
    FIELD(s32, tail, 0x70) = *(u8*)((u8*)shared + 2);

    index                           = data->unk_0B;
    entry                           = &D_80147A58[index];
    entry->unk_88                   = 0;
    entry->walk_dest_y              = 0;
    D_80147A58[index].walk_dest_x   = 0;
    D_80147A58[data->unk_0B].unk_77 = data->unk_0A;
    D_80147A58[data->unk_0B].unk_78 = data->unk_06;
    D_80147A58[data->unk_0B].unk_7C = (data->unk_0D | (data->unk_0C << 8));
    D_80147A58[data->unk_0B].unk_94 = 0x7F;

    func_801A4990((u8*)data + 8);
    g_Task->tint.signed_bytes.unk_5D = -0x80;
    g_Task->tint.signed_bytes.unk_5F = -0x80;
    g_Task->tint.signed_bytes.unk_5E = -0x80;
    g_Task->tint.bytes.flags         = 2;
}
