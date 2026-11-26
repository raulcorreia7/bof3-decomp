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
        Actor_RequestRoute(SELF(Actor)->direction);
    } else {
        work = SELF(Actor);
        Script_Request(((work->direction >> 1) + 0x10));
    }
    value = FIELD(s16, sel, 0x4u);
    if (((value & 0x8000) != 0) && ((type = FIELD(u8, sel, 0x6u)) != GAME_NONE)) {
        switch (type) {
            case 0:
                UI_MessageRequest(value & 0xFFF);
                break;
            case 1:
                UI_MessageStartArea(value & 0xFFF);
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
                    UI_MessageStartArea(result & 0xFFF);
                }
                g_Game.current->u.field.type  = g_CurrentActor->callback_index;
                state                         = SELF(Actor);
                g_Game.current->u.field.value = FIELD(u16, sel, 0x4u);
                state->header.step++;
        }
        SELF(Actor)->header.step++;
    } else {
        UI_MessageRequest(MSG_SYSTEM_000);
    }
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    SELF(Actor)->header.step++;
}
