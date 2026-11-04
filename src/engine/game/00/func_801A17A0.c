#include "game_00.h"

MATCH s32 func_801A17A0(u8* entry_record) {
    u16    flags;
    u32    entry;
    s32*   list;
    u16    mode;
    s32    result;
    Actor* work;

    flags = FIELD(u16, entry_record, 8u);
    entry_record[0] &= 0xEF;
    if (flags == 0xFFFF) {
        return 0;
    }
    if (flags & 0x8000) {
        entry = (u32)g_AreaLoads[g_GameAreaId];
        list  = (s32*)FIELD(u32, entry, 4u);
        func_801A3F3C((u8*)list[flags & 0xFFF]);
        if (FIELD(u16, entry_record, 8u) & 0x8000) {
            /* the entry keeps its 0x8000 state: skip the selection step */
            goto stored;
        }
    }
    mode = FIELD(u16, entry_record, 8u);
    if ((mode & 0x2000) == 0) {
        Message_StartAreaMessage((s16)mode);
    } else {
        Resource_RequestArea(mode & 0xFFF);
    }
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
stored:
    work                         = g_SpadWork;
    FIELD(u16, entry_record, 8u) = flags;
    if (work->option_flags & ACTOR_OPT_NO_SCRIPT_START) {
        entry_record[0] &= 0xDF;
        result = 1;
    } else {
        result = 1;
    }
    g_ScriptWorkRecord = (s8*)g_CurrentActor;
    return result;
}
