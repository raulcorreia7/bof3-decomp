#include "game_00.h"

/* nonmatching unmeasured: tried first-draft switch cleaned; signed divide by array element adds 8 stack bytes (frame
 * 0x28 vs 0x20); index pointer, cursor tails. */
#ifdef NON_MATCHING
NON_MATCHING u8 func_801AA470(void* sub, s32 target, u8 value) {
    u8* code;
    u8* cmd;
    u8  slot;
    s32 tmp;
    u16 hit;
    u16 next;
    u8* index;

    code = (u8*)target;
    switch (code[FIELD(u16, sub, 0xAu)]) {
        case 0xD0:
            g_PartyX       = g_AreaScrollTargetX;
            g_PartyY       = g_AreaScrollTargetY;
            g_ScrollHeight = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
            return value;
        case 0xD1:
            if (g_GameStateIndex != GAME_REQUEST_BATTLE) {
                hit              = Actor_ReadState();
                SP_REF(u16, 0x0) = hit;
                if (g_Task->script_pc != hit) {
                    cmd = code + FIELD(u16, sub, 0xAu);
                    if (hit == cmd[3]) {
                        func_8015D820(cmd[2] | (cmd[1] << 8), cmd[4]);
                    }
                }
            }
            next = FIELD(u16, sub, 0xAu) + 4;
        set_cursor:
            FIELD(u16, sub, 0xAu) = next;
        done:
            return value;
        case 0xD2:
            g_Task->option_flags ^= 0x40;
            if (g_Task->option_flags & 0x40) {
                FIELD(s8, g_Task, 0x48u) = 0;
            } else {
                FIELD(s8, g_Task, 0x48u) = 1;
            }
            return value;
        case 0xD3:
            g_Task->option_flags ^= ACTOR_OPT_NO_TARGET;
            return value;
        case 0xD4:
            index  = &D_1F800001;
            tmp    = -(g_CurrentActor - D_80147A58) >> 3;
            *index = tmp;
            if ((u8)tmp >= 5U) {
                *index = 4;
            }
            cmd = code + FIELD(u16, sub, 0xAu);
            if (cmd[7] != 0) {
                slot                                  = cmd[7];
                D_80147CB9[*index * 0x10]             = slot;
                D_80147CBA[*index * 0x10]             = slot;
                cmd                                   = code + FIELD(u16, sub, 0xAu);
                FIELD(s32, D_80147CC4, *index * 0x10) = (s16)(cmd[6] | (cmd[5] << 8)) / D_80147CBA[*index * 0x10];
                cmd                                   = code + FIELD(u16, sub, 0xAu);
                FIELD(s32, D_80147CC0, *index * 0x10) = (s16)(cmd[4] | (cmd[3] << 8)) / D_80147CBA[*index * 0x10];
                cmd                                   = code + FIELD(u16, sub, 0xAu);
                FIELD(s32, D_80147CBC, *index * 0x10) = (s16)(cmd[2] | (cmd[1] << 8)) / D_80147CBA[*index * 0x10];
            } else {
                g_Task->unk_6C = (s16)(cmd[6] | (cmd[5] << 8));
                cmd            = code + FIELD(u16, sub, 0xAu);
                g_Task->unk_68 = (s16)(cmd[4] | (cmd[3] << 8));
                cmd            = code + FIELD(u16, sub, 0xAu);
                g_Task->unk_64 = (s16)(cmd[2] | (cmd[1] << 8));
            }
            *(u8*)sub |= 8;
            FIELD(u16, sub, 0xAu) += 7;
            goto done;
        case 0xD5:
            tmp             = -(g_CurrentActor - D_80147A58) >> 3;
            SP_REF(s8, 0x1) = tmp;
            tmp &= BYTE_MASK;
            if ((u32)tmp < 4U && (D_80147CBA[tmp * 0x10] + D_80147CB9[tmp * 0x10]) != 0) {
                goto back;
            }
            return value;
        case 0xD6:
            index  = &D_1F800001;
            tmp    = -(g_CurrentActor - D_80147A58) >> 3;
            *index = tmp;
            if (tmp & 0x80) {
                *index = 4;
            }
            D_80147CB8[(s8)*index * 0x10] ^= 1;
            return value;
        case 0xD7:
            slot = code[FIELD(u16, sub, 0xAu) + 1];
            FIELD(u16, sub, 0xAu) += 1;
            FIELD(u8, sub, 0x6u) = slot;
            return value;
        case 0xD8:
            g_GameFlags &= ~GAME_FLAG_SCROLL_LOCK;
            *(u8*)sub |= 8;
            return value;
        case 0xD9:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                goto back;
            }
            return value;
        case 0xDA:
            if (WINDOW_EFFECT_BUSY()) {
                goto back;
            }
            return value;
        case 0xDB:
            Actor_ApplyVelocity();
            COORD_INT(g_Task->pos.z) = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
            /* fallthrough */
        case 0xDC:
            Area_SetCellPalette(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y));
            return value;
        case 0xDD:
            Area_ClearCellPalette(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y));
            return value;
        case 0xDE: {
            void* obj = g_AreaLoads[g_GameAreaId];
            (*(void (**)())((code[FIELD(u16, sub, 0xAu) + 1] * 4) + FIELD(s32, obj, 0x3Cu)))(obj);
            value = g_Task->direction_08;
            next  = FIELD(u16, sub, 0xAu) + 1;
            goto set_cursor;
        }
        case 0xDF:
            if (g_GameStateIndex == GAME_REQUEST_BATTLE) {
                goto back;
            }
            return value;
        default:
            goto done;
    }
back:
    next = FIELD(u16, sub, 0xAu) - 1;
    goto set_cursor;
}
#else
INCLUDE_ASM(func_801AA470);
#endif
