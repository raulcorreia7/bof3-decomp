#include "game_00.h"

MATCH void func_801B2DDC(void) {
    Actor  rec;
    Actor* state;
    Actor* work;
    void*  sel;
    void*  base;
    u32*   list;
    u32    entry;
    s16    value;
    u8     kind;
    u16    result;

    sel = func_801B5C54();
    if (g_GameRequestFlags & 0x1) {
        func_801B5BDC(g_Task->direction_08);
    } else {
        work = g_Task;
        Actor_RequestScript(((work->direction_08 >> 1) + 0x10));
    }
    value = FIELD(s16, sel, 0x4u);
    if (((value & 0x8000) != 0) && ((kind = FIELD(u8, sel, 0x6u)) != GAME_NONE)) {
        switch (kind) {
            case 0:
                Message_Request(value & 0xFFF);
                break;
            case 1:
                Message_StartAreaMessage(value & 0xFFF);
                break;
            case 2:
                rec.callback_index = 0xFF;
                base               = g_AreaLoads[LOHU(g_GameAreaId)];
                list               = FIELD(u32*, base, 0x4u);
                entry              = list[FIELD(u16, sel, 0x4u) & 0xFFF];
                g_CurrentActor     = &rec;
                func_801A3F3C((u8*)entry);
                result = rec.unk_7C;
                if (result != 0xFFFF) {
                    Message_StartAreaMessage(result & 0xFFF);
                }
                g_Game.current->u.field.kind_11E  = g_CurrentActor->callback_index;
                state                             = g_Task;
                g_Game.current->u.field.value_120 = FIELD(u16, sel, 0x4u);
                state->header.step++;
        }
        g_Task->header.step++;
    } else {
        Message_Request(0);
    }
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    g_Task->header.step++;
}
