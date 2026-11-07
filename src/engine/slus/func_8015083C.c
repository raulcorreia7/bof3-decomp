#include "engine/slus/slus.h"

/* The channel record at g_UiWindowChannel is addressed by byte offsets from its flag halfword: +0 flags, +2 a result
 * byte, +3 a repeat count, +0xC the script cursor, +0x10 the return cursor. */
#define CHAN_CURSOR(base) (*(u8**)((base) + 0xC))
#define CHAN_RETURN(base) (*(u8**)((base) + 0x10))
#define STEP_TABLE        ((u8*)D_8017F5B4)

/* runs the channel script at the cursor until an opcode ends the step: 0 returns or ends the step in state 2, 2 ends
 * it in state 3, 3/4/7/8 call a sub-script (with its return cursor kept), 0xA queues a cue, 0xB ends the step in
 * state 1, 0xF/0x14/0x16 load per-channel fields, 0x10/0x11 toggle bit 0x10; other opcodes read the pad state.
 */
/* nonmatching 24.33%: restated from the first draft with byte-offset field access and the dense switch. resume:
 * register assignment of the base pointers and the case order. */
#ifdef NON_MATCHING
NON_MATCHING void func_8015083C(void) {
    u8  loop;
    u8* chan;
    u8* s2;
    u8* s3;
    u8* s4;
    u8* t;
    u8  count;
    s32 v;

    loop = 1;
    chan = (u8*)&g_UiWindowChannel;
    s4   = chan + 2;
    s2   = chan + 0x20;
    s3   = chan - 2;
    do {
        if (g_UiWindowChannel & FRONTEND_FLAG_TIMER_ACTIVE) {
            count   = chan[3] - 1;
            chan[3] = count;
            if (count == 0) {
                g_UiWindowChannel &= ~FRONTEND_FLAG_TIMER_ACTIVE;
                CHAN_CURSOR(chan) = CHAN_RETURN(chan) + 1;
            }
        }
        switch (*D_801490B0) {
            case 0:
                if (g_UiWindowChannel & FRONTEND_FLAG_TIMER_ACTIVE) {
                    g_UiWindowChannel &= ~FRONTEND_FLAG_TIMER_ACTIVE;
                    CHAN_CURSOR(chan) = CHAN_RETURN(chan);
                } else {
                    loop                    = 0;
                    g_MessageState.state_00 = 2;
                }
                break;
            case 1:
            case 6:
            case 9:
            case 0xD:
            case 0xE:
                break;
            case 2:
                g_MessageState.state_00 = 3;
                loop                    = 0;
                break;
            case 3:
                g_UiWindowChannel |= FRONTEND_FLAG_TIMER_ACTIVE;
                CHAN_RETURN(chan) = CHAN_CURSOR(chan);
                v                 = g_CharSlot[g_BattlePartyBattlers[0].chr.character_id];
                loop              = 0;
                chan[3]           = 6;
                CHAN_CURSOR(chan) = (u8*)&D_80144967 + v * 0xA4;
                break;
            case 4:
                loop              = 0;
                t                 = CHAN_CURSOR(chan) + 1;
                CHAN_CURSOR(chan) = t;
                g_UiWindowChannel |= FRONTEND_FLAG_TIMER_ACTIVE;
                CHAN_RETURN(chan) = t;
                v                 = *D_801490B0;
                chan[3]           = 6;
                CHAN_CURSOR(chan) = (u8*)&D_80144967 + v * 0xA4;
                break;
            case 5:
            case 0xC:
                CHAN_CURSOR(chan) += 1;
                break;
            case 7:
                loop              = 0;
                t                 = CHAN_CURSOR(chan) + 1;
                CHAN_CURSOR(chan) = t;
                g_UiWindowChannel |= FRONTEND_FLAG_TIMER_ACTIVE;
                CHAN_RETURN(chan) = t;
                chan[3]           = 0x21;
                CHAN_CURSOR(chan) = (u8*)&D_801490D7 + (*D_801490B0 << 5);
                break;
            case 8:
                t = CHAN_CURSOR(chan) + 1;
                g_UiWindowChannel |= FRONTEND_FLAG_TIMER_ACTIVE;
                CHAN_CURSOR(chan) = t;
                CHAN_RETURN(chan) = t;
                v                 = *D_801490B0;
                t                 = (u8*)D_80010004 + SLUS_LOAD_ADDRESS;
                CHAN_CURSOR(chan) = t;
                chan[3]           = 0x11;
                CHAN_CURSOR(chan) = t + *(u16*)(D_801490B0 + v * 2);
                break;
            case 0xA:
                CHAN_CURSOR(chan) += 1;
                SND_PlayCue(*D_801490B0 | 0x200);
                break;
            case 0xB:
                loop                    = 0;
                g_MessageState.state_00 = 1;
                chan[2] += 8;
                break;
            case 0xF:
                t                  = *(u8**)(s3 + 0xE);
                *(u8**)(s3 + 0xE)  = t + 1;
                s3[1]              = 0;
                s3[-1]             = 0;
                s3[0]              = STEP_TABLE[t[1] * 4 + 4];
                *(u16*)(s3 + 8)    = *(u16*)&STEP_TABLE[*D_801490B0 * 4 + 6];
                *(s16*)(s3 + 0x26) = (s8)STEP_TABLE[*D_801490B0 * 4 + 5];
                break;
            case 0x10:
            case 0x11:
                g_UiWindowChannel ^= FRONTEND_FLAG_NO_INPUT_WAIT;
                break;
            case 0x14:
                t                       = *(u8**)(s2 - 0x14);
                *(u8**)(s2 - 0x14)      = t + 3;
                s2[0]                   = t[1];
                s2[2]                   = (*D_801490B0 & 0xF) - 1;
                loop                    = 0;
                s2[1]                   = *D_801490B0 >> 4;
                g_MessageState.state_00 = (s2[1] == 0) ? 5 : 4;
                break;
            case 0x16:
                t                       = *(u8**)(s4 + 0xA);
                loop                    = 0;
                *(u8**)(s4 + 0xA)       = t + 1;
                g_MessageState.state_00 = 7;
                s4[0]                   = t[1];
                break;
            case 0x12:
            case 0x13:
            case 0x15:
                CHAN_CURSOR(chan) += 1;
                /* fallthrough */
            default:
                if (!(g_UiWindowChannel & FRONTEND_FLAG_NO_INPUT_WAIT)) {
                    if (g_InputMasks[MESSAGE_INPUT_SPEED_UP] & g_InputHeld) {
                        chan[2] = STEP_TABLE[D_80144950 * 4];
                    } else {
                        chan[2] = STEP_TABLE[D_80144950 * 4 + 1];
                    }
                    if (g_UiWindowChannel & FRONTEND_FLAG_FORCE_STEP) {
                        chan[2] = 3;
                    }
                    if (chan[2] == 0) {
                        g_MessageState.state_00 = 0;
                    } else {
                        g_MessageState.state_00 = 1;
                    }
                    loop = 0;
                }
                D_801490B9 += 1;
                break;
        }
        if (g_UiWindowChannel & FRONTEND_FLAG_NO_INPUT_WAIT) {
            loop = 1;
        }
        CHAN_CURSOR(chan) += 1;
    } while (loop);
}
#else
INCLUDE_ASM(func_8015083C);
#endif
