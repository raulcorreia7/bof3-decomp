#include "game_00.h"

MATCH bool func_801B6258(void) {
    s8     prev;
    s32    cur;
    u8     saved;
    Actor* work;
    u8     sel;

    if (D_80146256 != 0) {
        return 0;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[FIELD_INPUT_INTERACT]) == 0) {
        return 0;
    }
    saved = SELF(Actor)->direction;
    ((s32 (*)(s32))func_801B4494)(0x30);
    cur  = func_801B4150();
    prev = cur;
    if ((prev != -1) || (SELF(Actor)->direction = saved, cur = func_801B4150(), (s8)cur != prev)) {
        func_801B60DC(cur & BYTE_MASK);
        return 1;
    }
    if ((((s32 (*)(s32))func_801B4494)(0x51) & BYTE_MASK) && (((s32 (*)(u16, u16))Game_ScenarioCall)(SP_REF(u16, 0x0u), GAME_ENTITY_ENTRY_DATA) != 0)) {
        Actor_RequestRoute(SELF(Actor)->direction);
        ACTOR_CLEAR_STEP();
        return 1;
    }
    SELF(Actor)->direction = saved;
    if (!((((s32 (*)(s32))func_801B4494)(0x50) & BYTE_MASK) || (((s32 (*)(s32))func_801B4494)(0x53) & BYTE_MASK) || (((s32 (*)(s32))func_801B4494)(0x55) & BYTE_MASK) ||
          (((s32 (*)(s32))func_801B4494)(0x52) & BYTE_MASK))) {
        return 0;
    }
    sel  = FIELD(u8, func_801B5C54(), 0x2u) & 0xF;
    work = SELF(Actor);
    if ((work->direction == sel) || (sel == 8)) {
        work->header.mode = 7;
        ACTOR_CLEAR_STEP();
        return 1;
    }
    work->direction = saved;
    return 0;
}
