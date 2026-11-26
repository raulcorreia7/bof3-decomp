#include "engine/slus/slus.h"

/* The channel record at g_UiWindowChannel is addressed by byte offsets from its flag halfword: +0 flags, +2 a result
 * byte, +3 a repeat count, +0xC the script cursor, +0x10 the return cursor. */
#define CHAN_CURSOR(base) (*(u8**)((base) + 0xC))
#define CHAN_RETURN(base) (*(u8**)((base) + 0x10))
#define CHAN_FLAGS(base)  (*(u16*)(base))
#define CHAN_STATE(base)  ((base)[-4])

/* runs the channel script at the cursor until an opcode ends the step: 0 returns or ends the step in state 2, 2 ends
 * it in state 3, 3/4/7/8 call a sub-script (with its return cursor kept), 0xA queues a cue, 0xB ends the step in
 * state 1, 0xF/0x14/0x16 load per-channel fields, 0x10/0x11 toggle bit 0x10; other opcodes read the pad state.
 */
/* func_8015083C */
#ifdef NON_MATCHING
NON_MATCHING void UI_MessageRunScript(void) {
    u8   loop;
    u8*  chan;
    u8*  s2;
    u8*  s3;
    u8*  s4;
    u8** s5;
    u8*  t;
    u8   count;
    s32  v;
    u16  flags;

    loop = 1;
    chan = (u8*)&g_UiWindowChannel;
    s5   = (u8**)(chan + 0xC);
    s4   = chan + 2;
    s2   = chan + 0x20;
    s3   = chan - 2;
    do {
        flags = CHAN_FLAGS(chan);
        if (flags & FRONTEND_FLAG_TIMER_ACTIVE) {
            if (--chan[3] == 0) {
                CHAN_FLAGS(chan)  = flags & ~FRONTEND_FLAG_TIMER_ACTIVE;
                CHAN_CURSOR(chan) = CHAN_RETURN(chan) + 1;
            }
        }
        switch (*D_801490B0) {
            case 1:
            case 6:
            case 9:
            case 0xD:
            case 0xE:
                break;
            case 0x100:
                CHAN_FLAGS(chan) |= 0x100;
                break;
            case 0xA:
                *s5 += 1;
                SND_SEPlay(*D_801490B0 | 0x200);
                break;
            case 0:
                if (CHAN_FLAGS(chan) & FRONTEND_FLAG_TIMER_ACTIVE) {
                    CHAN_FLAGS(chan) &= ~FRONTEND_FLAG_TIMER_ACTIVE;
                    CHAN_CURSOR(chan) = CHAN_RETURN(chan);
                } else {
                    loop             = 0;
                    CHAN_STATE(chan) = 2;
                }
                break;
            case 0x16:
                t                 = *(u8**)(s4 + 0xA);
                loop              = 0;
                *(u8**)(s4 + 0xA) = t + 1;
                s4[-6]            = 7;
                s4[0]             = t[1];
                break;
            case 0xB:
                loop             = 0;
                CHAN_STATE(chan) = 1;
                chan[2] += 8;
                break;
            case 2:
                g_UiMessageState.state = 3;
                loop                   = 0;
                break;
            case 0x14:
                t                  = *(u8**)(s2 - 0x14);
                *(u8**)(s2 - 0x14) = t + 1;
                count              = t[1];
                *(u8**)(s2 - 0x14) = t + 3;
                s2[0]              = count;
                s2[2]              = (*D_801490B0 & 0xF) - 1;
                loop               = 0;
                count              = *D_801490B0 >> 4;
                s2[1]              = count;
                if (count == 0) {
                    s2[-0x24] = 5;
                } else {
                    s2[-0x24] = 4;
                }
                break;
            case 7:
                loop              = 0;
                t                 = CHAN_CURSOR(chan) + 1;
                CHAN_CURSOR(chan) = t;
                CHAN_FLAGS(chan) |= FRONTEND_FLAG_TIMER_ACTIVE;
                CHAN_RETURN(chan) = t;
                chan[3]           = 0x21;
                CHAN_CURSOR(chan) = (u8*)&D_801490D7 + (*D_801490B0 << 5);
                break;
            case 3:
                loop = 0;
                CHAN_FLAGS(chan) |= FRONTEND_FLAG_TIMER_ACTIVE;
                CHAN_RETURN(chan) = CHAN_CURSOR(chan);
                chan[3]           = 6;
                CHAN_CURSOR(chan) = (u8*)&D_80144967 + g_CharSlot[g_Game.members[0].chr.character_id] * PARTY_RECORD_STRIDE;
                break;
            case 4:
                loop              = 0;
                t                 = CHAN_CURSOR(chan) + 1;
                CHAN_CURSOR(chan) = t;
                CHAN_FLAGS(chan) |= FRONTEND_FLAG_TIMER_ACTIVE;
                CHAN_RETURN(chan) = t;
                chan[3]           = 6;
                CHAN_CURSOR(chan) = (u8*)&D_80144967 + *D_801490B0 * PARTY_RECORD_STRIDE;
                break;
            case 0xF:
                t                  = *(u8**)(s3 + 0xE);
                *(u8**)(s3 + 0xE)  = t + 1;
                s3[1]              = 0;
                s3[-1]             = 0;
                s3[0]              = D_8017F5B8[t[1]].unk_00;
                *(u16*)(s3 + 8)    = D_8017F5B8[*D_801490B0].unk_02;
                *(s16*)(s3 + 0x26) = (s8)D_8017F5B8[*D_801490B0].unk_01;
                break;
            case 5:
            case 0xC:
                *s5 += 1;
                break;
            case 8:
                CHAN_FLAGS(chan) |= FRONTEND_FLAG_TIMER_ACTIVE;
                CHAN_CURSOR(chan) += 1;
                CHAN_RETURN(chan) = CHAN_CURSOR(chan);
                v                 = *D_801490B0;
                t                 = (u8*)D_80010004 + SLUS_LOAD_ADDRESS;
                CHAN_CURSOR(chan) = t;
                chan[3]           = 0x11;
                CHAN_CURSOR(chan) = t + *(u16*)(D_801490B0 + v * 2);
                break;
            case 0x10:
            case 0x11:
                CHAN_FLAGS(chan) ^= FRONTEND_FLAG_NO_INPUT_WAIT;
                break;
            case 0x12:
            case 0x13:
            case 0x15:
                *s5 += 1;
                /* fallthrough */
            default:
                if (!(CHAN_FLAGS(chan) & FRONTEND_FLAG_NO_INPUT_WAIT)) {
                    if (g_InputMasks[MESSAGE_INPUT_SPEED_UP] & g_PadStates[0].held) {
                        chan[2] = D_8017F5B4[g_MessageSpeed];
                    } else {
                        chan[2] = D_8017F5B4[g_MessageSpeed + 1];
                    }
                    if (CHAN_FLAGS(chan) & FRONTEND_FLAG_FORCE_STEP) {
                        chan[2] = 3;
                    }
                    if (chan[2] == 0) {
                        CHAN_STATE(chan) = 0;
                    } else {
                        CHAN_STATE(chan) = 1;
                    }
                    loop = 0;
                }
                g_UiMessageState.index += 1;
                break;
        }
        if (CHAN_FLAGS(chan) & FRONTEND_FLAG_NO_INPUT_WAIT) {
            loop = 1;
        }
        CHAN_CURSOR(chan) += 1;
    } while (loop);
}
#else
INCLUDE_ASM(UI_MessageRunScript);
#endif
