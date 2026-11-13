#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801A8F94(ScriptState* state, u8* base, s32 seed) {
    s32         left;
    s32         sel;
    s32         dist;
    s8          step;
    void*       obj;
    ObjectFunc* table;

    sel = seed;
    for (;;) {
        switch (base[state->cursor] & 0xF0) {
            case 0x00:
                switch (base[state->cursor]) {
                    case 1:
                        if ((base[state->cursor + 1] & 0xC0) == 0x40) {
                            state->cursor = (u16)(base[state->cursor + 2] | (base[state->cursor + 1] << 8));
                            state->cursor = func_801AC8F0(state, (u8)state->cursor, base);
                        } else {
                            state->cursor = (u16)(state->cursor + base[state->cursor + 2] + (base[state->cursor + 1] << 8));
                        }
                        break;
                    case 2:
                        if (state->count_02 == 0) {
                            state->count_02 = base[state->cursor + 2];
                            state->cursor   = (u16)(state->cursor + (s8)base[state->cursor + 1]);
                        } else {
                            state->count_02--;
                            if (state->count_02 != 0)
                                state->cursor = (u16)(state->cursor + (s8)base[state->cursor + 1]);
                            else
                                state->cursor += 3;
                        }
                        break;
                    case 3:
                        obj   = g_AreaLoads[g_GameAreaId];
                        table = FIELD(ObjectFunc*, obj, 0x3Cu);
                        table[base[state->cursor + 1]](obj);
                        sel = g_Task->direction_08;
                        state->cursor += 2;
                        break;
                    case 4:
                        left = base[state->cursor + 1];
                        if (func_8015B870(base[state->cursor + 2]) == left)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = func_801AC8F0(state, (u8)state->cursor, base);
                        break;
                    case 5:
                        left = func_8015B870(base[state->cursor + 1]);
                        if (func_8015B870(base[state->cursor + 2]) == left)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = func_801AC8F0(state, (u8)state->cursor, base);
                        break;
                    case 6:
                        left = base[state->cursor + 1];
                        if (func_8015B870(base[state->cursor + 2]) < left)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = func_801AC8F0(state, (u8)state->cursor, base);
                        break;
                    case 7:
                        left = func_8015B870(base[state->cursor + 1]);
                        if (func_8015B870(base[state->cursor + 2]) < left)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = func_801AC8F0(state, (u8)state->cursor, base);
                        break;
                    case 8:
                        left = base[state->cursor + 1];
                        if ((func_8015B870(base[state->cursor + 2]) & left) != 0)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = func_801AC8F0(state, (u8)state->cursor, base);
                        break;
                    case 9:
                        left = func_8015B870(base[state->cursor + 1]);
                        if ((func_8015B870(base[state->cursor + 2]) & left) != 0)
                            state->cursor = (u16)(base[state->cursor + 3] | (base[state->cursor + 4] << 8));
                        else
                            state->cursor = (u16)(base[state->cursor + 5] | (base[state->cursor + 6] << 8));
                        state->cursor = func_801AC8F0(state, (u8)state->cursor, base);
                        break;
                    case 10:
                        state->cursor += 2;
                        break;
                    case 11:
                        state->cursor = 0;
                        break;
                    case 12:
                        if (base[state->cursor + 1] == 0)
                            Party_HideBattlers();
                        else
                            Party_ShowBattlers();
                        state->cursor += 2;
                        break;
                    case 13:
                        if (Actor_GetOwner() == 2) {
                            g_PartyX       = (s32)((base[state->cursor + 1] << 16) | ((base[state->cursor + 2] != 0) << 15));
                            g_PartyY       = (s32)((base[state->cursor + 3] << 16) | ((base[state->cursor + 4] != 0) << 15));
                            g_ScrollHeight = Area_SampleHeight(g_PartyX, g_PartyY);
                            sel            = 0xFF;
                        } else {
                            g_Task->pos.x.fixed      = (s32)((base[state->cursor + 1] << 16) | ((base[state->cursor + 2] != 0) << 15));
                            g_Task->pos.y.fixed      = (s32)((base[state->cursor + 3] << 16) | ((base[state->cursor + 4] != 0) << 15));
                            COORD_INT(g_Task->pos.z) = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
                        }
                        state->cursor += 5;
                        break;
                    case 14:
                        left = base[state->cursor + 1];
                        state->flag_00 |= 0x40;
                        g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
                        if ((base[state->cursor + 3] & 1) != 0)
                            g_Task->header.flags |= ACTOR_FLAG_STEP_MOVE;
                        else
                            g_Task->header.flags &= ~ACTOR_FLAG_STEP_MOVE;
                        g_Task->unk_2A = base[state->cursor + 2];
                        if ((base[state->cursor + 3] & 2) != 0) {
                            Actor_BeginScript((u8)(left & BYTE_MASK), base[state->cursor + 4]);
                            state->cursor += 1;
                        } else {
                            Actor_SelectScript((u8)(left & BYTE_MASK));
                        }
                        state->cursor += 4;
                        break;
                    case 15:
                        left = s_TalkMessageIds[base[state->cursor + 1] * 11 + g_Game.current->chr.character_id];
                        state->flag_00 |= 0x40;
                        g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
                        if ((base[state->cursor + 3] & 1) != 0)
                            g_Task->header.flags |= ACTOR_FLAG_STEP_MOVE;
                        else
                            g_Task->header.flags &= ~ACTOR_FLAG_STEP_MOVE;
                        g_Task->unk_2A = base[state->cursor + 2];
                        if ((base[state->cursor + 3] & 2) != 0) {
                            Actor_BeginScript((u8)(left & BYTE_MASK), base[state->cursor + 4]);
                            state->cursor += 1;
                        } else {
                            Actor_SelectScript((u8)(left & BYTE_MASK));
                        }
                        state->cursor += 4;
                        break;
                }
                break;
            case 0xA0:
                dist = D_801821C0[base[state->cursor] & 3](base + state->cursor);
                step = (s8)dist;
                if (step < 0)
                    return (u8)(sel & BYTE_MASK);
                state->cursor = (u16)(state->cursor + step + 1);
                break;
            case 0xB0:
                func_801A96E4(state, base);
                state->cursor += 1;
                break;
            default:
                return (u8)(sel & BYTE_MASK);
        }
    }
}
#else
INCLUDE_ASM(func_801A8F94);
#endif
