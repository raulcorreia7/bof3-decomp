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
    u8     type;
    u16    result;

    sel = func_801B5C54();
    if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
        Actor_RequestRoute(g_Task->direction);
    } else {
        work = g_Task;
        Actor_RequestScript(((work->direction >> 1) + 0x10));
    }
    value = FIELD(s16, sel, 0x4u);
    if (((value & 0x8000) != 0) && ((type = FIELD(u8, sel, 0x6u)) != GAME_NONE)) {
        switch (type) {
            case 0:
                Message_Request(value & 0xFFF);
                break;
            case 1:
                Message_StartAreaMessage(value & 0xFFF);
                break;
            case 2:
                rec.callback_index = GAME_NONE;
                base               = g_AreaLoads[LOHU(g_GameAreaId)];
                list               = FIELD(u32*, base, 0x4u);
                entry              = list[FIELD(u16, sel, 0x4u) & 0xFFF];
                g_CurrentActor     = &rec;
                Area_RunSetupRecords((u8*)entry);
                result = rec.unk_7C;
                if (result != 0xFFFF) {
                    Message_StartAreaMessage(result & 0xFFF);
                }
                g_Game.current->u.field.type  = g_CurrentActor->callback_index;
                state                         = g_Task;
                g_Game.current->u.field.value = FIELD(u16, sel, 0x4u);
                state->header.step++;
        }
        g_Task->header.step++;
    } else {
        Message_Request(MSG_SYSTEM_000);
    }
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    g_Task->header.step++;
}
