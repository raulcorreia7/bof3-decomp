#include "game_00.h"

/* nonmatching unmeasured: tried 70.14%: single return value exit via break; retail keeps base pointer s2 for base[1]
 * (4(s2)); gcc folds it to the D_80145EC8 symbol. */
#ifdef NON_MATCHING
NON_MATCHING u8 func_801AB458(GameCursorState* state, const u8* table, u8 value) {
    u8    byte;
    u8    flag;
    u8    slot;
    s32   delta_x;
    s32   delta_y;
    u32   sel;
    u32   span_y;
    s32   step;
    s32   span;
    s32   buf[3];
    void* entry;
    u32*  list;

    byte = table[state->index_0A];
    switch (byte) {
        case 0x80:
            g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
            break;
        case 0x81:
            g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            break;
        case 0x82:
            state->flags |= ACTOR_FLAG_FADE_WHITE;
            break;
        case 0x83:
            state->flags |= ACTOR_FLAG_FADE_BLACK;
            break;
        case 0x84: {
            volatile Actor* work;

            func_801ABF30(buf, table[state->index_0A + 1], table[state->index_0A + 2]);
            work              = SCRATCH_WORK;
            work->pos.x.fixed = buf[0];
            work->pos.y.fixed = buf[1];
            work->pos.z       = buf[2];
            state->index_0A += 2;
            break;
        }
        case 0x85: {
            s32* base;

            base = &D_80145EC4;
            if ((g_AreaScrollTargetX != base[0]) || (g_AreaScrollTargetY != base[1])) {
                delta_x = g_AreaScrollTargetX - base[0];
                delta_x = ABS(delta_x);
                sel     = (u32)delta_x >> 15;
                delta_y = g_AreaScrollTargetY - base[1];
                delta_y = ABS(delta_y);
                span_y  = (u32)delta_y >> 15;
                if ((sel & 0xFF) < (span_y & 0xFF)) {
                    sel = span_y;
                }
                Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
                g_AreaScrollTargetX = base[0];
                g_AreaScrollTargetY = base[1];
                span                = Area_SampleHeight(base[0], base[1]);
                g_AreaCameraStep    = 0x20;
                step                = sel & 0xFF;
                if (step == 0) {
                    g_AreaCameraHeightStep = 0;
                } else {
                    g_AreaCameraHeightStep = (s16)(((s16)span - (s32)g_AreaCameraHeight) / (step * 4));
                }
                state->index_0A--;
                break;
            }
            if (g_AreaCameraMoving != 0) {
                state->index_0A--;
                break;
            }
            span = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
            Area_AdvanceScroll((s16)span);
            break;
        }
        case 0x86:
            if (Actor_GetType() == 1) {
                entry                  = g_AreaLoads[g_GameAreaId];
                byte                   = table[state->index_0A + 1];
                list                   = *(u32**)((u8*)entry + 0x18);
                g_GameState->index_124 = list[byte];
            } else {
                state->unk_03 = table[state->index_0A + 1];
            }
            state->index_0A = 0xFFFF;
            break;
        case 0x87:
            func_801ACBC4();
            break;
        case 0x88:
            func_801AC9D0();
            break;
        case 0x89:
            SND_StartXAStream((table[state->index_0A + 1] << 8) | table[state->index_0A + 2], 1);
            state->index_0A += 2;
            break;
        case 0x8A:
            func_80164020((table[state->index_0A + 1] << 8) | table[state->index_0A + 2], 1);
            state->index_0A += 2;
            break;
        case 0x8B:
            if ((SND_IsXAIdle() & 0xFF) != 0) {
                break;
            }
            state->index_0A--;
            break;
        case 0x8C: {
            volatile Actor* work;

            flag         = table[state->index_0A + 1];
            slot         = g_GameState->slot_index_79;
            work         = SCRATCH_WORK;
            work->unk_0B = func_8015CC00(flag - 0x90, -((flag ^ 0x94) == 0) & 0xA, D_80181B28[g_CharSlot[slot]],
                                         work->pos.x.fixed, work->pos.y.fixed, work->depth.fixed);
            state->index_0A += 1;
            break;
        }
        default:
            break;
    }
    return value;
}
#else
INCLUDE_ASM(func_801AB458);
#endif
