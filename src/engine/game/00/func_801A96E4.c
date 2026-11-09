#include "game_00.h"

MATCH void func_801A96E4(ScriptState* state, u8* base) {
    switch (*(base + state->cursor)) {
        case 0xB0:
            SND_PlayCue(*(base + state->cursor + 1));
            state->cursor += 1;
            break;
        case 0xB1:
            SND_PlayCue(*(base + state->cursor + 1) | 0x100);
            state->cursor += 1;
            break;
        case 0xB2:
            SND_PlayCue(*(base + state->cursor + 1) | 0x200);
            state->cursor += 1;
            break;
        case 0xB3:
            SND_PlayCue(*(base + state->cursor + 1) | 0x300);
            state->cursor += 1;
            break;
        case 0xB4:
            SND_PlayBGM(*(base + state->cursor + 1), 0x64, 8);
            state->cursor += 1;
            break;
        case 0xB5:
            SND_FadeOutBGM(*(base + state->cursor + 1), 0x64, 8);
            state->cursor += 1;
            break;
        case 0xB8:
            SND_PlaySequence(*(base + state->cursor + 1), *(base + state->cursor + 2), *(base + state->cursor + 3), *(base + state->cursor + 3));
            state->cursor += 3;
            break;
        case 0xB9:
            SND_StopSequence(*(base + state->cursor + 1), *(base + state->cursor + 2));
            state->cursor += 2;
            break;
        case 0xBA:
            SND_FadeInSequence(*(base + state->cursor + 1), *(base + state->cursor + 2), *(base + state->cursor + 3), *(base + state->cursor + 4));
            state->cursor += 4;
            break;
        case 0xBB:
            SND_StartDecrescendo(*(base + state->cursor + 1), *(base + state->cursor + 2), *(base + state->cursor + 3), *(base + state->cursor + 4));
            state->cursor += 4;
            break;
        case 0xBC:
            SND_QueueCueVolume(*(base + state->cursor + 2) | (*(base + state->cursor + 1) << 8), *(base + state->cursor + 3), *(base + state->cursor + 4));
            state->cursor += 4;
            break;
        case 0xBD:
            func_8015D820(*(base + state->cursor + 2) | (*(base + state->cursor + 1) << 8), *(base + state->cursor + 3));
            state->cursor += 3;
            break;
        case 0xBE:
            SND_StartBGM(*(base + state->cursor + 1), 0x64, 8);
            state->cursor += 1;
            break;
        default:
            break;
    }
}
