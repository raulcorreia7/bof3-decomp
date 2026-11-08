#include "game_00.h"

MATCH u8* func_801A4844(u8* script) {
    u8* cursor;
    u8  opcode;
    u8  active;
    s32 value;
    s32 param;

    active = 1u;
    value  = script[1];
    /* FAKE: barrier keeps the script[1] load apart from the u8 copy, so the
     * raw word stays in v0 and the copy masks into s1. */
    FAKE_BARRIER();
    cursor = script + 2;
    param  = (u8)value;
    while (active != 0u) {
        /* FAKE: keep the dead script[1] copy live across the call in s1. */
        FAKE_USE(param);
        opcode = *cursor;
        if (opcode >= 0xF0u) {
            switch (opcode - 0xF0u) {
                case 0x5:
                    cursor += 1;
                    active = 0u;
                    break;
                case 0x6:
                    cursor += 2;
                    break;
                case 0x7:
                case 0x8:
                    cursor += 1;
                    break;
                case 0x0:
                case 0x1:
                case 0x4:
                case 0x9:
                case 0xA:
                    cursor = func_801A44A4(cursor);
                    break;
            }
        } else {
            cursor += s_ScriptOpcodeLengths[opcode >> 4];
        }
    }
    return cursor;
}
