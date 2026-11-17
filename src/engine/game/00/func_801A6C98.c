#include "game_00.h"

typedef struct SpawnScript {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 mode;
    u8 unk_06;
    u8 step;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 index;
    u8 unk_0C;
    u8 unk_0D;
} SpawnScript;

MATCH void func_801A6C98(u8* record) {
    u8*          script;
    SpawnScript* data;
    u8*          src;
    Actor*       work;
    void*        shared;
    u32          x;
    u32          y;
    s32          off;
    u8           index;
    Actor*       tail;
    Actor*       entry;

    script               = record;
    off                  = script[9] * 8;
    g_Task               = &D_80147A58[script[0xB]];
    g_CurrentActor       = &D_80147A58[script[0xB]];
    src                  = *(u8**)((u8*)g_AreaLoads[g_GameAreaId] + 8) + off;
    g_Task->direction_08 = script[0] & 0xF;

    Actor_ResetMotion();
    func_801A4B80(script[0xB]);
    SYS_InitScratchpad(src);

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
    data                     = (SpawnScript*)script;

    work                = g_Task;
    work->header.mode   = data->mode;
    g_Task->header.step = data->step;
    g_Task->unk_06      = (data->unk_00 >> 4) - 1;
    tail                = g_Task;
    shared              = tail->range_54.table;
    tail->gravity       = 0;
    tail->unk_1C        = 0;
    tail->unk_18        = 0;
    tail->state_70.word = *(u8*)((u8*)shared + 2);

    index                          = data->index;
    entry                          = &D_80147A58[index];
    entry->unk_88                  = 0;
    entry->walk_dest_y             = 0;
    D_80147A58[index].walk_dest_x  = 0;
    D_80147A58[data->index].unk_77 = data->unk_0A;
    D_80147A58[data->index].unk_78 = data->unk_06;
    D_80147A58[data->index].unk_7C = (data->unk_0D | (data->unk_0C << 8));
    D_80147A58[data->index].unk_94 = 0x7F;

    Actor_SetOptionFlags((u8*)data + 8);
    g_Task->tint.signed_bytes.delta.red   = -0x80;
    g_Task->tint.signed_bytes.delta.blue  = -0x80;
    g_Task->tint.signed_bytes.delta.green = -0x80;
    g_Task->tint.bytes.flags              = 2;
}
