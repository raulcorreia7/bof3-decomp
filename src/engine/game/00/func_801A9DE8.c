#include "game_00.h"

/* Entity spawn counter cell in scratchpad (signed 16-bit slot index). */
/* The entry cell at 0x1F800002 is stored through D_1F800002 and read back signed. */
MATCH u8 func_801A9DE8(GameCursorState* state, const u8* table, u8 value) {
    u8 byte;
    u8 result;

    byte = table[state->index_0A];
    switch (byte) {
        case 0xF0:
            Game_ClearScriptActive();
            return value;
        case 0xF1:
            Game_SetScriptActive();
            return value;
        case 0xF2: {
            u8 next;

            value         = *(table + state->index_0A + 1);
            next          = *(table + state->index_0A + 2);
            state->unk_07 = next;
            if (next != 0) {
                if (Actor_GetType() != 2)
                    func_801ABBA8(state, value);
                else
                    func_801C5DFC(value);
            }
            state->index_0A += 2;
            break;
        }
        case 0xF3: {
            u8 next;

            value         = *(table + state->index_0A + 1);
            next          = *(table + state->index_0A + 2);
            state->unk_07 = next;
            if (next != 0) {
                if (Actor_GetType() != 2) {
                    Actor* work;
                    s32    den;

                    func_801ABBA8(state, value);
                    work     = g_SpadWork;
                    den      = work->unk_09 * state->unk_07;
                    work->vz = ((s16)((*(table + state->index_0A + 3) << 8) | *(table + state->index_0A + 4)) -
                                (s16)work->z.part.integer) /
                               den;
                    state->flags_00 |= GAME_CURSOR_FLAG_MOVING;
                } else {
                    s16* counter;
                    s32  step;

                    counter    = (s16*)&D_1F800000;
                    *counter   = g_SpadWork->z.part.integer;
                    D_1F800002 = (s16)((*(table + state->index_0A + 3) << 8) | *(table + state->index_0A + 4));
                    func_801C5DFC(value);
                    step       = (0x80 / g_AreaCameraStep) * D_80143FC3;
                    D_80143F5C = ((SP_REF(s16, 0x2u) - *counter) << 16) / step;
                    state->flags_00 |= 0x40;
                }
            }
            state->index_0A += 4;
            break;
        }
        case 0xF4: {
            Actor* work;

            state->flags_00 |= GAME_CURSOR_FLAG_MOVING;
            g_SpadWork->unk_09 = *(table + state->index_0A + 3);
            if (g_SpadWork->unk_09 == 0)
                g_SpadWork->unk_09 = 1;
            work         = g_SpadWork;
            work->vz     = ((s16)((*(table + state->index_0A + 1) << 8) | *(table + state->index_0A + 2)) -
                            (s16)work->z.part.integer) /
                           work->unk_09;
            work->unk_0C = 0;
            work->unk_10 = 0;
            state->index_0A += 3;
            break;
        }
        case 0xF5:
            state->flags_00 &= 0x7F;
            break;
        case 0xF9: {
            Actor* work;

            if ((func_801AC33C(*(table + state->index_0A + 1), *(table + state->index_0A + 2)) << 24) != 0) {
                state->index_0A--;
                return 0xFF;
            }
            state->index_0A += 2;
            work  = g_SpadWork;
            value = work->direction_08 & 7;
            break;
        }
        case 0xFA: {
            u8     next;
            Actor* work;

            value         = *(table + state->index_0A + 1);
            next          = *(table + state->index_0A + 2);
            state->unk_07 = next;
            if (next != 0) {
                if (Actor_GetType() != 2) {
                    func_801ABBA8(state, value);
                    state->flags_00 |= GAME_CURSOR_FLAG_MOVING;
                } else {
                    func_801C5DFC(value);
                    g_AreaCameraHeightStep = 0;
                    state->flags_00 |= 0x40;
                }
            }
            work                 = g_SpadWork;
            work->vz             = 0;
            work->z.part.integer = (u16)((*(table + state->index_0A + 3) << 8) | *(table + state->index_0A + 4));
            state->index_0A += 4;
            break;
        }
        case 0xFD:
            if (func_8014DAEC() != 0)
                return value;
            g_SpadWork->option_flags |= ACTOR_OPT_WAIT_STREAM;
            state->index_0A--;
            break;
        case 0xFE: {
            Actor* work;
            u16    mode;

            if (g_GameStateIndex != GAME_REQUEST_BATTLE) {
                mode                = Actor_ReadState();
                work                = g_SpadWork;
                GAME_ENTITY_COUNTER = mode;
                /* FAKE: counter store before work read. */
                MATCH_BARRIER();
                if ((work->script_pc != mode) && (mode == *(table + state->index_0A + 2)))
                    SND_PlayCue((u16)(0x200u | *(table + state->index_0A + 1)));
            }
            state->index_0A += 2;
            break;
        }
        case 0xF6:
            g_SceneState.state_04 = *(table + state->index_0A + 1);
            /* Retail shares the +1 cursor advance with case 0xF8. */
            goto advance_one;
        case 0xF7: {
            s32 hi;
            s32 lo;

            hi = (*(table + state->index_0A + 1) << 16) | (*(table + state->index_0A + 2) << 8);
            lo = (*(table + state->index_0A + 3) << 16) | (*(table + state->index_0A + 4) << 8);
            func_801ABD68(hi, lo, *(table + state->index_0A + 5), state);
            value = *(table + state->index_0A + 6);
            if (Actor_GetType() == 1)
                state->unk_07 = 1;
            state->index_0A += 6;
            break;
        }
        case 0xF8:
            func_801AC768(state, *(table + state->index_0A + 1), *(table + state->index_0A + 2),
                          *(table + state->index_0A + 3), *(table + state->index_0A + 4));
        advance_one:
            state->index_0A += 1;
            break;
        case 0xFB: {
            Actor* work;

            work   = g_SpadWork;
            result = Area_SetCellPalette(work->x.part.integer, work->y.part.integer);
            /* Retail shares the cue check with case 0xFC. */
            goto queue_cue;
        }
        case 0xFC: {
            Actor* work;

            work   = g_SpadWork;
            result = Area_ClearCellPalette(work->x.part.integer, work->y.part.integer);
        }
        queue_cue:
            if (result != 0)
                SND_PlayCue(EMI_CUE_ID(1, 3));
            return value;
        case 0xFF:
            state->index_0A--;
            return value;
    }
    return value;
}
