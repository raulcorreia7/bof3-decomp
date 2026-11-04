#include "game_00.h"

MATCH u8 func_801A9944(void* sub, s32 target, u8 value) {
    u8*    target_bytes;
    u16    next_cursor_e7;
    u16    next_cursor_e8;
    u16    next_cursor_e0e3;
    u16    next_cursor_e2;
    u16    next_cursor;
    Actor* spad_work_ea;
    Actor* spad_work_e5;
    Actor* spad_work_eb;
    Actor* spad_work_ec;
    Actor* spad_work_ed;
    Actor* spad_work_ee;
    Actor* spad_work_e4;
    u8     high_byte;
    u8     state_flags;
    u8     opcode;
    u8     updated_flags;
    u8     low_byte;
    u8     selection;
    u8     result;
    /* FAKE: keep the E9 command pointer in the retail a3 register. */
    MATCH_REG(u8*, target_entry_e9, "a3");
    u8* target_entry_ea;
    /* FAKE: keep the E2 command pointer in the retail v1 register. */
    MATCH_REG(u8*, target_entry_e2, "v1");
    ScriptState* state;

    state        = sub;
    target_bytes = (u8*)target;
    opcode       = *(target_bytes + state->cursor);
    selection    = value;
    switch (opcode) {
        case 0xE1:
            state->unk_05 = (u8)g_SpadWork->direction_08;
            func_8015BAC4((target_bytes + state->cursor)[1]);
            state->unk_08 = (target_bytes + state->cursor)[2];
            func_801A17A0((u8*)state);
            state->flag_00 = (u8)((state->flag_00 & ~ACTOR_FLAG_SCRIPT_REQUEST) | ACTOR_FLAG_SCRIPT_PENDING);
            state->cursor  = (u16)(state->cursor + 2);
            return 0xFFU;
        case 0xE0:
            state->unk_05  = (u8)g_SpadWork->direction_08;
            state->flag_00 = (u8)(state->flag_00 | ACTOR_FLAG_MOVING);
            selection      = D_80145E98 ^ 4;
            func_8015BAC4(selection);
            goto block_5; /* E0 and E3 share the operand-read tail */
        case 0xE3:
            state->unk_05 = (u8)(g_SpadWork->direction_08 & 7);
        block_5:
            next_cursor_e0e3 = state->cursor + 1;
            state->cursor    = next_cursor_e0e3;
            state->unk_08    = (s16) * (target_bytes + (next_cursor_e0e3 & HALF_MASK));
            func_801A17A0((u8*)state);
            state_flags    = state->flag_00;
            updated_flags  = state_flags & ~ACTOR_FLAG_SCRIPT_REQUEST;
            state->flag_00 = updated_flags;
            if (g_SpadWork->option_flags & ACTOR_OPT_NO_SCRIPT_START) {
                state->flag_00 = (u8)(state_flags & ~(ACTOR_FLAG_SCRIPT_REQUEST | ACTOR_FLAG_SCRIPT_PENDING));
            } else {
                state->flag_00 = (u8)(updated_flags | ACTOR_FLAG_SCRIPT_PENDING);
            }
            goto block_29; /* every command that keeps the selection shares the return */
        case 0xE2:
            target_entry_e2 = target_bytes + state->cursor;
            /* FAKE: retain the second 16-bit load at sub+0xA. */
            next_cursor_e2  = *MATCH_VOLATILE_PTR(u16, &state->cursor);
            high_byte       = target_entry_e2[1];
            low_byte        = target_entry_e2[2];
            next_cursor_e2  = (u16)(next_cursor_e2 + 2);
            state->cursor   = next_cursor_e2;
            state->unk_08   = (s16)(low_byte | (high_byte << 8));
            goto block_29; /* every command that keeps the selection shares the return */
        case 0xE6:
            g_SpadWork->flags_00 = 0;
            goto block_29; /* every command that keeps the selection shares the return */
        case 0xE5:
            spad_work_e5 = g_SpadWork;
            g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            spad_work_e5->unk_01 = (u8)spad_work_e5->unk_03;
            goto block_29; /* every command that keeps the selection shares the return */
        case 0xE7:
            next_cursor_e7 = state->cursor + 1;
            state->cursor  = next_cursor_e7;
            func_801A2788((s32) * (target_bytes + (next_cursor_e7 & HALF_MASK)));
            state->unk_07 = 0;
            return 0xFFU;
        case 0xE9:
            target_entry_e9 = target_bytes + state->cursor;
            if ((Actor_RunHandler((s32)state, ((s8*)target_entry_e9)[1], ((s8*)target_entry_e9)[2],
                                  (s16)((target_entry_e9[3] << 8) | target_entry_e9[4]),
                                  (s16)(s32)(s16)(target_entry_e9[6] | (target_entry_e9[5] << 8)),
                                  (target_bytes + state->cursor)[7], (target_bytes + state->cursor)[8])
                 << 0x18) != 0) {
                state->cursor = (u16)(state->cursor - 1);
                result        = 0xFF;
                if (Actor_GetType() == 2) {
                    return g_SpadWork->direction_08;
                }
                return result;
            }
            next_cursor = state->cursor + 8;
            goto block_28; /* E9 and EA share the cursor store */
        case 0xEB:
            spad_work_eb = g_SpadWork;
            spad_work_eb->flags_00 ^= ACTOR_FLAG_HIDDEN;
            goto block_29; /* every command that keeps the selection shares the return */
        case 0xEC:
            spad_work_ec               = g_SpadWork;
            spad_work_ec->option_flags = (u8)(spad_work_ec->option_flags ^ ACTOR_OPT_NO_SCRIPT_START);
            goto block_29; /* every command that keeps the selection shares the return */
        case 0xED:
            spad_work_ed               = g_SpadWork;
            spad_work_ed->option_flags = (u8)(spad_work_ed->option_flags ^ ACTOR_OPT_ROUTE_LOCKED);
            goto block_29; /* every command that keeps the selection shares the return */
        case 0xEE:
            spad_work_ee               = g_SpadWork;
            spad_work_ee->option_flags = (u8)(spad_work_ee->option_flags ^ ACTOR_OPT_WAIT_STREAM);
            goto block_29; /* every command that keeps the selection shares the return */
        case 0xE8:
            next_cursor_e8 = state->cursor + 1;
            state->cursor  = next_cursor_e8;
            state->unk_04  = (u8) * (target_bytes + (next_cursor_e8 & HALF_MASK));
            if (Actor_GetType() == 2) {
                selection = 0;
                goto block_29; /* every command that keeps the selection shares the return */
            }
            return selection;
        case 0xEF:
            state->flag_00 = (u8)(state->flag_00 | ACTOR_FLAG_MOVING);
            goto block_29; /* every command that keeps the selection shares the return */
        case 0xE4:
            spad_work_e4               = g_SpadWork;
            SP_REF(u8, 0x3)            = 0xFF;
            spad_work_e4->option_flags = (u8)(spad_work_e4->option_flags & 0xD7);
            state->flag_00             = (u8)(state->flag_00 & 0xBF);
            goto block_29; /* every command that keeps the selection shares the return */
        case 0xEA:
            spad_work_ea = g_SpadWork;
            if (spad_work_ea->unk_06 != 0xA) {
                target_entry_ea = target_bytes + state->cursor;
                GFX_AllocPaletteFade((u8*)spad_work_ea, target_entry_ea[1], target_entry_ea[2], target_entry_ea[3],
                                     target_entry_ea[4]);
            } else {
                spad_work_ea->tint.bytes.unk_5D = (target_bytes + state->cursor)[1];
                g_SpadWork->tint.bytes.unk_5E   = (target_bytes + state->cursor)[2];
                g_SpadWork->tint.bytes.unk_5F   = (target_bytes + state->cursor)[3];
            }
            next_cursor = state->cursor + 4;
        block_28:
            state->cursor = next_cursor;
        default:
        block_29:
            result = selection & BYTE_MASK;
            return result;
    }
}
