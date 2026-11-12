#include "game_00.h"

MATCH u16 func_801AC8F0(ScriptState* state, u8 wanted_id, u8* base) {
    s32 offset = 0;
    u16 cursor;
    u8* record;
    s32 opcode;

    cursor = state->cursor;
    if (!(cursor & 0x4000)) {
        return cursor;
    }
    if (base[offset] == 0x0A && base[offset + 1] == wanted_id) {
        /* the cursor's own record already matches: use the shared exit */
        goto done;
    }
loop:
    record = base + (u16)offset;
    opcode = record[0];
    if ((opcode & BYTE_MASK) == 0xF8) {
        if (record[1] == 7) {
            offset += 5;
        } else {
            offset += 2;
        }
    } else if ((opcode - 14) < 2U) {
        if (record[3] & 0x2) {
            offset += 5;
        } else {
            offset += 4;
        }
    } else {
        offset += s_ScriptOpcodeOffsets[opcode & BYTE_MASK];
    }
    if (base[(u16)offset] != 0x0A || base[(u16)offset + 1] != wanted_id) {
        /* not the wanted id pair yet: keep seeking */
        goto loop;
    }
done:
    return offset;
}
